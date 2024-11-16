#include <chess.h>
#include <tiles.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(tiles_trigger);

extern Tiles tiles;
extern Chess chess;

K_THREAD_DEFINE(tiles_callback_thread, 1024, tilesTriggerHandler, nullptr,
                nullptr, nullptr, 10, 0, 0);
K_SEM_DEFINE(tiles_sem, 1, 1);
K_MSGQ_DEFINE(chess_queue, sizeof(Tile *), 64, 4);

void tilesChangeCallback(const struct device *dev,
                         const struct sensor_trigger *trg) {
  struct sensor_value buff;
  Tile *tile = nullptr;
  ChessPosition *position = nullptr;
  uint8_t state = 0;

  sensor_channel_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_STATE, &buff);

  for (int i = 0; i < 64; i++) {
    if (!tiles.tiles[i].dev) {
      continue;
    }

    if (tiles.tiles[i].dev != dev) {
      continue;
    }

    tile = &tiles.tiles[i];
    position = &tile->position;
    state = (buff.val1 >> (tile->channel - 1)) & 0x01;

    bool state_changed = (tile->state != state);

    if (state_changed) {
      // Test log
      char buff[3];
      position->toString(buff);
      buff[2] = '\0';

      LOG_INF("CALLBACK: Tile at %s has been %s\n", buff,
              state ? "put down" : "picked up");

      tile->state = state;

      while (k_msgq_put(&chess_queue, &tile, K_NO_WAIT) != 0) {
        k_yield();
      }
    }
  }

  k_sem_give(&tiles_sem);
}

void tilesTriggerHandler(void *arg1, void *arg2, void *arg3) {
  ARG_UNUSED(arg1);
  ARG_UNUSED(arg2);
  ARG_UNUSED(arg3);

  Tile *tile = nullptr;
  ChessPosition *position = nullptr;
  char buff[3];
  while (1) {
    k_sem_take(&tiles_sem, K_FOREVER);

    while (k_msgq_num_used_get(&chess_queue)) {
      k_msgq_get(&chess_queue, &tile, K_NO_WAIT);

      if (tile == nullptr) {
        LOG_ERR("HANDLER: Tile is null\n");
        continue;
      }

      position = &tile->position;

      position->toString(buff);
      buff[2] = '\0';

      LOG_INF("HANDLER: Tile at %s has been %s\n", buff,
              tile->state ? "put down" : "picked up");

      ChessTileActionType action = (tile->state) ? ChessTileActionType::PutDown
                                                 : ChessTileActionType::PickUp;
      chess.notifyTileAction(position, action);

      k_yield();
    }
  }
}