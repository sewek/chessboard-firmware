#include "chess.h"
#include "chess_log.h"

ChessPiece *Chess::findPiece(ChessPosition *position) {
  for (int i = 0; i < 32; ++i) {
    if (*this->piece[i].position == *position) {
      return &this->piece[i];
    }
  }
  return nullptr;
}

ChessPiece *Chess::findPiece(ChessPieceType type, ChessColor color) {
  for (int i = 0; i < 32; ++i) {
    if (this->piece[i].getType() == type &&
        this->piece[i].getColor() == color) {
      return &this->piece[i];
    }
  }
  return nullptr;
}

uint8_t Chess::findPieces(ChessPieceType type, ChessColor color,
                          ChessPiece *pieces) {
  uint8_t count = 0;
  for (int i = 0; i < 32; ++i) {
    if (this->piece[i].getType() == type &&
        this->piece[i].getColor() == color) {
      pieces[count++] = this->piece[i];
    }
  }
  return count;
}

// sprawdzenie czy na polu jest jakaś figura
int Chess::isOccupied(ChessPosition *position, ChessColor color) {
  ChessPiece *found = this->findPiece(position);

  if (found == nullptr) {
    return 0;
  }

  if (found->getColor() == color) {
    return 1;  // nasza figura
  }

  return -1;  // figura prezciwnika
}

// szach ten tego
bool Chess::isKingChecked(ChessColor color) {
  ChessPiece *king = this->findPiece(ChessPieceType::King, color);
  ChessPiece *oponent = nullptr;

  if (king == nullptr) {
    print_error("King not found\n");
    return false;  // błąd
  }

  if (king->getPosition() == nullptr) {
    print_error("King not on board\n");
    return false;  // błąd
  }

  ChessPosition positions[27];
  ChessPosition *currentPosition;
  uint8_t positionsCount = 0;
  for (int i = 0; i < 32; ++i) {
    oponent = &this->piece[i];

    if (oponent->getPosition() == nullptr || oponent->isOnBoard == false) {
      continue;
    }

    if (oponent->getColor() == color) {
      continue;
    }

    positionsCount = this->getAvailablePositions(oponent, positions, false);

    for (int j = 0; j < positionsCount; ++j) {
      currentPosition = &positions[j];

      if (*currentPosition == *king->getPosition()) {
        return true;  // szach
      }
    }
  }

  return false;  // nie szach
}

bool Chess::willBeKingChecked(ChessPosition *kingPosition, ChessColor color) {
  ChessPosition positions[27];
  ChessPiece *oponent;
  ChessPosition *currentPosition;
  uint8_t positionsCount = 0;
  for (int i = 0; i < 32; ++i) {
    oponent = &this->piece[i];

    if (oponent->getColor() == color) {
      continue;
    }

    positionsCount = this->getAvailablePositions(oponent, positions);
    for (int j = 0; j < positionsCount; ++j) {
      currentPosition = &positions[i];

      if (currentPosition == kingPosition) {
        return true;  // szach
      }
    }
  }

  return false;  // nie szach
}

bool Chess::isKingCheckmate(ChessColor color) {
  ChessPiece *king = this->findPiece(ChessPieceType::King, color);
  ChessPosition positions[27];
  ChessPosition *currentPosition;
  uint8_t positionsCount = 0;
  for (int i = 0; i < 32; ++i) {
    ChessPiece *piece = &this->piece[i];

    if (piece->getColor() != color) {
      continue;
    }

    positionsCount = this->getAvailablePositions(piece, positions);
    for (int j = 0; j < positionsCount; ++j) {
      currentPosition = &positions[j];

      if (this->willBeKingChecked(currentPosition, color) == false) {
        return false;  // nie mat
      }
    }
  }

  return true;  // mat
}
// sprawdzenie czy jest pat
bool Chess::isStalemate(ChessColor color) {
  ChessPiece *ourpiece = nullptr;

  ChessPosition positions[27];
  ChessPosition *currentPosition;
  uint8_t positionsCount = 0;
  for (int i = 0; i < 32; ++i) {
    ourpiece = &this->piece[i];

    if (ourpiece->getPosition() == nullptr || ourpiece->isOnBoard == false) {
      continue;
    }

    if (ourpiece->getColor() != color) {
      continue;
    }

    positionsCount = this->getAvailablePositions(ourpiece, positions, false);

    if (positionsCount > 0) {
      return false;  // nie pat
    }
  }

  return true;  // pat
}

// sprawdzenie czy jest możliwy mat -> 2 gońce na tym samym kolorze, skoczek i
// król, goniec i król, krl i krl
bool Chess::isMatPossible() {
  uint8_t onBoardCount = 0;
  for (int i = 0; i < 32; ++i) {
    if (this->piece[i].isOnBoard) {
      onBoardCount++;
    }
  }

  if (onBoardCount == 2) {
    return false;
  }

  if (onBoardCount == 3 &&
      (this->findPiece(ChessPieceType::Knight, ChessColor::White)->isOnBoard ==
           true ||
       this->findPiece(ChessPieceType::Knight, ChessColor::Black)->isOnBoard ==
           true)) {
    return false;
  }

  if (onBoardCount == 3 &&
      (this->findPiece(ChessPieceType::Bishop, ChessColor::White)->isOnBoard ==
           true ||
       this->findPiece(ChessPieceType::Bishop, ChessColor::Black)->isOnBoard ==
           true)) {
    return false;
  }

  if (onBoardCount == 4 && this->piece[2].isOnBoard &&
      this->piece[21].isOnBoard) {
    return false;
  }

  if (onBoardCount == 4 && this->piece[19].isOnBoard &&
      this->piece[21].isOnBoard) {
    return false;
  }

  return true;
}

