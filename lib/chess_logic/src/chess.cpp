
#include "chess.h"

#ifdef CHESS_ZEPHYR_LOG
LOG_MODULE_REGISTER(chess_main, LOG_LEVEL_DBG);
#endif

Chess::Chess() = default;

Chess::~Chess() = default;

void Chess::notifyTileAction(ChessPosition *position,
                             ChessTileActionType action) {
  print_debug(
      "Tile at %d %d has been %s\n", position->getRank(), position->getFile(),
      action == ChessTileActionType::PutDown ? "put down" : "picked up");

  this->tileState[position->getFile() - 1][position->getRank() - 1] =
      (action == ChessTileActionType::PickUp ? ChessTileState::Available
                                             : ChessTileState::Taken);

  if (this->gameState != ChessGameState::InProgress) {
    print_debug("Game is not in progress, skipping\n");
    return;
  }

  if (this->waitingForTimmer) {
    print_debug("Waiting for timmer, skipping\n");
    return;
  }

  ChessPiece *piece = this->findPiece(position);
  ChessColor color = this->getCurrentPlayerColor();
  ChessColor oponentColor =
      color == ChessColor::White ? ChessColor::Black : ChessColor::White;

  print_debug("Move made by %s\n",
              color == ChessColor::White ? "white" : "black");
  if (piece != nullptr) {
    print_debug("Found piece type %d, color %s\n", (int)piece->getType(),
                piece->getColor() == ChessColor::White ? "white" : "black");
  } else {
    print_debug("No piece found\n");
  }

  if (this->castlingRook != nullptr && this->castlingRookPosition != nullptr) {
    if (action == ChessTileActionType::PutDown &&
        *position == *this->castlingRook->getPosition()) {
      print_debug("Castling rook put down\n");
      this->castlingRook = nullptr;
      this->castlingRookPosition = nullptr;

      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          notifyUnhighlightSquare(&this->position[i][j]);
        }
      }
    }

    return;
  }

  if (this->enPassantPosition != nullptr) {
    if (action == ChessTileActionType::PickUp &&
        *position == *this->enPassantPosition) {
      print_debug("En passant position picked up\n");
      ChessPiece *oponent = this->findPiece(this->enPassantPosition);
      if (oponent != nullptr) {
        oponent->isOnBoard = false;
        oponent->setPosition(nullptr);
      }
      this->enPassantPosition = nullptr;
    }

    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        notifyUnhighlightSquare(&this->position[i][j]);
      }
    }

    return;
  }

  if (this->promotionPiece != nullptr) {
    return;
  }

  if (action == ChessTileActionType::PickUp && piece != nullptr &&
      piece->getColor() == color) {
    print_debug("First picked up piece\n");

    notifyHighlightSquare(piece->getPosition(), ChessHighlightType::Info);

    this->pickedUpPiece = piece;

    if (this->choosenOpening >= 0) {
      ChessOpening *opening = &this->openings[this->choosenOpening];

      if (this->move_index < opening->movesCount) {
        ChessMove *move = &opening->moves[this->move_index];
        if (*move->getFrom() == *piece->getPosition()) {
          notifyHighlightSquare(move->getTo(),
                                move->getType() == ChessMoveType::Capture
                                    ? ChessHighlightType::CaptureMove
                                    : ChessHighlightType::NormalMove);
          return;
        }
      }
    }

    bool highlight = color == ChessColor::White ? this->highlightWhites
                                                : this->highlightBlacks;
    if (!highlight) {
      return;
    }

    ChessPosition possiblePositions[27];
    uint8_t count = this->getAvailablePositions(piece, possiblePositions);
    count = this->filterAvailablePositions(possiblePositions, count, piece);

    print_debug("Found %d possible positions\n", count);
    print_debug("Saved picked up piece\n");

    ChessPiece *oponent = nullptr;
    for (int i = 0; i < count; ++i) {
      oponent = this->findPiece(&possiblePositions[i]);
      if (piece->getType() == ChessPieceType::Pawn && oponent == nullptr &&
          piece->getPosition()->getFile() != possiblePositions[i].getFile() &&
          piece->getPosition()->getRank() != possiblePositions[i].getRank()) {
        notifyHighlightSquare(&possiblePositions[i],
                              ChessHighlightType::CaptureMove);
        this->positionsToExcludeFromWrongMoves
            [this->positionsToExcludeFromWrongMovesCount++] =
            &possiblePositions[i];
      } else if (oponent == nullptr) {
        notifyHighlightSquare(&possiblePositions[i],
                              ChessHighlightType::NormalMove);
      } else {
        notifyHighlightSquare(&possiblePositions[i],
                              ChessHighlightType::CaptureMove);
        this->positionsToExcludeFromWrongMoves
            [this->positionsToExcludeFromWrongMovesCount++] =
            &possiblePositions[i];
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

    if (color == ChessColor::White) {
      this->lastWrongMoveWhite = -1;
    } else {
      this->lastWrongMoveBlack = -1;
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
    this->positionsToExcludeFromWrongMovesCount = 0;
    return;
  }

  // Pionek został odłożony na inne pole
  if (action == ChessTileActionType::PutDown &&
      this->pickedUpPiece != nullptr) {
    print_debug("Puted down picked up piece\n");

    ChessPosition possiblePositions[27];
    uint8_t count =
        this->getAvailablePositions(this->pickedUpPiece, possiblePositions);
    count = this->filterAvailablePositions(possiblePositions, count, piece);
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
      this->waitingForTimmer = this->shouldWaitForTimmer;
      print_debug("Good move\n");

      ChessMove *move = &this->move[this->move_index];
      this->createMove(move, this->pickedUpPiece->getPosition(), position);

      if (this->choosenOpening >= 0) {
        ChessOpening *opening = &this->openings[this->choosenOpening];

        if (this->move_index < opening->movesCount) {
          ChessMove *openingMove = &opening->moves[this->move_index];
          if (*openingMove->getFrom() != *move->getFrom() ||
              *openingMove->getTo() != *move->getTo()) {
            this->choosenOpening = -1;
          }
        } else {
          this->choosenOpening = -1;
        }
      }

      this->applyMove(move);
      this->pickedUpPiece = nullptr;
      this->positionsToExcludeFromWrongMovesCount = 0;

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

      // Zasada 3 powtórzeń pozycji na szachownicy
      if (this->are3RepeatedPositions()) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        clear();
        return;
      }

      if (this->isMatPossible() == false) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        clear();
        return;
      }

      // Zasada 75 ruchów
      if (this->movesFor75Rule == 150) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        clear();
        return;
      }

      if (this->isKingChecked(ChessColor::White)) {
        if (this->isKingCheckmate(ChessColor::White)) {
          notifyHighlightSquare(whiteKing->getPosition(),
                                ChessHighlightType::Checkmate);
          this->gameResult = ChessGameResult::BlackWins;
          this->gameState = ChessGameState::Ended;
          notifyGameEnded();
          clear();
          return;
        }

        notifyHighlightSquare(whiteKing->getPosition(),
                              ChessHighlightType::Check);
      }

      if (this->isKingChecked(ChessColor::Black)) {
        if (this->isKingCheckmate(ChessColor::Black)) {
          notifyHighlightSquare(blackKing->getPosition(),
                                ChessHighlightType::Checkmate);
          this->gameResult = ChessGameResult::WhiteWins;
          this->gameState = ChessGameState::Ended;
          notifyGameEnded();
          clear();
          return;
        }

        notifyHighlightSquare(blackKing->getPosition(),
                              ChessHighlightType::Check);
      }

      if (this->isStalemate(oponentColor) &&
          !this->isKingChecked(oponentColor)) {
        this->gameResult = ChessGameResult::Draw;
        this->gameState = ChessGameState::Ended;
        notifyGameEnded();
        clear();
        return;
      }

      if (move->getType() == ChessMoveType::EnPassant) {
        this->notifyEnPassant(move->getPiece()->getColor());
      }

      if (move->getType() == ChessMoveType::Promotion) {
        this->promotionPiece = move->getPiece();
        this->notifyPromotion(move->getPiece()->getColor());
      }

      if (move->getType() == ChessMoveType::Castling) {
        this->notifyCastling(move->getPiece()->getColor());
      }

      if (this->choosenOpening >= 0) {
        ChessOpening *opening = &this->openings[this->choosenOpening];

        if (this->move_index < opening->movesCount) {
          ChessMove *move = &opening->moves[this->move_index];
          notifyHighlightSquare(move->getFrom(), ChessHighlightType::Info);
          return;
        }
      }

    } else {
      print_debug("Wrong move\n");
      if (this->pickedUpPiece->getColor() == ChessColor::White) {
        if (this->lastWrongMoveWhite != this->move_index) {
          this->lastWrongMoveWhite = this->move_index;
          this->whiteWrongMoves++;
        }

        if (this->whiteWrongMoves >= 3) {
          this->gameResult = ChessGameResult::BlackWins;
          this->gameState = ChessGameState::Ended;
          notifyGameEnded();
          clear();
          return;
        }
      } else if (this->pickedUpPiece->getColor() == ChessColor::Black) {
        if (this->lastWrongMoveBlack != this->move_index) {
          this->lastWrongMoveBlack = this->move_index;
          this->blackWrongMoves++;
        }

        if (this->blackWrongMoves >= 3) {
          this->gameResult = ChessGameResult::WhiteWins;
          this->gameState = ChessGameState::Ended;
          notifyGameEnded();
          clear();
          return;
        }
      }

      notifyHighlightSquare(this->pickedUpPiece->getPosition(),
                            ChessHighlightType::Error);
      notifyHighlightSquare(position, ChessHighlightType::Error);
      notifyError(color);
    }
  }

  if (this->castlingRook != nullptr && this->castlingRookPosition != nullptr) {
    this->notifyHighlightSquare(this->castlingRookPosition,
                                ChessHighlightType::Error);
    this->notifyHighlightSquare(this->castlingRook->getPosition(),
                                ChessHighlightType::Error);
  }

  if (this->enPassantPosition != nullptr) {
    this->notifyHighlightSquare(this->enPassantPosition,
                                ChessHighlightType::CaptureMove);
  }

  print_debug("End of notifyTileAction\n");
}

