/**
 * @file main.cpp
 * @brief Main source file.
 */
#include <chess.h>
#include <chess_types.h>
#include <lvgl.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/fs/fs.h>
#include <zephyr/fs/littlefs.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/usb/usb_device.h>

#include "buttons.h"
#include "display.h"
#include "highlights.h"
#include "screens/screen_controller.h"
#include "tiles.h"
#include "timer.h"

#define CONFIG_BOARD "nRF52840"

LOG_MODULE_REGISTER(main);

#define ETC_PARTITION_NODE DT_NODELABEL(etc)
#define MNT_PARTITION_NODE DT_NODELABEL(mnt)

FS_FSTAB_DECLARE_ENTRY(ETC_PARTITION_NODE);
FS_FSTAB_DECLARE_ENTRY(MNT_PARTITION_NODE);

/* Timers */
Timer whiteTimer;
Timer blackTimer;

/* Buttons */
Buttons buttons;

/* Displays */
ScreenController screenController;

/* Tiles */
Tiles tiles;

/* Chess */
Chess chess;

void gameStartedCb() { LOG_INF("Game started\n"); }

void gameEndedCb() { LOG_INF("Game ended\n"); }

void moveMadeCb(ChessMove *move) {
  char buff[7];
  move->toString(buff);
  buff[6] = '\0';
  LOG_INF("Move made: %s\n", buff);
}

void pieceHighlightedCb(ChessPosition *position, ChessHighlightType type) {
  printk("Highlighting piece\n");
  char buff[3];
  position->toString(buff);
  buff[2] = '\0';
  LOG_INF("Piece at %s highlighted\n", buff);

  tiles.setTileColor(position, getColor(type));
}

void pieceUnhighlightedCb(ChessPosition *position) {
  char buff[3];
  position->toString(buff);
  buff[2] = '\0';
  LOG_INF("Piece at %s unhighlighted\n", buff);

  refreshTileColor(&tiles, position);
}

/* void tilesChangeCallback(const struct device *dev,
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

    LOG_INF("Tile %d state: %d\n", i, state);

    if (state_changed) {
      // Test log
      char buff[3];
      position->toString(buff);
      buff[2] = '\0';

      LOG_INF("Tile at %s has been %s\n", buff,
              state ? "put down" : "picked up");

      tile->state = state;
      ChessTileActionType action =
          (state) ? ChessTileActionType::PutDown : ChessTileActionType::PickUp;
      chess.notifyTileAction(position, action);
    }
  }
} */

int main() {
  LOG_INF("build time: " __DATE__ " " __TIME__ "\n");
  LOG_INF("board: %s\n", CONFIG_BOARD);

  int ret;

  chess.addListener(ChessEventType::GameStarted, gameStartedCb);
  chess.addListener(ChessEventType::GameEnded, gameEndedCb);
  chess.addListener(ChessEventType::MoveMade, moveMadeCb);
  chess.addListener(ChessEventType::HighlightSquare, pieceHighlightedCb);
  chess.addListener(ChessEventType::UnhighlightSquare, pieceUnhighlightedCb);
  tiles.setTriggerHandler(tilesChangeCallback);

  LOG_INF("Initializing buttons");
  ret = buttons.init();
  if (ret < 0) {
    LOG_ERR("Failed to initialize buttons\n");
    return ret;
  }
  LOG_INF("Buttons initialized\n");

  LOG_INF("Initializing screen controller");
  ret = screenController.init();
  if (ret < 0) {
    LOG_ERR("Failed to initialize screen controller\n");
    return ret;
  }
  LOG_INF("Screen controller initialized\n");

  LOG_INF("Initializing tiles");
  ret = tiles.init();
  if (ret < 0) {
    LOG_ERR("Failed to initialize tiles\n");
    return ret;
  }
  LOG_INF("Tiles initialized\n");

  refreshTilesColor(&tiles);

  Tile *tile = nullptr;
  for (int i = 0; i < 64; i++) {
    tile = &tiles.tiles[i];
    if (tile->dev == nullptr) {
      continue;
    }

    chess.notifyTileAction(&tile->position, tile->state
                                                ? ChessTileActionType::PutDown
                                                : ChessTileActionType::PickUp);
  }

  if (chess.startGame() != ChessGameStartError::Ok) {
    LOG_ERR("Failed to start game\n");
    return -1;
  }

  // display_blanking_off(white_display.dev);
  // display_blanking_off(black_display.dev);

  while (true) {
    // Refresh the screen
    screenController.run();
    k_sleep(K_MSEC(200));
  }

  return 0;
}
