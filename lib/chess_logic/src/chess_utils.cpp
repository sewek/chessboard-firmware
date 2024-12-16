#include "chess.h"
#include "chess_log.h"

#ifdef CHESS_ZEPHYR_LOG
LOG_MODULE_REGISTER(chess_utils, LOG_LEVEL_DBG);
#endif

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

  if (king == nullptr) {
    return false;  // błąd
  }

  if (king->getPosition() == nullptr) {
    return false;  // błąd
  }

  ChessPiece *oponent = nullptr;
  ChessPosition positions[27];
  ChessPosition *kingPosition = king->getPosition();
  ChessPosition *currentPosition;
  uint8_t positionsCount = 0;
  for (int i = 0; i < 32; ++i) {
    oponent = &this->piece[i];

    if (oponent == nullptr) {
      print_error("Oponent not found\n");
      continue;
    }

    if (oponent->getPosition() == nullptr) {
      continue;
    }

    if (!oponent->isOnBoard) {
      continue;
    }

    if (oponent->getColor() == color) {
      continue;
    }

    if (oponent->getType() == ChessPieceType::King) {
      positionsCount = this->getKingAvailablePositions(oponent, positions);
      for (int j = 0; j < positionsCount; ++j) {
        currentPosition = &positions[j];

        if (*currentPosition == *kingPosition) {
          return true;  // szach od króla przeciwnika
        }
      }
      continue;
    }

    positionsCount = this->getAvailablePositions(oponent, positions);

    for (int j = 0; j < positionsCount; ++j) {
      currentPosition = &positions[j];

      if (*currentPosition == *kingPosition) {
        return true;  // szach
      }
    }
  }

  return false;  // nie szach
}

