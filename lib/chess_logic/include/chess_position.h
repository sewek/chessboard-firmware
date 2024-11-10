/**
 * @file chess_position.h
 * @brief Defines the position of a chess piece on the board.
 */

#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H

#include <inttypes.h>

#include "chess_types.h"

/**
 * @brief Represents the position of a chess piece on the board.
 */
class ChessPosition {
 public:
  /**
   * @brief Construct a new ChessPosition object.
   */
  ChessPosition() = default;

  /**
   * @brief Construct a new ChessPosition object.
   *
   * @param file The file of the position.
   * @param rank The rank of the position.
   */
  ChessPosition(const char file, int rank);

  /**
   * @brief Construct a new ChessPosition object.
   *
   * @param position The position in algebraic notation.
   */
  explicit ChessPosition(const char* position);

  /**
   * @brief Construct a new ChessPosition object.
   *
   * @param data The data of the position.
   */
  explicit ChessPosition(uint8_t data);

  /**
   * @brief Get the file of the position.
   *
   * @return The file of the position.
   */
  uint8_t getFile() const;

  /**
   * @brief Get the rank of the position.
   *
   * @return The rank of the position.
   */
  uint8_t getRank() const;

  /**
   * @brief Check if the position is valid.
   *
   * @return True if the position is valid, false otherwise.
   */
  bool isValid() const;

  /**
   * @brief Get the data of the position.
   *
   * @return The data of the position.
   */
  uint8_t toData() const;

  /**
   * @brief Get the position in algebraic notation.
   *
   * @return The position in algebraic notation.
   */
  uint8_t toString(char* buff) const;

  /**
   * @brief Check if two positions are equal.
   *
   * @param other The other position to compare to.
   * @return True if the positions are equal, false otherwise.
   */
  bool operator==(const ChessPosition& other) const;

  /**
   * @brief Check if two positions are not equal.
   *
   * @param other The other position to compare to.
   * @return True if the positions are not equal, false otherwise.
   */
  bool operator!=(const ChessPosition& other) const;

  /**
   * @brief Sum two positions.
   *
   * @param other The other position to sum to.
   * @return The sum of the two positions.
   */
  ChessPosition operator+(const ChessPosition& other) const;

  /**
   * @brief Subtract two positions.
   *
   * @param other The other position to subtract from.
   * @return The difference of the two positions.
   */
  ChessPosition operator-(const ChessPosition& other) const;

  /**
   * @brief Get the position from the given data.
   *
   * @param data The data of the position.
   * @return The position from the given data.
   */
  static ChessPosition fromData(uint8_t data);

  /**
   * @brief Get the position from the given algebraic notation.
   *
   * @param position The position in algebraic notation.
   * @return The position from the given algebraic notation.
   */
  static ChessPosition fromString(char* position);

 private:
  uint8_t data_;
};

#endif  // CHESS_POSITION_H
