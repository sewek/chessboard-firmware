/**
 * @file tile.h
 * @brief Chessboard Tile representation
 */

#ifndef TILE_H
#define TILE_H

#include <chess_position.h>
#include <inttypes.h>
#include <zephyr/device.h>

/**
 * @brief Representation of single chessboard tile with its position, current
 * color and state
 */
class Tile {
 public:
  ChessPosition position = ChessPosition(0, 0);
  uint32_t color;
  uint8_t state;
  struct device *dev;
  uint8_t channel;

  Tile();
  Tile(ChessPosition *position, uint32_t color, uint8_t state,
       struct device *dev, uint8_t channel);
  ~Tile();
};

#endif  // TILE_H
