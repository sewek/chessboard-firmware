#ifndef CHESS_OPENING_H
#define CHESS_OPENING_H

#define CHESS_OPENING_MAX_NAME 50
#define CHESS_OPENING_MAX_MOVES 50

#include "chess_move.h"
#include "chess_types.h"

typedef struct {
  const char name[CHESS_OPENING_MAX_NAME];
  uint8_t movesCount;
  ChessMove moves[CHESS_OPENING_MAX_MOVES];
} ChessOpening;

#endif  // CHESS_OPENING_H