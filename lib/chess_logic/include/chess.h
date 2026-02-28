#ifndef _CHESS_LOGIC_H_
#define _CHESS_LOGIC_H_

#include "chess_events.h"
#include "chess_log.h"
#include "chess_opening.h"
#include "chess_piece.h"
#include "chess_types.h"

#define CHESS_MOVE_MAX 500

class Chess : public ChessEvents {
 public:
  Chess();
  ~Chess();

  /**
   * @brief Notify about chess tile action.
   */
  void notifyTileAction(ChessPosition *position, ChessTileActionType action);

  /**
   * @brief Start game by user
   */
  ChessGameStartError startGame(bool shouldWaitForTimmer = false);

  /**
   * @brief Check if the game is in progress.
   */
  bool isInProgress() const { return gameState == ChessGameState::InProgress; }

  /**
   * @brief Get wrong moves count for given color.
   * @param color The color of the player.
   * @return The wrong moves count.
   */
  uint8_t getWrongMoves(ChessColor color) const {
    return color == ChessColor::White ? whiteWrongMoves : blackWrongMoves;
  }

  /**
   * @brief Get the game result.
   */
  ChessGameResult getGameResult() const { return gameResult; }

  /**
   * @brief Get the game state.
   */
  void pressTimmerButton(ChessColor color);

  /**
   * @brief Is waiting for timmer button.
   * @return True if waiting for timmer button, false otherwise.
   */
  bool isWaitingForTimmer() const { return waitingForTimmer; }

  /**
   * @brief Finish the game.
   * @param result The result of the game.
   */
  void finishGame(ChessGameResult result);

  /**
   * @brief Set promotion piece.
   * @param piece The piece to promote.
   */
  void setPromotionPiece(ChessPieceType piece);

  /**
   * @brief Highlight available positions.
   * @param color The color of the player.
   * @param highlight If true, highlight available positions.
   */
  void setHighlightAvailablePositions(ChessColor color, bool highlight) {
    color == ChessColor::White ? this->highlightWhites = highlight
                               : this->highlightBlacks = highlight;
  }

  /**
   * @brief Get highlight status for color.
   * @param color The color of the player.
   * @return The highlight status.
   */
  bool getHighlightAvailablePositions(ChessColor color) const {
    return color == ChessColor::White ? this->highlightWhites
                                      : this->highlightBlacks;
  }

  /**
   * @brief Get openings count.
   * @return The openings count.
   */
  uint8_t getOpeningsCount() const { return openingsCount; }

  /**
   * @brief Get n'th opening move.
   * @param index The index of the opening move.
   * @return The opening.
   */
  ChessOpening *getOpening(int index) {
    if (index >= openingsCount) {
      return &openingFallback;
    }

    if (index < 0) {
      return &openingFallback;
    }

    return &openings[index];
  }

  /**
   * @brief Get opening index.
   * @return The opening index.
   * @return The opening index.
   */
  int getOpeningIndex() const { return choosenOpening; }

  /**
   * @brief Set the opening.
   * @param index The index of the opening.
   */
  void setOpening(int index) {
    if (index >= openingsCount) {
      choosenOpening = -1;
    }

    choosenOpening = index;
  }

