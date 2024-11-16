/**
 * @file chess_position.cpp
 *
 * Implementation of the ChessPosition class.
 */

#include "chess_position.h"

ChessPosition::ChessPosition(const char file, int rank) {
  if ((file < 'a' || file > 'h') && (rank < 1 || rank > 8)) {
    this->data_ = 0;
    return;
  }

  if (rank < 1 || rank > 8) {
    this->data_ = 0;
    return;
  }

  if (file >= 'a' && file <= 'h') {
    this->data_ = (((file - 'a' + 1) & 0x0f) << 4) | (rank & 0x0f);
  } else {
    this->data_ = ((file & 0x0f) << 4) | (rank & 0x0f);
  }
}

ChessPosition::ChessPosition(const char* position) {
  const char file = position[0];
  const char rank = position[1];

  if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
    this->data_ = 0;
    return;
  }

  this->data_ = ((file - 'a' + 1) << 4) | (rank - '1' + 1);
}

ChessPosition::ChessPosition(uint8_t data) { this->data_ = data; }

uint8_t ChessPosition::getFile() const { return (this->data_ >> 4) & 0x0f; }

uint8_t ChessPosition::getRank() const { return this->data_ & 0x0f; }

bool ChessPosition::isValid() const {
  return (this->data_ & 0xf0) && (this->data_ & 0x0f);
}

uint8_t ChessPosition::toData() const { return this->data_; }

uint8_t ChessPosition::toString(char* buff) const {
  if (!this->isValid()) {
    return 0;
  }

  buff[0] = 'a' + this->getFile() - 1;
  buff[1] = '1' + this->getRank() - 1;

  return 2;
}

bool ChessPosition::operator==(const ChessPosition& other) const {
  return this->data_ == other.data_;
}

bool ChessPosition::operator!=(const ChessPosition& other) const {
  return this->data_ != other.data_;
}

ChessPosition ChessPosition::operator+(const ChessPosition& other) const {
  return ChessPosition(((this->getFile() + other.getFile()) << 4) |
                       (this->getRank() + other.getRank()));
}

ChessPosition ChessPosition::operator-(const ChessPosition& other) const {
  return ChessPosition(((this->getFile() - other.getFile()) << 4) |
                       (this->getRank() - other.getRank()));
}

ChessPosition ChessPosition::fromData(uint8_t data) {
  return ChessPosition(data);
}

ChessPosition ChessPosition::fromString(char* position) {
  return ChessPosition(position);
}