ChessGameStartError Chess::startGame(bool shouldWaitForTimmer) {
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

  this->gameState = ChessGameState::InProgress;

  if (this->choosenOpening >= 0) {
    ChessOpening *opening = &this->openings[this->choosenOpening];

    if (this->move_index < opening->movesCount) {
      ChessMove *move = &opening->moves[this->move_index];
      notifyHighlightSquare(move->getFrom(), ChessHighlightType::Info);
    }
  }

  return ChessGameStartError::Ok;
}

int Chess::checkPiecesArrangement() {
  print_debug("Checking pieces arrangement\n");
  int ret = 0;

  uint8_t positionsToHighlight[8][8];

  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      positionsToHighlight[i][j] = 0;
    }
  }

  // Sprawdzamy czy pionki są na swoich miejscach
  for (uint8_t file = 0; file < 8; file++) {
    for (uint8_t rank = 0; rank < 8; rank++) {
      if (this->tileState[file][rank] == ChessTileState::Available &&
          (rank == 0 || rank == 1 || rank == 6 || rank == 7)) {
        // Brakuje pionka
        positionsToHighlight[file][rank] = 1;
        ret = -1;
      }

      if (this->tileState[file][rank] == ChessTileState::Taken && rank > 1 &&
          rank < 6) {
        // Pionek nie powinien tu być
        positionsToHighlight[file][rank] = 1;
        ret = -2;
      }
    }
  }

  for (uint8_t file = 0; file < 8; file++) {
    for (uint8_t rank = 0; rank < 8; rank++) {
      if (positionsToHighlight[file][rank]) {
        notifyHighlightSquare(&this->position[file][rank],
                              ChessHighlightType::Error);
      } else {
        notifyUnhighlightSquare(&this->position[file][rank]);
      }
    }
  }

  if (ret == 0) {
    print_debug("Pieces arrangement is correct\n");
  } else {
    print_error("Pieces arrangement is incorrect\n");
  }

  return ret;
}

