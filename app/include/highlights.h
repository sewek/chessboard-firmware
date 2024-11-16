#ifndef HIGHLIGHTS_H
#define HIGHLIGHTS_H

#include <chess_types.h>

#include "tiles.h"

#define NORMAL_MOVE_COLOR 0xbadc58
#define CAPTURE_MOVE_COLOR 0xc0392b
#define CHECK_COLOR 0xf1c40f
#define INFO_COLOR 0x9b59b6
#define ERROR_COLOR 0x9b59b6

#define LIGHT_COLOR 0x000000
#define DARK_COLOR 0x3498db

uint32_t rgbToHex(uint32_t rgb);

uint32_t getColor(ChessHighlightType type);

uint32_t getTileLightColor();

uint32_t getTileDarkColor();

void refreshTilesColor(Tiles* tiles);

void refreshTileColor(Tiles* tiles, ChessPosition* position);

#endif  // HIGHLIGHTS_H