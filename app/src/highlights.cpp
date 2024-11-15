#include "highlights.h"

#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(highlights, LOG_LEVEL_DBG);

uint32_t rgbToHex(uint32_t rgb) {
  return (rgb >> 16) | ((rgb & 0x00FF00) | (rgb << 16));
}

uint32_t getColor(ChessHighlightType type) {
  switch (type) {
    case ChessHighlightType::NormalMove:
      return rgbToHex(NORMAL_MOVE_COLOR);
    case ChessHighlightType::CaptureMove:
      return rgbToHex(CAPTURE_MOVE_COLOR);
    case ChessHighlightType::Check:
      return rgbToHex(CHECK_COLOR);
    case ChessHighlightType::Error:
      return rgbToHex(ERROR_COLOR);
    default:
      return rgbToHex(0x000000);
  }
}

uint32_t getTileLightColor() { return rgbToHex(LIGHT_COLOR); }

uint32_t getTileDarkColor() { return rgbToHex(DARK_COLOR); }

void refreshTilesColor(Tiles* tiles) {
  uint8_t file = 0;
  uint8_t rank = 0;
  Tile* tile = nullptr;
  for (int i = 0; i < 64; i++) {
    tile = &tiles->getTiles()[i];

    if (tile->dev == nullptr) {
      // LOG_ERR("No device found for tile %d", i);
      continue;
    }

    file = tile->position.getFile();
    rank = tile->position.getRank();

    if ((file % 2) == (rank % 2)) {
      tiles->setTileColor(&tile->position, getTileDarkColor());
      // LOG_INF("Tile %d is dark", i);
    } else {
      tiles->setTileColor(&tile->position, getTileLightColor());
      // LOG_INF("Tile %d is light", i);
    }
  }
}