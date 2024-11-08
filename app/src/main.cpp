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

#include "display.h"
#include "tiles.h"

#define CONFIG_BOARD "nRF52840"

LOG_MODULE_REGISTER(main);

#define ETC_PARTITION_NODE DT_NODELABEL(etc)
#define MNT_PARTITION_NODE DT_NODELABEL(mnt)

FS_FSTAB_DECLARE_ENTRY(ETC_PARTITION_NODE);
FS_FSTAB_DECLARE_ENTRY(MNT_PARTITION_NODE);

Display white_display =
    Display(DEVICE_DT_GET(DT_NODELABEL(display_white)),
            DT_PROP(DT_NODELABEL(display_white), width),
            DT_PROP(DT_NODELABEL(display_white), height), 24);
Display black_display =
    Display(DEVICE_DT_GET(DT_NODELABEL(display_black)),
            DT_PROP(DT_NODELABEL(display_black), width),
            DT_PROP(DT_NODELABEL(display_black), height), 24);
Tiles tiles;
Chess chess;

void gameStartedCb() { LOG_INF("Game started\n"); }
void gameEndedCb() { LOG_INF("Game ended\n"); }
void moveMadeCb(ChessMove move) {
  char buff[7];
  move.toString(buff);
  buff[6] = '\0';
  LOG_INF("Move made: %s\n", buff);
}
void pieceHighlightedCb(ChessPosition position) {
  char buff[3];
  position.toString(buff);
  buff[2] = '\0';
  LOG_INF("Piece at %s highlighted\n", buff);

  tiles.setTileColor(position, 0x00FF00);
}
void pieceUnhighlightedCb(ChessPosition position) {
  char buff[3];
  position.toString(buff);
  buff[2] = '\0';
  LOG_INF("Piece at %s unhighlighted\n", buff);

  tiles.setTileColor(position, 0x000000);
}
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
      /* char buff[3];
      position->toString(buff);
      buff[2] = '\0';

      LOG_INF("Tile at %s has been %s\n", buff,
              state ? "put down" : "picked up"); */

      tile->state = state;
      ChessTileActionType action =
          (state) ? ChessTileActionType::PutDown : ChessTileActionType::PickUp;
      chess.notifyTileAction(position, action);
    }
  }
}

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

  LOG_INF("Initializing tiles");
  ret = tiles.init();
  if (ret < 0) {
    LOG_ERR("Failed to initialize tiles\n");
    return ret;
  }
  LOG_INF("Tiles initialized\n");

  LOG_INF("Initializing displays");
  white_display.init();
  black_display.init();

  lv_obj_t *hello_world_label;
  hello_world_label =
      lv_label_create(lv_disp_get_scr_act(white_display.display));
  lv_obj_set_style_text_font(hello_world_label, &lv_font_montserrat_24, 0);
  lv_label_set_text(hello_world_label, "Ekran dla bialych");
  lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);

  lv_obj_t *hello_world_label2;
  hello_world_label2 =
      lv_label_create(lv_disp_get_scr_act(black_display.display));
  lv_obj_set_style_text_font(hello_world_label2, &lv_font_montserrat_24, 0);
  lv_label_set_text(hello_world_label2, "Ekran dla czarnych");
  lv_obj_align(hello_world_label2, LV_ALIGN_CENTER, 0, 0);

  lv_task_handler();
  display_blanking_off(white_display.dev);
  display_blanking_off(black_display.dev);

  while (true) {
    lv_task_handler();
    k_sleep(K_MSEC(100));
  }

  return 0;
}
