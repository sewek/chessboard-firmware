#include "chess_piece.h"

ChessPiece::ChessPiece(ChessColor color, ChessPosition *position,
                       ChessPieceType pieceType) {
  this->position = position;
  this->color = color;
  this->type = pieceType;
}