 private:
  ChessTileState tileState[8][8] = {};
  ChessPosition position[8][8] = {
      {
          ChessPosition("a1"),
          ChessPosition("a2"),
          ChessPosition("a3"),
          ChessPosition("a4"),
          ChessPosition("a5"),
          ChessPosition("a6"),
          ChessPosition("a7"),
          ChessPosition("a8"),
      },
      {
          ChessPosition("b1"),
          ChessPosition("b2"),
          ChessPosition("b3"),
          ChessPosition("b4"),
          ChessPosition("b5"),
          ChessPosition("b6"),
          ChessPosition("b7"),
          ChessPosition("b8"),
      },
      {
          ChessPosition("c1"),
          ChessPosition("c2"),
          ChessPosition("c3"),
          ChessPosition("c4"),
          ChessPosition("c5"),
          ChessPosition("c6"),
          ChessPosition("c7"),
          ChessPosition("c8"),
      },
      {
          ChessPosition("d1"),
          ChessPosition("d2"),
          ChessPosition("d3"),
          ChessPosition("d4"),
          ChessPosition("d5"),
          ChessPosition("d6"),
          ChessPosition("d7"),
          ChessPosition("d8"),
      },
      {
          ChessPosition("e1"),
          ChessPosition("e2"),
          ChessPosition("e3"),
          ChessPosition("e4"),
          ChessPosition("e5"),
          ChessPosition("e6"),
          ChessPosition("e7"),
          ChessPosition("e8"),
      },
      {
          ChessPosition("f1"),
          ChessPosition("f2"),
          ChessPosition("f3"),
          ChessPosition("f4"),
          ChessPosition("f5"),
          ChessPosition("f6"),
          ChessPosition("f7"),
          ChessPosition("f8"),
      },
      {
          ChessPosition("g1"),
          ChessPosition("g2"),
          ChessPosition("g3"),
          ChessPosition("g4"),
          ChessPosition("g5"),
          ChessPosition("g6"),
          ChessPosition("g7"),
          ChessPosition("g8"),
      },
      {
          ChessPosition("h1"),
          ChessPosition("h2"),
          ChessPosition("h3"),
          ChessPosition("h4"),
          ChessPosition("h5"),
          ChessPosition("h6"),
          ChessPosition("h7"),
          ChessPosition("h8"),
      },
  };
  ChessPiece piece[32] = {
      ChessPiece(ChessColor::White, ChessPieceType::Rook),
      ChessPiece(ChessColor::White, ChessPieceType::Knight),
      ChessPiece(ChessColor::White, ChessPieceType::Bishop),
      ChessPiece(ChessColor::White, ChessPieceType::Queen),
      ChessPiece(ChessColor::White, ChessPieceType::King),
      ChessPiece(ChessColor::White, ChessPieceType::Bishop),
      ChessPiece(ChessColor::White, ChessPieceType::Knight),
      ChessPiece(ChessColor::White, ChessPieceType::Rook),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::White, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Rook),
      ChessPiece(ChessColor::Black, ChessPieceType::Knight),
      ChessPiece(ChessColor::Black, ChessPieceType::Bishop),
      ChessPiece(ChessColor::Black, ChessPieceType::Queen),
      ChessPiece(ChessColor::Black, ChessPieceType::King),
      ChessPiece(ChessColor::Black, ChessPieceType::Bishop),
      ChessPiece(ChessColor::Black, ChessPieceType::Knight),
      ChessPiece(ChessColor::Black, ChessPieceType::Rook),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
      ChessPiece(ChessColor::Black, ChessPieceType::Pawn),
  };
  int choosenOpening = -1;
  uint8_t openingsCount = 2;
  ChessOpening openingFallback = {
      .name = "Brak",
      .movesCount = 0,
      .moves = {},
  };
  ChessOpening openings[2] = {
      {
          .name = "Sicilian Defense: Open Variation",
          .movesCount = 7,
          .moves =
              {
                  ChessMove(this->getPosition("e2"), this->getPosition("e4")),
                  ChessMove(this->getPosition("c7"), this->getPosition("c5")),
                  ChessMove(this->getPosition("g1"), this->getPosition("f3")),
                  ChessMove(this->getPosition("d7"), this->getPosition("d6")),
                  ChessMove(this->getPosition("d2"), this->getPosition("d4")),
                  ChessMove(this->getPosition("c5"), this->getPosition("d4"),
                            nullptr, ChessMoveType::Capture),
                  ChessMove(this->getPosition("f3"), this->getPosition("d4"),
                            nullptr, ChessMoveType::Capture),
              },
      },
      {
          .name = "Sicilian Defense: Najdorf Variation",
          .movesCount = 10,
          .moves =
              {
                  ChessMove(this->getPosition("e2"), this->getPosition("e4")),
                  ChessMove(this->getPosition("c7"), this->getPosition("c5")),
                  ChessMove(this->getPosition("g1"), this->getPosition("f3")),
                  ChessMove(this->getPosition("d7"), this->getPosition("d6")),
                  ChessMove(this->getPosition("d2"), this->getPosition("d4")),
                  ChessMove(this->getPosition("c5"), this->getPosition("d4"),
                            nullptr, ChessMoveType::Capture),
                  ChessMove(this->getPosition("f3"), this->getPosition("d4"),
                            nullptr, ChessMoveType::Capture),
                  ChessMove(this->getPosition("g8"), this->getPosition("f6")),
                  ChessMove(this->getPosition("b1"), this->getPosition("c3")),
                  ChessMove(this->getPosition("a7"), this->getPosition("a6")),
              },
      }

  };
  ChessPiece repeatedPositions[50][32];
  ChessPiece pieceSimulationBackup[32];
  uint8_t repeatedPositionIndex = 0;
  ChessPiece *pickedUpPiece = nullptr;
  ChessMove move[CHESS_MOVE_MAX];
  uint16_t move_index = 0;
  ChessGameState gameState = ChessGameState::NotStarted;
  ChessGameResult gameResult = ChessGameResult::Draw;
  uint8_t whiteWrongMoves = 0;
  uint8_t blackWrongMoves = 0;
  uint8_t movesFor75Rule = 0;
  uint8_t repeatedPosition = 0;
  uint8_t highlightedPositions[8][8];
  ChessPiece *castlingRook = nullptr;
  ChessPosition *castlingRookPosition = nullptr;
  ChessPosition *enPassantPosition = nullptr;
  int lastWrongMoveWhite = -1;
  int lastWrongMoveBlack = -1;
  ChessPosition *positionsToExcludeFromWrongMoves[50];
  uint8_t positionsToExcludeFromWrongMovesCount = 0;
  bool shouldWaitForTimmer = false;
  bool waitingForTimmer = false;
  ChessPiece *promotionPiece = nullptr;
  bool highlightWhites = true;
  bool highlightBlacks = true;

  // void highlightPositions(ChessPosition *position, uint8_t count);
  ChessColor getCurrentPlayerColor();
  uint8_t getAvailablePositions(ChessPiece *piece,
                                ChessPosition *chessPositions);
  uint8_t filterAvailablePositions(ChessPosition *chessPositions, uint8_t count,
                                   ChessPiece *piece);
  bool isKingChecked(ChessColor color);
  bool isKingCheckmate(ChessColor color);
  bool isStalemate(ChessColor color);
  bool isMatPossible();
  bool willBeKingChecked(ChessPosition *kingPosition, ChessColor color);
  ChessPiece *findPiece(ChessPosition *position);
  ChessPiece *findPiece(ChessPieceType type, ChessColor color);
  uint8_t findPieces(ChessPieceType type, ChessColor color, ChessPiece *pieces);
  int isOccupied(ChessPosition *position, ChessColor color);
  void createMove(ChessMove *move, ChessPosition *from, ChessPosition *to);
  void applyMove(ChessMove *move);
  int checkPiecesArrangement();
  void assignPiecesToPositions();
  void pawnPromotion(ChessPosition *position);

  void startSimulation();
  void endSimulation();
  void simulateMove(ChessMove *move);
  bool isCastlingPossible(ChessCastlingType type, ChessColor color);
  ChessPosition *getPosition(const char *position);
  void clear();

  uint8_t getKingAvailablePositions(ChessPiece *king, ChessPosition *positions);

  void saveRepeatedPosition();
  void clearRepeatedPositions();
  bool are3RepeatedPositions();
};

#endif  // _CHESS_LOGIC_H_
