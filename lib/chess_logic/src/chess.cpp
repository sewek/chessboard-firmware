
#include "chess.h"

Chess::Chess() = default;

Chess::~Chess() = default;

void Chess::notifyTileAction(ChessPosition *position,
                             ChessTileActionType action) {
  this->tileState[position->getRank()][position->getFile()] =
      (action == ChessTileActionType::PickUp ? ChessTileState::Available
                                             : ChessTileState::Taken);

  ChessPiece *piece = this->findPiece(position);
  ChessColor color = this->getCurrentPlayerColor();

  if (action == ChessTileActionType::PickUp && piece != nullptr &&
      piece->getColor() == color) {
    ChessPosition possiblePositions[27];
    uint8_t count = this->getAvailablePositions(piece, possiblePositions);
    this->pickedUpPiece = piece;

    for (int i = 0; i < count; ++i) {
      if (this->findPiece(&possiblePositions[i]) == nullptr) {
        notifyHighlightSquare(&possiblePositions[i],
                              ChessHighlightType::NormalMove);
      } else {
        notifyHighlightSquare(&possiblePositions[i],
                              ChessHighlightType::CaptureMove);
      }
    }

    return;
  }

  if (action == ChessTileActionType::PutDown &&
      this->pickedUpPiece != nullptr) {
    ChessPosition possiblePositions[27];
    uint8_t count =
        this->getAvailablePositions(this->pickedUpPiece, possiblePositions);
    bool isGoodMove = false;

    for (int i = 0; i < count; ++i) {
      notifyUnhighlightSquare(&possiblePositions[i]);
    }

    for (int i = 0; i < count; ++i) {
      if (possiblePositions[i] == *position) {
        isGoodMove = true;
        break;
      }
    }

    if (isGoodMove) {
      // TODO: Add move to history
      ChessMove *move = nullptr;
      this->createMove(move, this->pickedUpPiece->getPosition(), position);
      this->applyMove(move);
      // notifyMoveMade(move);
    } else {
      if (color == ChessColor::White) {
        this->whiteWrongMoves++;
      } else {
        this->blackWrongMoves++;
      }

      notifyHighlightSquare(this->pickedUpPiece->getPosition(),
                            ChessHighlightType::Error);
    }
  }
}

ChessGameStartError Chess::startGame() {
  int err = 0;

  if (this->gameState == ChessGameState::InProgress) {
    return ChessGameStartError::GameAlreadyStarted;
  }

  this->gameState = ChessGameState::NotStarted;

  err = this->checkPiecesArrangement();
  if (err != 0) {
    return ChessGameStartError::InvalidPieceArrangement;
  }

  this->assignPiecesToPositions();

  this->gameState = ChessGameState::InProgress;

  return ChessGameStartError::Ok;
}

int Chess::checkPiecesArrangement() {
  for (uint8_t rank = 0; rank < 8; rank++) {
    for (uint8_t file = 0; file < 8; file++) {
      if (this->tileState[rank][file] == ChessTileState::Available &&
          (rank == 0 || rank == 1 || rank == 6 || rank == 7)) {
        // Brakuje pionka
        notifyHighlightSquare(&this->position[rank][file],
                              ChessHighlightType::Error);
        return -1;
      }

      if (this->tileState[rank][file] == ChessTileState::Taken && rank > 1 &&
          rank < 6) {
        // Pionek nie powinien tu być
        notifyHighlightSquare(&this->position[rank][file],
                              ChessHighlightType::Error);
        return -2;
      }
    }
  }

  return 0;
}

// przypisujemy pionki
void Chess::assignPiecesToPositions() {
  for (int i = 0; i < 8; ++i) {
    this->piece[i].setPosition(&this->position[i][0]);
  }

  for (int i = 0; i < 8; ++i) {
    this->piece[8 + i].setPosition(&this->position[i][1]);
  }

  for (int i = 0; i < 8; ++i) {
    this->piece[16 + i].setPosition(&this->position[i][7]);
  }

  for (int i = 0; i < 8; ++i) {
    this->piece[24 + i].setPosition(&this->position[i][6]);
  }
}

// podświetlenie kwadracikow
/* void Chess::highlightPositions(ChessPosition *chessPositions, uint8_t count)
{ ChessPosition *position; for (int i = 0; i < count; ++i) { position =
&chessPositions[i];
    // tu podświetla ormmalny ruch
    if (isOccupied(piece, chessPositions[i]) = 0) {
      notifyHighlightSquare(position);
    }
    // tu podświetla bicie, nie licząc enpasant
    if (isOccupied(piece, chessPositions[i]) = -1) {
      notifyHighlightSquare(position);
    }
  }
} */