ChessColor Chess::getCurrentPlayerColor() {
  if (this->move_index == 0) {
    return ChessColor::White;
  }

  if (this->move_index % 2 == 0) {
    return ChessColor::White;
  }

  return ChessColor::Black;
}

bool Chess::isCastlingPossible(ChessCastlingType type, ChessColor color) {
  ChessPiece *king = this->findPiece(ChessPieceType::King, color);
  ChessPiece rocks[2];
  ChessPiece *shortRook = nullptr;
  ChessPiece *longRook = nullptr;
  ChessPiece *rook = nullptr;
  ChessPosition *kingPosition = king->getPosition();
  ChessPosition *rookPosition = nullptr;
  ChessPosition tempPosition = ChessPosition(0, 0);
  uint8_t rocksCount = 0;
  int isOccupied = 0;

  if (king == nullptr) {
    return false;
  }

  if (king->hasMoved()) {
    return false;
  }

  if (this->isKingChecked(color)) {
    return false;
  }

  rocksCount = this->findPieces(ChessPieceType::Rook, color, rocks);
  for (int i = 0; i < rocksCount; ++i) {
    rook = &rocks[i];
    rookPosition = rook->getPosition();

    if (rookPosition == nullptr) {
      continue;
    }

    if (rookPosition->getFile() == 1) {
      longRook = rook;
    } else if (rookPosition->getFile() == 8) {
      shortRook = rook;
    }
  }

  if (type == ChessCastlingType::Short) {
    if (shortRook == nullptr) {
      return false;
    }

    if (shortRook->hasMoved()) {
      return false;
    }

    for (int i = 1; i < 3; ++i) {
      tempPosition =
          ChessPosition(kingPosition->getFile() + i, kingPosition->getRank());

      if (this->willBeKingChecked(&tempPosition, color)) {
        return false;
      }

      if (i == 2) {
        continue;
      }

      isOccupied = this->isOccupied(&tempPosition, color);
      if (isOccupied != 0) {
        return false;
      }
    }
  }

  if (type == ChessCastlingType::Long) {
    if (longRook == nullptr) {
      return false;
    }

    if (longRook->hasMoved()) {
      return false;
    }

    for (int i = 1; i < 4; ++i) {
      tempPosition =
          ChessPosition(kingPosition->getFile() - i, kingPosition->getRank());

      if (this->willBeKingChecked(&tempPosition, color)) {
        return false;
      }

      if (i == 3) {
        continue;
      }

      isOccupied = this->isOccupied(&tempPosition, color);
      if (isOccupied != 0) {
        return false;
      }
    }
  }

  return false;
}

void Chess::createMove(ChessMove *move, ChessPosition *from,
                       ChessPosition *to) {
  print_debug("Creating move\n");
  if (move == nullptr) {
    print_error("Move is null\n");
    return;
  }

  ChessPiece *piece = this->findPiece(from);
  ChessPiece *oponent = this->findPiece(to);

  if (oponent != nullptr) {
    print_debug("Found oponent piece %d %s\n", oponent->getType(),
                oponent->getColor() == ChessColor::White ? "white" : "black");
  }

  move->setFrom(from);
  move->setTo(to);
  move->setPiece(piece);
  move->setType(ChessMoveType::Normal);
  this->movesFor75Rule++;

  if (piece->getType() == ChessPieceType::Pawn) {
    this->movesFor75Rule = 0;
  }

  if (oponent != nullptr) {
    move->setType(ChessMoveType::Capture);
    this->movesFor75Rule = 0;
  }

  if (this->piece->getType() == ChessPieceType::Pawn &&
      (this->piece->getPosition()->getRank() == 1 ||
       this->piece->getPosition()->getRank() == 8)) {
    move->setType(ChessMoveType::Promotion);
    pawnPromotion(piece->getPosition());
  }
}

void Chess::applyMove(ChessMove *move) {
  print_debug("Applying move\n");
  ChessPiece *piece = this->findPiece(move->getFrom());
  ChessPiece *oponent = this->findPiece(move->getTo());

  if (oponent != nullptr) {
    oponent->setPosition(nullptr);
    print_debug("Captured piece\n");
  }

  print_debug("Moving piece from %d %d to %d %d\n", move->getFrom()->getRank(),
              move->getFrom()->getFile(), move->getTo()->getRank(),
              move->getTo()->getFile());

  piece->setPosition(move->getTo());
  piece->setLastMove(move);

  this->move_index++;
}

ChessPosition *Chess::getPosition(const char *position) {
  uint8_t file = position[0] - 'a';
  uint8_t rank = position[1] - '1';

  if (file < 0 || file > 7 || rank < 0 || rank > 7) {
    return nullptr;
  }

  return &this->position[file][rank];
}

void Chess::pawnPromotion(ChessPosition *position) {
  ChessPiece *piece = this->findPiece(position);
  if (piece == nullptr) {
    return;
  }

  if (piece->getType() != ChessPieceType::Pawn) {
    return;
  }

  if (piece->getColor() == ChessColor::White && position->getRank() != 8) {
    return;
  }

  if (piece->getColor() == ChessColor::Black && position->getRank() != 1) {
    return;
  }

  // TODO: Add pawn promotion request and wait for user input
}
