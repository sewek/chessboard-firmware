#include "chess.h"
#include "chess_log.h"

#ifdef CHESS_ZEPHYR_LOG
LOG_MODULE_REGISTER(chess_logic, LOG_LEVEL_DBG);
#endif

static void removePosition(ChessPosition *array, uint8_t *count,
                           uint8_t index) {
  for (uint8_t i = index; i < *count - 1; ++i) {
    array[i] = array[i + 1];
  }
  (*count)--;
}

// moliwe ruchy figur
uint8_t Chess::getAvailablePositions(ChessPiece *piece,
                                     ChessPosition *chessPositions) {
  // print_debug("Getting available positions\n");
  uint8_t count = 0;
  ChessPosition *position = piece->getPosition();
  ChessPosition tempPosition = ChessPosition(0, 0);  // tymczasowa zmienna
  int isOccupied = 0;

  switch (piece->getType()) {
    case ChessPieceType::Pawn: {
      int site;
      if (piece->getColor() == ChessColor::White) {
        site = 1;
      } else {
        site = -1;
      }

      // pioneczki do przodu o 1 i o 2 pyk pyk
      tempPosition =
          ChessPosition(position->getFile(), position->getRank() + site);
      isOccupied = this->isOccupied(&tempPosition, piece->getColor());
      if (isOccupied == 0) {
        chessPositions[count++] = tempPosition;
        if ((piece->getColor() == ChessColor::White &&
             position->getRank() == 2) ||
            (piece->getColor() == ChessColor::Black &&
             position->getRank() == 7)) {
          tempPosition = ChessPosition(position->getFile(),
                                       position->getRank() + 2 * site);
          isOccupied = this->isOccupied(&tempPosition, piece->getColor());
          if (isOccupied == 0) {
            chessPositions[count++] = tempPosition;
          }
        }
      }

      // tu bicie w obie strony
      if (position->getFile() > 1) {
        tempPosition =
            ChessPosition(position->getFile() - 1, position->getRank() + site);
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());
        if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
        }
      }

      if (position->getFile() < 7) {
        tempPosition =
            ChessPosition(position->getFile() + 1, position->getRank() + site);
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());
        if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
        }
      }

      // en pasant tutaj
      if (this->move_index > 0) {
        ChessMove *lastMove = &this->move[this->move_index - 1];
        uint8_t lastMoveFromRank = lastMove->getFrom()->getRank();
        uint8_t lastMoveToRank = lastMove->getTo()->getRank();
        uint8_t lastMoveRankDelta = lastMoveFromRank > lastMoveToRank
                                        ? lastMoveFromRank - lastMoveToRank
                                        : lastMoveToRank - lastMoveFromRank;
        if (lastMove->getPiece()->getType() == ChessPieceType::Pawn &&
            lastMove->getTo()->getRank() == position->getRank() &&
            lastMoveRankDelta == 2) {
          int fileDelta = lastMove->getTo()->getFile() - position->getFile();

          if (fileDelta == 1) {
            chessPositions[count++] = ChessPosition(position->getFile() + 1,
                                                    position->getRank() + site);
          }

          if (fileDelta == -1) {
            chessPositions[count++] = ChessPosition(position->getFile() - 1,
                                                    position->getRank() + site);
          }
        }
      }
      break;
    }

    // po prostym ruchy
    case ChessPieceType::Rook: {
      for (uint8_t road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile() + road, position->getRank());
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (uint8_t road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile() - road, position->getRank());
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (uint8_t road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile(), position->getRank() + road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (uint8_t road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile(), position->getRank() - road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      break;
    }

    // koń zjebany jakiś nie wiem jak to inzczej
    case ChessPieceType::Knight: {
      int knightMoves[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                               {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
      int knightCurrentMove[2];

      for (int moveIndex = 0; moveIndex < 8; ++moveIndex) {
        knightCurrentMove[0] = knightMoves[moveIndex][0];
        knightCurrentMove[1] = knightMoves[moveIndex][1];
        tempPosition =
            ChessPosition(position->getFile() + knightCurrentMove[0],
                          position->getRank() + knightCurrentMove[1]);
        if (!tempPosition.isValid()) {
          continue;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied <= 0) {
          chessPositions[count++] = tempPosition;
        }
      }
      break;
    }

    // tu skosy
    case ChessPieceType::Bishop: {
      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() + road,
                                     position->getRank() + road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() - road,
                                     position->getRank() + road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() + road,
                                     position->getRank() - road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() - road,
                                     position->getRank() - road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }
      break;
    }

    // to to samo co wiea i goniec
    case ChessPieceType::Queen: {
      for (int road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile() + road, position->getRank());
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile() - road, position->getRank());
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile(), position->getRank() + road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition =
            ChessPosition(position->getFile(), position->getRank() - road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() + road,
                                     position->getRank() + road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() - road,
                                     position->getRank() + road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() + road,
                                     position->getRank() - road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }

      for (int road = 1; road <= 7; ++road) {
        tempPosition = ChessPosition(position->getFile() - road,
                                     position->getRank() - road);
        if (!tempPosition.isValid()) {
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->color);

        if (isOccupied == 0) {
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          chessPositions[count++] = tempPosition;
          break;
        } else {
          break;
        }
      }
      break;
    }

    // i podobnie jak w skoczku
    // dodać warunki do roszady
    case ChessPieceType::King: {
      int kingMoves[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
                             {1, 0}, {-1, 0}, {0, 1},  {0, -1}};
      int kingCurrentMove[2];
      ChessPiece *oponentKing = this->findPiece(
          ChessPieceType::King, piece->getColor() == ChessColor::White
                                    ? ChessColor::Black
                                    : ChessColor::White);
      ChessPosition oponentKingPositions[8];
      uint8_t oponentKingPositionsCount = 0;
      oponentKingPositionsCount =
          this->getKingAvailablePositions(oponentKing, oponentKingPositions);

      for (uint8_t moveIndex = 0; moveIndex < 8; ++moveIndex) {
        kingCurrentMove[0] = kingMoves[moveIndex][0];
        kingCurrentMove[1] = kingMoves[moveIndex][1];
        tempPosition = ChessPosition(position->getFile() + kingCurrentMove[0],
                                     position->getRank() + kingCurrentMove[1]);

        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        for (uint8_t i = 0; i < oponentKingPositionsCount; ++i) {
          if (tempPosition == oponentKingPositions[i]) {
            isOccupied = 1;
            break;
          }
        }

        if (isOccupied <= 0) {
          chessPositions[count++] = tempPosition;
        }
      }

      // roszada
      bool isShortCastlingPossible =
          this->isCastlingPossible(ChessCastlingType::Short, piece->getColor());
      bool isLongCastlingPossible =
          this->isCastlingPossible(ChessCastlingType::Long, piece->getColor());

      if (isShortCastlingPossible) {
        chessPositions[count++] = ChessPosition('g', position->getRank());
      }

      if (isLongCastlingPossible) {
        chessPositions[count++] = ChessPosition('c', position->getRank());
      }
      break;
    }
  }

  // Symulujemy ruchy i sprawdzamy czy król jest szachowany
  /* if (removeKingCheck) {
    ChessMove simulatedMove;
    for (int i = 0; i < count; i++) {
      this->startSimulation();

      simulatedMove = ChessMove(position, &chessPositions[i]);
      this->simulateMove(&simulatedMove);

      if (this->isKingChecked(piece->getColor())) {
        removePosition(chessPositions, &count, i);
        i--;
      }

      this->endSimulation();
    }
  } */

  return count;
}

