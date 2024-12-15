
#include "chess.h"

#include "chess_log.h"

Chess::Chess() = default;

Chess::~Chess() = default;

void Chess::notifyTileAction(ChessPosition *position,
                             ChessTileActionType action) {
  print_debug(
      "Tile at %d %d has been %s\n", position->getRank(), position->getFile(),
      action == ChessTileActionType::PutDown ? "put down" : "picked up");

  this->tileState[position->getRank()][position->getFile()] =
      (action == ChessTileActionType::PickUp ? ChessTileState::Available
                                             : ChessTileState::Taken);

  if (this->gameState != ChessGameState::InProgress) {
    print_debug("Game is not in progress, skipping\n");
    return;
  }

  ChessPiece *piece = this->findPiece(position);
  ChessColor color = this->getCurrentPlayerColor();

  print_debug("Move made by %s\n",
              color == ChessColor::White ? "white" : "black");
  if (piece != nullptr) {
    print_debug("Found piece type %d, color %s\n", piece->getType(),
                piece->getColor() == ChessColor::White ? "white" : "black");
  } else {
    print_debug("No piece found\n");
  }

  // Pionek został podniesiony
  if (action == ChessTileActionType::PickUp && piece != nullptr &&
      piece->getColor() == color) {
    print_debug("First picked up piece\n");

    ChessPosition possiblePositions[27];
    uint8_t count = this->getAvailablePositions(piece, possiblePositions);
    this->pickedUpPiece = piece;

    print_debug("Found %d possible positions\n", count);
    print_debug("Saved picked up piece\n");

    notifyHighlightSquare(piece->getPosition(), ChessHighlightType::Info);

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

  // Pionek został odłożony na to samo pole
  if (action == ChessTileActionType::PutDown &&
      this->pickedUpPiece != nullptr && piece != nullptr &&
      piece->getPosition() == this->pickedUpPiece->getPosition()) {
    print_debug("Picked up piece put down on the same position\n");

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        notifyUnhighlightSquare(&this->position[i][j]);
      }
    }

    ChessPiece *whiteKing =
        this->findPiece(ChessPieceType::King, ChessColor::White);
    ChessPiece *blackKing =
        this->findPiece(ChessPieceType::King, ChessColor::Black);

    if (this->isKingChecked(ChessColor::White)) {
      notifyHighlightSquare(whiteKing->getPosition(),
                            ChessHighlightType::Check);
    }

    if (this->isKingChecked(ChessColor::Black)) {
      notifyHighlightSquare(blackKing->getPosition(),
                            ChessHighlightType::Check);
    }

    this->pickedUpPiece = nullptr;
    return;
  }

  // Pionek został odłożony na inne pole
  if (action == ChessTileActionType::PutDown &&
      this->pickedUpPiece != nullptr) {
    print_debug("Puted down picked up piece\n");

    ChessPosition possiblePositions[27];
    uint8_t count =
        this->getAvailablePositions(this->pickedUpPiece, possiblePositions);
    bool isGoodMove = false;

    print_debug("Found %d possible positions to unhighlight\n", count);

    notifyUnhighlightSquare(this->pickedUpPiece->getPosition());
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
      print_debug("Good move\n");
      // TODO: Add move to history
      ChessMove *move = &this->move[this->move_index];
      this->createMove(move, this->pickedUpPiece->getPosition(), position);
      this->applyMove(move);
      // notifyMoveMade(move);
      this->pickedUpPiece = nullptr;

      print_debug("Move applied\n");

      ChessPiece *whiteKing =
          this->findPiece(ChessPieceType::King, ChessColor::White);
      ChessPiece *blackKing =
          this->findPiece(ChessPieceType::King, ChessColor::Black);

      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          notifyUnhighlightSquare(&this->position[i][j]);
        }
      }

      if (this->repeatedPosition >= 10) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        return;
      }

      if (this->isMatPossible() == false) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        return;
      }

      if (this->movesFor75Rule == 150) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        return;
      }

      if (this->isKingChecked(ChessColor::White)) {
        notifyHighlightSquare(whiteKing->getPosition(),
                              ChessHighlightType::Check);
      }

      if (this->isKingCheckmate(ChessColor::White)) {
        notifyHighlightSquare(whiteKing->getPosition(),
                              ChessHighlightType::Checkmate);
        this->gameResult = ChessGameResult::BlackWins;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        return;
      }

      if (this->isKingChecked(ChessColor::Black)) {
        notifyHighlightSquare(blackKing->getPosition(),
                              ChessHighlightType::Check);
      }

      if (this->isKingCheckmate(ChessColor::Black)) {
        notifyHighlightSquare(blackKing->getPosition(),
                              ChessHighlightType::Checkmate);
        this->gameResult = ChessGameResult::WhiteWins;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        return;
      }

      if (this->isStalemate(color)) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        return;
      }

      print_debug("Wrong move\n");
      if (color == ChessColor::White) {
        this->whiteWrongMoves++;
        if (this->whiteWrongMoves >= 3) {
          this->gameResult = ChessGameResult::BlackWins;
          this->gameState = ChessGameState::Ended;
          notifyGameEnded();
          return;
        }
      } else {
        this->blackWrongMoves++;
        if (this->blackWrongMoves >= 3) {
          this->gameResult = ChessGameResult::WhiteWins;
          this->gameState = ChessGameState::Ended;
          notifyGameEnded();
          return;
        }
      }

      notifyHighlightSquare(this->pickedUpPiece->getPosition(),
                            ChessHighlightType::Error);
      notifyHighlightSquare(position, ChessHighlightType::Error);

    } else {
      notifyError(color);
    }
  }
  print_debug("End of notifyTileAction\n");
}

ChessGameStartError Chess::startGame() {
  int err = 0;

  print_debug("Starting game\n");

  if (this->gameState == ChessGameState::InProgress) {
    print_error("Game already started\n");
    return ChessGameStartError::GameAlreadyStarted;
  }

  this->gameState = ChessGameState::NotStarted;
  print_debug("Game state set to not started\n");

#ifndef CONFIG_CHESS_LIB_TEST
  err = this->checkPiecesArrangement();
  if (err != 0) {
    return ChessGameStartError::InvalidPieceArrangement;
  }
#endif

  this->assignPiecesToPositions();

  this->gameState = ChessGameState::InProgress;

  return ChessGameStartError::Ok;
}

int Chess::checkPiecesArrangement() {
  print_debug("Checking pieces arrangement\n");

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

  print_debug("Pieces arrangement is correct\n");

  return 0;
}

// przypisujemy pionki
void Chess::assignPiecesToPositions() {
  print_debug("Assigning pieces to positions\n");
#ifndef CONFIG_CHESS_LIB_TEST
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

  print_debug("Assigned all pieces\n");

#else
  /*
  this->piece[0].setPosition(this->getPosition("a1"));
  this->piece[3].setPosition(this->getPosition("b1"));
  this->piece[1].setPosition(this->getPosition("d2"));
  this->piece[18].setPosition(this->getPosition("a3"));
  this->piece[20].setPosition(this->getPosition("d4"));
  this->piece[24].setPosition(this->getPosition("b4"));
  */
  this->piece[8].setPosition(this->getPosition("c2"));
  this->piece[30].setPosition(this->getPosition("b4"));

  print_debug("Piece 0 assigned to position A1\n");
  // print_debug("Piece 8 assigned to position A2\n");
#endif
}

// podświetlenie kwadracikow
/* void Chess::highlightPositions(ChessPosition *chessPositions, uint8_t
count) { ChessPosition *position; for (int i = 0; i < count; ++i) { position =
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
