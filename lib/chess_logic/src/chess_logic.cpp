#include "chess.h"
#include "chess_log.h"

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
      ChessMove *lastMove = &this->move[move_index];
      uint8_t lastMoveFromRank = lastMove->getFrom()->getRank();
      uint8_t lastMoveToRank = lastMove->getTo()->getRank();
      uint8_t lastMoveRankDelta = lastMoveFromRank > lastMoveToRank
                                      ? lastMoveFromRank - lastMoveToRank
                                      : lastMoveToRank - lastMoveFromRank;
      if (lastMove->getPiece()->getType() == ChessPieceType::Pawn &&
          lastMove->getTo()->getRank() == position->getRank() &&
          lastMoveRankDelta == 2) {
        int fileDelta = lastMove->getTo()->getRank() - position->getRank();

        if (fileDelta == 1) {
          chessPositions[count++] = ChessPosition(position->getFile() + 1,
                                                  position->getRank() + site);
        }

        if (fileDelta == -1) {
          chessPositions[count++] = ChessPosition(position->getFile() - 1,
                                                  position->getRank() + site);
        }
      }
      break;
    }

    // po prostym ruchy
    case ChessPieceType::Rook: {
      for (uint8_t road = 1; road <= 7; ++road) {
        print_debug("#1 Road: %d\n", road);
        tempPosition =
            ChessPosition(position->getFile() + road, position->getRank());
        if (!tempPosition.isValid()) {
          print_debug("Position is not valid, break\n");
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          print_debug("Position is not occupied, add\n");
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          print_debug(
              "Position is occupied by opponent piece, add and break\n");
          chessPositions[count++] = tempPosition;
          break;
        } else {
          print_debug("Position is occupied by our piece, break\n");
          break;
        }
      }

      for (uint8_t road = 1; road <= 7; ++road) {
        print_debug("#2 Road: %d\n", road);
        tempPosition =
            ChessPosition(position->getFile() - road, position->getRank());
        print_debug("Position %d %d\n", tempPosition.getFile(),
                    tempPosition.getRank());
        if (!tempPosition.isValid()) {
          print_debug("Position is not valid, break\n");
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          print_debug("Position is not occupied, add\n");
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          print_debug(
              "Position is occupied by opponent piece, add and break\n");
          chessPositions[count++] = tempPosition;
          break;
        } else {
          print_debug("Position is occupied by our piece, break\n");
          break;
        }
      }

      for (uint8_t road = 1; road <= 7; ++road) {
        print_debug("#3 Road: %d\n", road);
        tempPosition =
            ChessPosition(position->getFile(), position->getRank() + road);
        if (!tempPosition.isValid()) {
          print_debug("Position is not valid, break\n");
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          print_debug("Position is not occupied, add\n");
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          print_debug(
              "Position is occupied by opponent piece, add and break\n");
          chessPositions[count++] = tempPosition;
          break;
        } else {
          print_debug("Position is occupied by our piece, break\n");
          break;
        }
      }

      for (uint8_t road = 1; road <= 7; ++road) {
        print_debug("#4 Road: %d\n", road);
        tempPosition =
            ChessPosition(position->getFile(), position->getRank() - road);
        if (!tempPosition.isValid()) {
          print_debug("Position is not valid, break\n");
          break;
        }
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied == 0) {
          print_debug("Position is not occupied, add\n");
          chessPositions[count++] = tempPosition;
        } else if (isOccupied == -1) {
          print_debug(
              "Position is occupied by opponent piece, add and break\n");
          chessPositions[count++] = tempPosition;
          break;
        } else {
          print_debug("Position is occupied by our piece, break\n");
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
      bool willBeChecked = false;
      int kingCurrentMove[2];

      for (uint8_t moveIndex = 0; moveIndex < 8; ++moveIndex) {
        kingCurrentMove[0] = kingMoves[moveIndex][0];
        kingCurrentMove[1] = kingMoves[moveIndex][1];
        tempPosition = ChessPosition(position->getFile() + kingCurrentMove[0],
                                     position->getRank() + kingCurrentMove[1]);
        /* willBeChecked =
            this->willBeKingChecked(&tempPosition, piece->getColor()); */
        isOccupied = this->isOccupied(&tempPosition, piece->getColor());

        if (isOccupied <= 0 /* && !willBeChecked */) {
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
  ChessMove simulatedMove;
  for (uint8_t i = 0; i < count; i++) {
    this->startSimulation();

    simulatedMove = ChessMove(position, &chessPositions[i]);
    this->simulateMove(&simulatedMove);

    if (this->isKingChecked(piece->getColor())) {
      removePosition(chessPositions, &count, i);
    }

    this->endSimulation();
  }

  return count;
}
