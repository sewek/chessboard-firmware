#ifndef _CHESS_LOGIC_H_
#define _CHESS_LOGIC_H_

#include "chess_board.h"
#include "chess_events.h"
#include "chess_game.h"
#include "chess_piece.h"
#include "chess_types.h"

#define CHESS_MOVE_MAX 100

class Chess : public ChessEvents {
 public:
  Chess();
  ~Chess();

  /**
   * @brief Notify about chess tile action.
   */
  void notifyTileAction(ChessPosition *position, ChessTileActionType action);

 private:
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
  ChessPiece piece[32];
  ChessMove move[CHESS_MOVE_MAX];
  uint16_t move_index = 0;
};

#endif  // _CHESS_LOGIC_H_
