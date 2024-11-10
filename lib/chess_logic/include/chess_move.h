/**
 * @file chess_move.h
 * @brief Represents a move in a chess game.
 */

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <inttypes.h>

#include "chess_piece.h"
#include "chess_position.h"
#include "chess_types.h"

class ChessPiece;

/**
 * @brief Represents a move in a chess game.
 */
class ChessMove {
 public:
  ChessMove() = default;
  /**
   * @brief Construct a new ChessMove object.
   *
   * @param from The position the move is from.
   * @param to The position the move is to.
   */
  ChessMove(ChessPosition* from, ChessPosition* to);

  /**
   * @brief Construct a new ChessMove object.
   *
   * @param from The position the move is from.
   * @param to The position the move is to.
   * @param piece The piece type of the move.
   */
  ChessMove(ChessPosition* from, ChessPosition* to, ChessPiece* piece);

  /**
   * @brief Construct a new ChessMove object.
   *
   * @param from The position the move is from.
   * @param to The position the move is to.
   * @param piece The piece type of the move.
   * @param type The type of the move.
   */
  ChessMove(ChessPosition* from, ChessPosition* to, ChessPiece* piece,
            ChessMoveType type);

  /**
   * @brief Get the position the move is from.
   *
   * @return The position the move is from.
   */
  ChessPosition* getFrom() const;

  /**
   * @brief Get the position the move is to.
   *
   * @return The position the move is to.
   */
  ChessPosition* getTo() const;

  /**
   * @brief Get the piece type of the move.
   *
   * @return The piece type of the move.
   */
  ChessPiece* getPiece() const;

  /**
   * @brief Get the type of the move.
   *
   * @return The type of the move.
   */
  ChessMoveType getType() const;

  /**
   * @brief Set the position the move is from.
   */
  void setFrom(ChessPosition* from) { from_ = from; }

  /**
   * @brief Set the position the move is to.
   */
  void setTo(ChessPosition* to) { to_ = to; }

  /**
   * @brief Set the piece type of the move.
   */
  void setPiece(ChessPiece* piece) { piece_ = piece; }

  /**
   * @brief Set the type of the move.
   */
  void setType(ChessMoveType type) { type_ = type; }

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
  uint8_t toString(char* buff) const;

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
  ChessPosition* from_;
  ChessPosition* to_;
  ChessPiece* piece_;
  ChessMoveType type_;
};

#endif  // CHESS_MOVE_H
