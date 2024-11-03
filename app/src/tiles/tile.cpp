/**
 * @file tile.cpp
 * @brief Chessboard Tile representation
 */

#include <tile.h>

Tile::Tile() {
  this->position = ChessPosition(0, 0);
  this->color = 0;
  this->state = 0;
  this->dev = nullptr;
  this->channel = 0;
}

Tile::Tile(ChessPosition *position, uint32_t color, uint8_t state,
           struct device *dev, uint8_t channel) {
  this->position = ChessPosition(position->toData());
  this->color = color;
  this->state = state;
  this->dev = dev;
  this->channel = channel;
}

Tile::~Tile() {
  this->position = ChessPosition(0, 0);
  this->color = 0;
  this->state = 0;
  this->dev = nullptr;
  this->channel = 0;
}
