#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "chess_move.h"
#include "chess_position.h"
#include "chess_types.h"

class ChessPiece {
 public:
  ChessPosition *position = nullptr;
  ChessMove *lastMove = nullptr;
  ChessColor color;
  ChessPieceType type;
  bool isOnBoard = true;

  ChessPiece(ChessColor color, ChessPosition *position,
             ChessPieceType pieceType);
  ChessPiece() = default;
  ~ChessPiece() = default;
};

#endif  // CHESS_PIECE_H
