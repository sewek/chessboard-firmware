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

void gameStartedCb() { LOG_INF("Game started"); }

void gameEndedCb() {
  LOG_INF("Game ended");
  ChessGameResult result = chess.getGameResult();

  whiteTimer.stop();
  blackTimer.stop();

  if (result == ChessGameResult::WhiteWins) {
    screenController.navigateTo(ChessColor::White, "win");
    screenController.navigateTo(ChessColor::Black, "lose");
  } else if (result == ChessGameResult::BlackWins) {
    screenController.navigateTo(ChessColor::White, "lose");
    screenController.navigateTo(ChessColor::Black, "win");
  } else {
    screenController.navigateTo(ChessColor::White, "draw2");
    screenController.navigateTo(ChessColor::Black, "draw2");
  }
}

void moveMadeCb(ChessMove *move) {
  char buff[7];
  move->toString(buff);
  buff[6] = '\0';
  LOG_INF("Move made: %s", buff);
}

void pieceHighlightedCb(ChessPosition *position, ChessHighlightType type) {
  printk("Highlighting piece\n");
  // char buff[3];
  // position->toString(buff);
  // buff[2] = '\0';
  // LOG_INF("Piece at %s highlighted", buff);

  tiles.setTileColor(position, getColor(type));
}

void pieceUnhighlightedCb(ChessPosition *position) {
  printk("Unhighlighting piece\n");
  // char buff[3];
  // position->toString(buff);
  // buff[2] = '\0';
  // LOG_INF("Piece at %s unhighlighted", buff);

  refreshTileColor(&tiles, position);
}

void chessCastlingCb(ChessColor color) {
  screenController.navigateTo(color, "castling");
}

void chessPromotionCb(ChessColor color) {
  screenController.navigateTo(color, "promotion");
}

void chessEnPassantCb(ChessColor color) {
  screenController.navigateTo(color, "en_passant");
}

void chessErrorCb(ChessColor color) {
  screenController.navigateTo(color, "error");
}

int main() {
  LOG_INF("build time: " __DATE__ " " __TIME__ "");
  LOG_INF("board: %s", CONFIG_BOARD);

  int ret;

  chess.addListener(ChessEventType::GameStarted, gameStartedCb);
  chess.addListener(ChessEventType::GameEnded, gameEndedCb);
  chess.addListener(ChessEventType::MoveMade, moveMadeCb);
  chess.addListener(ChessEventType::HighlightSquare, pieceHighlightedCb);
  chess.addListener(ChessEventType::UnhighlightSquare, pieceUnhighlightedCb);
  chess.addListener(ChessEventType::Castling, chessCastlingCb);
  chess.addListener(ChessEventType::Promotion, chessPromotionCb);
  chess.addListener(ChessEventType::EnPassant, chessEnPassantCb);
  chess.addListener(ChessEventType::Error, chessErrorCb);
  tiles.setTriggerHandler(tilesChangeCallback);

  LOG_INF("Initializing buttons");
  ret = buttons.init();
  if (ret < 0) {
    LOG_ERR("Failed to initialize buttons");
    return ret;
  }
  LOG_INF("Buttons initialized");

  LOG_INF("Initializing tiles");
  ret = tiles.init();
  if (ret < 0) {
    LOG_ERR("Failed to initialize tiles");
    return ret;
  }
  LOG_INF("Tiles initialized");

  refreshTilesColor(&tiles);

  LOG_INF("Initializing screen controller");
  ret = screenController.init();
  if (ret < 0) {
    LOG_ERR("Failed to initialize screen controller");
    return ret;
  }
  LOG_INF("Screen controller initialized");

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

  while (true) {
    // Refresh the screen
    handleTilesAction();
    screenController.run();

    k_sleep(K_MSEC(50));
  }

  return 0;
}
