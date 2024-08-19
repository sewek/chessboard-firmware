/**
 * @file chess_move.cpp
 * @brief Represents a move in a chess game.
 */

#include "chess_move.h"

ChessMove::ChessMove(ChessPosition from, ChessPosition to)
    : from_(from),
      to_(to),
      piece_(ChessPieceType::Pawn),
      type_(ChessMoveType::Normal) {}

ChessMove::ChessMove(ChessPosition from, ChessPosition to, ChessPieceType piece)
    : from_(from), to_(to), piece_(piece), type_(ChessMoveType::Normal) {}

ChessMove::ChessMove(ChessPosition from, ChessPosition to, ChessPieceType piece,
                     ChessMoveType type)
    : from_(from), to_(to), piece_(piece), type_(type) {}

ChessPosition ChessMove::getFrom() const { return from_; }

ChessPosition ChessMove::getTo() const { return to_; }

ChessPieceType ChessMove::getPiece() const { return piece_; }

ChessMoveType ChessMove::getType() const { return type_; }

bool ChessMove::isValid() const {
  return from_.isValid() && to_.isValid() && from_ != to_;
}

std::string ChessMove::toString() const {
  std::string from = from_.toString();
  std::string to = to_.toString();
  char piece = ' ';
  char type = ' ';

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
    if (from_.getFile() - to_.getFile() > 2) {
      return "O-O-O";
    }

    return "O-O";
  }

  if (type_ == ChessMoveType::Promotion) {
    return from + to + type + piece;
  }

  if (type_ == ChessMoveType::Normal) {
    return piece + from + to;
  }

  return piece + from + type + to;
}

bool ChessMove::operator==(const ChessMove& other) const {
  return from_ == other.from_ && to_ == other.to_ && piece_ == other.piece_ &&
         type_ == other.type_;
}

bool ChessMove::operator!=(const ChessMove& other) const {
  return !(*this == other);
}
