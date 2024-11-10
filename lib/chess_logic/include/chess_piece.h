#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "chess_move.h"
#include "chess_position.h"
#include "chess_types.h"

class ChessMove;

class ChessPiece {
 public:
  ChessPosition *position = nullptr;
  ChessMove *lastMove = nullptr;
  ChessColor color;
  ChessPieceType type;
  bool isOnBoard = true;

  ChessPiece(ChessColor color, ChessPosition *position,
             ChessPieceType pieceType);
  ChessPiece(ChessColor color, ChessPieceType pieceType);
  ChessPiece() = default;
  ~ChessPiece() = default;

  bool hasMoved() { return this->lastMove != nullptr; }

  ChessPosition *getPosition() { return this->position; }
  ChessMove *getLastMove() { return this->lastMove; }
  ChessColor getColor() { return this->color; }
  ChessPieceType getType() { return this->type; }

  void setPosition(ChessPosition *position) { this->position = position; }
  void setLastMove(ChessMove *move) { this->lastMove = move; }
  void setColor(ChessColor color) { this->color = color; }
  void setType(ChessPieceType type) { this->type = type; }
};

#endif  // CHESS_PIECE_H