bool Chess::willBeKingChecked(ChessPosition *kingPosition, ChessColor color) {
  ChessPiece *oponentKing = this->findPiece(
      ChessPieceType::King,
      color == ChessColor::White ? ChessColor::Black : ChessColor::White);
  ChessPosition positions[27];
  ChessPiece *oponent;
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

    if (oponent->getType() == ChessPieceType::King) {
      positionsCount = this->getKingAvailablePositions(oponentKing, positions);
      for (int j = 0; j < positionsCount; ++j) {
        currentPosition = &positions[j];

        if (*currentPosition == *kingPosition) {
          return true;  // szach od króla przeciwnika
        }
      }
      continue;
    }

    positionsCount = this->getAvailablePositions(oponent, positions);
    positionsCount =
        this->filterAvailablePositions(positions, positionsCount, oponent);
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
    positionsCount =
        this->filterAvailablePositions(positions, positionsCount, piece);
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

    positionsCount = this->getAvailablePositions(ourpiece, positions);

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
    print_debug("King has moved\n");
    return false;
  }

  if (this->isKingChecked(color)) {
    print_debug("King is checked\n");
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
      print_debug("Long rook found\n");
    } else if (rookPosition->getFile() == 8) {
      shortRook = rook;
      print_debug("Short rook found\n");
    }
  }

  if (type == ChessCastlingType::Short) {
    print_debug("Checking short castling\n");
    if (shortRook == nullptr) {
      print_debug("Short rook not found\n");
      return false;
    }

    if (shortRook->hasMoved()) {
      print_debug("Short rook has moved\n");
      return false;
    }

    for (int i = 1; i < 4; ++i) {
      tempPosition =
          ChessPosition(kingPosition->getFile() + i, kingPosition->getRank());

      if (this->willBeKingChecked(&tempPosition, color)) {
        print_debug("King will be checked in %d iteration (%d %d position)\n",
                    i, tempPosition.getFile(), tempPosition.getRank());
        return false;
      }

      if (i == 3) {
        continue;
      }

      isOccupied = this->isOccupied(&tempPosition, color);
      if (isOccupied != 0) {
        print_debug("Position %d %d is occupied\n", tempPosition.getFile(),
                    tempPosition.getRank());
        return false;
      }
    }
  }

  if (type == ChessCastlingType::Long) {
    if (longRook == nullptr) {
      print_debug("Long rook not found\n");
      return false;
    }

    if (longRook->hasMoved()) {
      print_debug("Long rook has moved\n");
      return false;
    }

    for (int i = 1; i < 5; ++i) {
      tempPosition =
          ChessPosition(kingPosition->getFile() - i, kingPosition->getRank());

      if (this->willBeKingChecked(&tempPosition, color)) {
        print_debug("King will be checked in %d iteration (%d %d position)\n",
                    i, tempPosition.getFile(), tempPosition.getRank());
        return false;
      }

      if (i == 4) {
        continue;
      }

      isOccupied = this->isOccupied(&tempPosition, color);
      if (isOccupied != 0) {
        print_debug("Position %d %d is occupied\n", tempPosition.getFile(),
                    tempPosition.getRank());
        return false;
      }
    }
  }

  return true;
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
    print_debug("Found oponent piece %d %s\n", (int)oponent->getType(),
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

  if (piece->getType() == ChessPieceType::Pawn && oponent == nullptr &&
      from->getFile() != to->getFile()) {
    move->setType(ChessMoveType::EnPassant);
    ChessColor color = piece->getColor();
    this->enPassantPosition =
        &this->position[to->getFile() - 1]
                       [to->getRank() - 1 +
                        (color == ChessColor::White ? -1 : 1)];
  }

  if (piece->getType() == ChessPieceType::Pawn &&
      (to->getRank() == 1 || to->getRank() == 8)) {
    move->setType(ChessMoveType::Promotion);
    pawnPromotion(piece->getPosition());
  }

  if (piece->getType() == ChessPieceType::King &&
      (from->getFile() - to->getFile() == 2 ||
       to->getFile() - from->getFile() == 2)) {
    move->setType(ChessMoveType::Castling);
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

  if (move->getType() == ChessMoveType::Castling) {
    ChessPiece *rook = nullptr;
    ChessPosition *rookPosition = nullptr;
    ChessPosition *kingPosition = piece->getPosition();
    ChessPosition *tempPosition = nullptr;

    if (kingPosition->getFile() == 7) {
      tempPosition = &this->position[7][kingPosition->getRank() - 1];
    } else if (kingPosition->getFile() == 3) {
      tempPosition = &this->position[0][kingPosition->getRank() - 1];
    } else {
      print_error("Invalid castling move\n");
      return;
    }

    rook = this->findPiece(tempPosition);

    if (kingPosition->getFile() == 7) {
      rookPosition = &this->position[5][kingPosition->getRank() - 1];
    } else if (kingPosition->getFile() == 3) {
      rookPosition = &this->position[3][kingPosition->getRank() - 1];
    } else {
      print_error("Invalid castling move\n");
      return;
    }

    this->castlingRookPosition = rook->getPosition();
    rook->setPosition(rookPosition);
    this->castlingRook = rook;
  }

  /* if (move->getType() == ChessMoveType::Capture ||
      move->getType() == ChessMoveType::Promotion ||
      move->getType() == ChessMoveType::Castling ||
      piece->getType() == ChessPieceType::Pawn ||
      (piece->getType() == ChessPieceType::Rook && !piece->hasMoved()) ||
      (piece->getType() == ChessPieceType::King && !piece->hasMoved())) {
    this->clearRepeatedPositions();
  }

  bool isPotentialEnPassant =
      (move->getType() == ChessMoveType::Normal &&
       piece->getType() == ChessPieceType::Pawn &&
       (move->getFrom()->getRank() - move->getTo()->getRank() == 2 ||
        move->getTo()->getRank() - move->getFrom()->getRank() == 2));

  if (isPotentialEnPassant) {
    ChessPosition leftPosition =
        ChessPosition(move->getTo()->getFile() - 1, move->getTo()->getRank());
    ChessPosition rightPosition =
        ChessPosition(move->getTo()->getFile() + 1, move->getTo()->getRank());
    ChessPiece *pieceAtLeft = this->findPiece(&leftPosition);
    ChessPiece *pieceAtRight = this->findPiece(&rightPosition);

    bool oponentAtLeft = pieceAtLeft != nullptr &&
                         pieceAtLeft->getColor() != piece->getColor() &&
                         pieceAtLeft->getType() == ChessPieceType::Pawn;
    bool oponentAtRight = pieceAtRight != nullptr &&
                          pieceAtRight->getColor() != piece->getColor() &&
                          pieceAtRight->getType() == ChessPieceType::Pawn;

    if (!oponentAtLeft && !oponentAtRight) {
      isPotentialEnPassant = false;
    }
  }

  if (!isPotentialEnPassant) {
    this->saveRepeatedPosition();
  } */
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

void Chess::clear() {
  this->whiteWrongMoves = 0;
  this->blackWrongMoves = 0;
  this->lastWrongMoveWhite = -1;
  this->lastWrongMoveBlack = -1;
  this->move_index = 0;
  this->positionsToExcludeFromWrongMovesCount = 0;
  this->castlingRook = nullptr;
  this->castlingRookPosition = nullptr;
  this->enPassantPosition = nullptr;
  this->shouldWaitForTimmer = shouldWaitForTimmer;
}