#ifndef _CHESS_LOGIC_H_
#define _CHESS_LOGIC_H_

#include "chess_board.h"
#include "chess_events.h"
#include "chess_game.h"
#include "chess_types.h"

class Chess : public ChessEvents {
 public:
  Chess();
  ~Chess();

  /**
   * @brief Notify about chess tile action.
   */
  void notifyTileAction(ChessPosition *position, ChessTileActionType action);
};

#endif  // _CHESS_LOGIC_H_