uint8_t Chess::getKingAvailablePositions(ChessPiece *king,
                                         ChessPosition *positions) {
  uint8_t count = 0;
  int isOccupied = 0;
  int kingMoves[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
                         {1, 0}, {-1, 0}, {0, 1},  {0, -1}};
  int kingCurrentMove[2];
  ChessPosition *position = king->getPosition();
  ChessPosition tempPosition = ChessPosition(0, 0);

  for (uint8_t moveIndex = 0; moveIndex < 8; ++moveIndex) {
    kingCurrentMove[0] = kingMoves[moveIndex][0];
    kingCurrentMove[1] = kingMoves[moveIndex][1];
    tempPosition = ChessPosition(position->getFile() + kingCurrentMove[0],
                                 position->getRank() + kingCurrentMove[1]);

    isOccupied = this->isOccupied(&tempPosition, piece->getColor());

    if (isOccupied <= 0) {
      positions[count++] = tempPosition;
    }
  }

  return count;
}

uint8_t Chess::filterAvailablePositions(ChessPosition *chessPositions,
                                        uint8_t count, ChessPiece *piece) {
  // print_debug("Filtering available positions\n");
  ChessPosition *position = piece->getPosition();
  ChessColor color = piece->getColor();
  ChessMove simulatedMove;

  for (int i = 0; i < count; i++) {
    this->startSimulation();

    simulatedMove = ChessMove(position, &chessPositions[i]);
    this->simulateMove(&simulatedMove);

    if (this->isKingChecked(piece->getColor())) {
      removePosition(chessPositions, &count, i);
      i--;
    }

    this->endSimulation();
  }

  return count;
}
