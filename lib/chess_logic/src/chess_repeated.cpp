#include "chess.h"

void Chess::saveRepeatedPosition() {
  if (this->repeatedPositionIndex >= 50) {
    // Shift all positions
    for (uint8_t i = 0; i < 49; i++) {
      for (uint8_t j = 0; j < 32; j++) {
        this->repeatedPositions[i][j] = this->repeatedPositions[i + 1][j];
      }
    }

    this->repeatedPositionIndex = 49;
  }

  for (uint8_t i = 0; i < 32; i++) {
    this->repeatedPositions[this->repeatedPositionIndex][i] = this->piece[i];
  }

  this->repeatedPositionIndex++;
}

void Chess::clearRepeatedPositions() { this->repeatedPositionIndex = 0; }

bool Chess::are3RepeatedPositions() {
  // Check if there are at least 3 repeated positions
  if (this->repeatedPositionIndex < 3) {
    return false;
  }

  // Check in reverse order
  bool areEqual = true;
  for (uint8_t i = this->repeatedPositionIndex - 1; i >= 2; i--) {
    for (uint8_t j = i - 1; j >= 1; j--) {
      for (uint8_t k = j - 1; k >= 0; k--) {
        areEqual = true;
        for (uint8_t l = 0; l < 32; l++) {
          if (this->repeatedPositions[i][l] != this->repeatedPositions[j][l] ||
              this->repeatedPositions[j][l] != this->repeatedPositions[k][l]) {
            areEqual = false;
            break;
          }
        }

        if (areEqual) {
          return true;
        }
      }
    }
  }

  return false;
}