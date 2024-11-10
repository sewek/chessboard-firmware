#ifndef CHESS_EVENTS_H
#define CHESS_EVENTS_H

#include "chess_move.h"
#include "chess_position.h"
#include "chess_types.h"

#define CHESS_EVENTS_MAX_LISTENERS 10

using ChessCallbackUnknwon = void (*)();
using ChessCallbackEmpty = void (*)();
using ChessCallbackWithMove = void (*)(ChessMove*);
using ChessCallbackWithPosition = void (*)(ChessPosition*);
using ChessCallbackWithPositionAndHighlight = void (*)(ChessPosition*,
                                                       ChessHighlightType);

class ChessEvents {
 public:
  uint8_t MAX_LISTENERS = CHESS_EVENTS_MAX_LISTENERS;

  ChessEvents();
  ~ChessEvents();

  void addListener(ChessEventType event, ChessCallbackEmpty callback);
  void addListener(ChessEventType event, ChessCallbackWithMove callback);
  void addListener(ChessEventType event, ChessCallbackWithPosition callback);
  void addListener(ChessEventType event,
                   ChessCallbackWithPositionAndHighlight callback);

  void removeListener(ChessEventType event, ChessCallbackEmpty callback);
  void removeListener(ChessEventType event, ChessCallbackWithMove callback);
  void removeListener(ChessEventType event, ChessCallbackWithPosition callback);
  void removeListener(ChessEventType event,
                      ChessCallbackWithPositionAndHighlight callback);

 protected:
  void notifyGameStarted();
  void notifyGameEnded();
  void notifyMoveMade(ChessMove* move);
  void notifyHighlightSquare(ChessPosition* position, ChessHighlightType type);
  void notifyUnhighlightSquare(ChessPosition* position);
  void notifyGameCannotStart(ChessPosition* position);

 private:
  uint8_t callbackCountGameStarted_ = 0;
  uint8_t callbackCountGameEnded_ = 0;
  uint8_t callbackCountMoveMade_ = 0;
  uint8_t callbackCountHighlightSquare_ = 0;
  uint8_t callbackCountUnhighlightSquare_ = 0;
  uint8_t callbackCountGameCantStart_ = 0;

  ChessCallbackEmpty callbacksGameStarted_[CHESS_EVENTS_MAX_LISTENERS];
  ChessCallbackEmpty callbacksGameEnded_[CHESS_EVENTS_MAX_LISTENERS];
  ChessCallbackWithMove callbacksMoveMade_[CHESS_EVENTS_MAX_LISTENERS];
  ChessCallbackWithPositionAndHighlight
      callbacksHighlightSquare_[CHESS_EVENTS_MAX_LISTENERS];
  ChessCallbackWithPosition
      callbacksUnhighlightSquare_[CHESS_EVENTS_MAX_LISTENERS];
  ChessCallbackWithPosition callbacksGameCantStart_[CHESS_EVENTS_MAX_LISTENERS];

  void removeListener(ChessCallbackUnknwon callback,
                      ChessCallbackUnknwon* array, uint8_t* count);
};

#endif  // CHESS_EVENTS_H