// przypisujemy pionki
void Chess::assignPiecesToPositions() {
  print_debug("Assigning pieces to positions\n");

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
}

void Chess::pressTimmerButton(ChessColor color) {
  print_debug("Timmer button pressed\n");

  if (this->gameState != ChessGameState::InProgress) {
    print_debug("Game is not in progress, skipping\n");
    return;
  }

  if (this->waitingForTimmer == false) {
    print_debug("Not waiting for timmer, skipping\n");
    return;
  }

  ChessColor currentPlayerColor = this->getCurrentPlayerColor();
  if (currentPlayerColor == ChessColor::White) {
    currentPlayerColor = ChessColor::Black;
  } else {
    currentPlayerColor = ChessColor::White;
  }

  if (currentPlayerColor != color) {
    print_debug("Wrong player pressed timmer button\n");
    return;
  }

  this->waitingForTimmer = false;
  print_debug("Timmer button pressed\n");

  ChessPiece *whiteKing =
      this->findPiece(ChessPieceType::King, ChessColor::White);
  ChessPiece *blackKing =
      this->findPiece(ChessPieceType::King, ChessColor::Black);

  if (this->isKingChecked(ChessColor::White)) {
    notifyHighlightSquare(whiteKing->getPosition(), ChessHighlightType::Check);
  }

  if (this->isKingChecked(ChessColor::Black)) {
    notifyHighlightSquare(blackKing->getPosition(), ChessHighlightType::Check);
  }
}

void Chess::finishGame(ChessGameResult result) {
  print_debug("Finishing game\n");

  if (this->gameState != ChessGameState::InProgress) {
    print_debug("Game is not in progress, skipping\n");
    return;
  }

  this->gameResult = result;
  this->gameState = ChessGameState::Ended;
  notifyGameEnded();
  clear();
}

void Chess::setPromotionPiece(ChessPieceType piece) {
  print_debug("Setting promotion piece\n");

  if (this->promotionPiece == nullptr) {
    print_error("No promotion piece to set\n");
    return;
  }

  this->promotionPiece->setType(piece);
  this->promotionPiece = nullptr;

  ChessPiece *whiteKing =
      this->findPiece(ChessPieceType::King, ChessColor::White);
  ChessPiece *blackKing =
      this->findPiece(ChessPieceType::King, ChessColor::Black);

  if (this->isKingChecked(ChessColor::White)) {
    notifyHighlightSquare(whiteKing->getPosition(), ChessHighlightType::Check);
  }

  if (this->isKingChecked(ChessColor::Black)) {
    notifyHighlightSquare(blackKing->getPosition(), ChessHighlightType::Check);
  }
}