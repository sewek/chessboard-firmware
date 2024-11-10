#include "chess.h"

#ifdef __ZEPHYR__
#include <zephyr/sys/util.h>
#define memcpy bytecpy
#else
#include <string.h>
#endif

void Chess::startSimulation() {
  memcpy(this->pieceSimulationBackup, this->piece, sizeof(this->piece));
}

void Chess::endSimulation() {
  memcpy(this->piece, this->pieceSimulationBackup, sizeof(this->piece));
}

void Chess::simulateMove(ChessMove *move) {
  ChessPiece *piece = this->findPiece(move->getFrom());
  ChessPiece *oponent = this->findPiece(move->getTo());

  if (oponent != nullptr) {
    oponent->setPosition(nullptr);
  }

  piece->setPosition(move->getTo());
}
