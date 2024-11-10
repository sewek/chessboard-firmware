#ifndef CHESS_LOGIC_TYPES_H
#define CHESS_LOGIC_TYPES_H

#include <inttypes.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

enum class chess_piece_color_t {
  kWhite = 0,
  kBlack,
};

enum class chess_file_t {
  kA = 1,
  kB,
  kC,
  kD,
  kE,
  kF,
  kG,
  kH,
};

enum class chess_game_state_t {
  kGameNotStarted = 0,
  kGameInProgress,
  kGameEnded,
};

enum class chess_game_result_t {
  kResultWhiteWins = 0,
  kResultBlackWins,
  kResultDraw,
};

typedef struct {
  chess_file_t file;
  uint8_t rank;
} chess_position_t;

enum class ChessEventType {
  GameStarted = 0,
  GameEnded,
  MoveMade,
  HighlightSquare,
  UnhighlightSquare,
  GameCannotStart,
};

enum class ChessMoveType {
  Normal = 0,
  Capture = 1,
  Castling = 2,
  Check = 4,
  Checkmate = 8,
  Promotion = 16,
  EnPassant = 32,
};

enum class ChessColor {
  White = 0,
  Black,
};

enum class ChessPieceType {
  Pawn = 0,
  Knight,
  Bishop,
  Rook,
  Queen,
  King,
};

enum class ChessTileActionType {
  PickUp = 0,
  PutDown,
};

enum class ChessTileState {
  Available = 0,
  Taken,
};

enum class ChessCastlingType {
  None = 0,
  Short,
  Long,
};

enum class ChessGameResult {
  WhiteWins = 0,
  BlackWins,
  Draw,
};

enum class ChessGameState {
  NotStarted = 0,
  InProgress,
  Ended,
};

enum class ChessGameStartError {
  Ok = 0,
  InvalidPieceArrangement,
  GameAlreadyStarted,
};

enum class ChessHighlightType {
  NormalMove = 0,
  CaptureMove,
  Check,
  Error,
};

#endif  // CHESS_LOGIC_TYPES_H
