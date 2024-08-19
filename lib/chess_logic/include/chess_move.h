/**
 * @file chess_move.h
 * @brief Represents a move in a chess game.
 */

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <inttypes.h>

#include <string>

#include "chess_position.h"
#include "chess_types.h"

/**
 * @brief Represents a move in a chess game.
 */
class ChessMove {
 public:
  /**
   * @brief Construct a new ChessMove object.
   *
   * @param from The position the move is from.
   * @param to The position the move is to.
   */
  ChessMove(ChessPosition from, ChessPosition to);

  /**
   * @brief Construct a new ChessMove object.
   *
   * @param from The position the move is from.
   * @param to The position the move is to.
   * @param piece The piece type of the move.
   */
  ChessMove(ChessPosition from, ChessPosition to, ChessPieceType piece);

  /**
   * @brief Construct a new ChessMove object.
   *
   * @param from The position the move is from.
   * @param to The position the move is to.
   * @param piece The piece type of the move.
   * @param type The type of the move.
   */
  ChessMove(ChessPosition from, ChessPosition to, ChessPieceType piece,
            ChessMoveType type);

  /**
   * @brief Get the position the move is from.
   *
   * @return The position the move is from.
   */
  ChessPosition getFrom() const;

  /**
   * @brief Get the position the move is to.
   *
   * @return The position the move is to.
   */
  ChessPosition getTo() const;

  /**
   * @brief Get the piece type of the move.
   *
   * @return The piece type of the move.
   */
  ChessPieceType getPiece() const;

  /**
   * @brief Get the type of the move.
   *
   * @return The type of the move.
   */
  ChessMoveType getType() const;

  /**
   * @brief Check if the move is valid.
   *
   * @return True if the move is valid, false otherwise.
   */
  bool isValid() const;

  /**
   * @brief Get the move in algebraic notation.
   *
   * @return The move in algebraic notation.
   */
  std::string toString() const;

  /**
   * @brief Check if two moves are equal.
   *
   * @param other The move to compare to.
   */
  bool operator==(const ChessMove& other) const;

  /**
   * @brief Check if two moves are not equal.
   *
   * @param other The move to compare to.
   */
  bool operator!=(const ChessMove& other) const;

 private:
  ChessPosition from_;
  ChessPosition to_;
  ChessPieceType piece_;
  ChessMoveType type_;
};

#endif  // CHESS_MOVE_H
