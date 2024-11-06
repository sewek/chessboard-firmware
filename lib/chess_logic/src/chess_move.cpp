/**
 * @file chess_move.cpp
 * @brief Represents a move in a chess game.
 */

#include "chess_move.h"

#include <string.h>

ChessMove::ChessMove(ChessPosition* from, ChessPosition* to)
    : from_(from),
      to_(to),
      piece_(ChessPieceType::Pawn),
      type_(ChessMoveType::Normal) {}

ChessMove::ChessMove(ChessPosition* from, ChessPosition* to,
                     ChessPieceType piece)
    : from_(from), to_(to), piece_(piece), type_(ChessMoveType::Normal) {}

ChessMove::ChessMove(ChessPosition* from, ChessPosition* to,
                     ChessPieceType piece, ChessMoveType type)
    : from_(from), to_(to), piece_(piece), type_(type) {}

ChessPosition* ChessMove::getFrom() const { return from_; }

ChessPosition* ChessMove::getTo() const { return to_; }

ChessPieceType ChessMove::getPiece() const { return piece_; }

ChessMoveType ChessMove::getType() const { return type_; }

bool ChessMove::isValid() const {
  return from_->isValid() && to_->isValid() && from_ != to_;
}

uint8_t ChessMove::toString(char* buff) const {
  char from[2];
  char to[2];
  char piece = ' ';
  char type = ' ';

  from_->toString(from);
  to_->toString(to);

  switch (piece_) {
    case ChessPieceType::Pawn:
      piece = 'P';
      break;
    case ChessPieceType::Knight:
      piece = 'N';
      break;
    case ChessPieceType::Bishop:
      piece = 'B';
      break;
    case ChessPieceType::Rook:
      piece = 'R';
      break;
    case ChessPieceType::Queen:
      piece = 'Q';
      break;
    case ChessPieceType::King:
      piece = 'K';
      break;
  }

  switch (type_) {
    case ChessMoveType::Normal:
      type = ' ';
      break;
    case ChessMoveType::Capture:
      type = 'x';
      break;
    case ChessMoveType::Castling:
      type = 'O';
      break;
    case ChessMoveType::Check:
      type = '+';
      break;
    case ChessMoveType::Checkmate:
      type = '#';
      break;
    case ChessMoveType::Promotion:
      type = '=';
      break;
    case ChessMoveType::EnPassant:
      type = 'e';
      break;
  }

  if (type_ == ChessMoveType::Castling) {
    if (from_->getFile() - to_->getFile() > 2) {
      buff[0] = 'O';
      buff[1] = '-';
      buff[2] = 'O';
      buff[3] = '-';
      buff[4] = 'O';
      return 5;
    }

    buff[0] = 'O';
    buff[1] = '-';
    buff[2] = 'O';
    return 3;
  }

  if (type_ == ChessMoveType::Promotion) {
    buff[0] = from[0];
    buff[1] = from[1];
    buff[2] = to[0];
    buff[3] = to[1];
    buff[4] = type;
    buff[5] = piece;
    return 6;
  }

  if (type_ == ChessMoveType::Normal) {
    buff[0] = piece;
    buff[1] = from[0];
    buff[2] = from[1];
    buff[3] = to[0];
    buff[4] = to[1];
    return 6;
  }

  buff[0] = piece;
  buff[1] = from[0];
  buff[2] = from[1];
  buff[3] = type;
  buff[4] = to[0];
  buff[5] = to[1];
  return 6;
}

bool ChessMove::operator==(const ChessMove& other) const {
  return from_ == other.from_ && to_ == other.to_ && piece_ == other.piece_ &&
         type_ == other.type_;
}

bool ChessMove::operator!=(const ChessMove& other) const {
  return !(*this == other);
}
