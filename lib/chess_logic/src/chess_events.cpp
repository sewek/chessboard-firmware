#include "chess_events.h"

#include "chess_log.h"

ChessEvents::ChessEvents() = default;

ChessEvents::~ChessEvents() = default;

void ChessEvents::addListener(ChessEventType event,
                              ChessCallbackEmpty callback) {
  if (event == ChessEventType::GameStarted) {
    this->callbacksGameStarted_[this->callbackCountGameStarted_++] = callback;
  }

  if (event == ChessEventType::GameEnded) {
    this->callbacksGameEnded_[this->callbackCountGameEnded_++] = callback;
  }
}

void ChessEvents::addListener(ChessEventType event,
                              ChessCallbackWithMove callback) {
  if (event == ChessEventType::MoveMade) {
    this->callbacksMoveMade_[this->callbackCountMoveMade_++] = callback;
  }
}

void ChessEvents::addListener(ChessEventType event,
                              ChessCallbackWithPosition callback) {
  if (event == ChessEventType::UnhighlightSquare) {
    this->callbacksUnhighlightSquare_[this->callbackCountUnhighlightSquare_++] =
        callback;
  }

  if (event == ChessEventType::GameCannotStart) {
    this->callbacksGameCantStart_[this->callbackCountGameCantStart_++] =
        (callback);
  }
}

void ChessEvents::addListener(ChessEventType event,
                              ChessCallbackWithPositionAndHighlight callback) {
  if (event == ChessEventType::HighlightSquare) {
    this->callbacksHighlightSquare_[this->callbackCountHighlightSquare_++] =
        callback;
  }
}

void ChessEvents::removeListener(ChessEventType event,
                                 ChessCallbackEmpty callback) {
  if (event == ChessEventType::GameStarted) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksGameStarted_,
                         &this->callbackCountGameStarted_);
  }

  if (event == ChessEventType::GameEnded) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksGameEnded_,
                         &this->callbackCountGameEnded_);
  }
}

void ChessEvents::removeListener(ChessEventType event,
                                 ChessCallbackWithMove callback) {
  if (event == ChessEventType::MoveMade) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksMoveMade_,
                         &this->callbackCountMoveMade_);
  }
}

void ChessEvents::removeListener(ChessEventType event,
                                 ChessCallbackWithPosition callback) {
  if (event == ChessEventType::UnhighlightSquare) {
    this->removeListener(
        (ChessCallbackUnknwon)callback,
        (ChessCallbackUnknwon*)this->callbacksUnhighlightSquare_,
        &this->callbackCountUnhighlightSquare_);
  }

  if (event == ChessEventType::GameCannotStart) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksGameCantStart_,
                         &this->callbackCountGameCantStart_);
  }
}

void ChessEvents::removeListener(
    ChessEventType event, ChessCallbackWithPositionAndHighlight callback) {
  if (event == ChessEventType::HighlightSquare) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksHighlightSquare_,
                         &this->callbackCountHighlightSquare_);
  }
}

void ChessEvents::notifyGameStarted() {
  for (int i = 0; i < this->callbackCountGameStarted_; i++) {
    if (this->callbacksGameStarted_[i]) {
      this->callbacksGameStarted_[i]();
    }
  }
}

void ChessEvents::notifyGameEnded() {
  for (int i = 0; i < this->callbackCountGameEnded_; i++) {
    if (this->callbacksGameEnded_[i]) {
      this->callbacksGameEnded_[i]();
    }
  }
}

void ChessEvents::notifyMoveMade(ChessMove* move) {
  for (int i = 0; i < this->callbackCountMoveMade_; i++) {
    if (this->callbacksMoveMade_[i]) {
      this->callbacksMoveMade_[i](move);
    }
  }
}

void ChessEvents::notifyHighlightSquare(ChessPosition* position,
                                        ChessHighlightType type) {
  print_debug("Highlighting square\n");
  for (int i = 0; i < this->callbackCountHighlightSquare_; i++) {
    if (this->callbacksHighlightSquare_[i]) {
      print_debug("Executing callback %d %p\n", i,
                  this->callbacksHighlightSquare_[i]);
      this->callbacksHighlightSquare_[i](position, type);
    } else {
      print_debug("Callback %d is null\n", i);
    }
  }
}

void ChessEvents::notifyUnhighlightSquare(ChessPosition* position) {
  for (int i = 0; i < this->callbackCountUnhighlightSquare_; i++) {
    if (this->callbacksUnhighlightSquare_[i]) {
      this->callbacksUnhighlightSquare_[i](position);
    }
  }
}

void ChessEvents::notifyGameCannotStart(ChessPosition* position) {
  for (int i = 0; i < this->callbackCountGameCantStart_; i++) {
    if (this->callbacksGameCantStart_[i]) {
      this->callbacksGameCantStart_[i](position);
    }
  }
}

void ChessEvents::removeListener(ChessCallbackUnknwon callback,
                                 ChessCallbackUnknwon* array, uint8_t* count) {
  if (*count == 0) {
    return;
  }

  for (uint8_t i = 0; i < *count; i++) {
    if (array[i] == callback) {
      for (uint8_t j = i; j < *count - 1; j++) {
        array[j] = array[j + 1];
      }

      (*count)--;
      return;
    }
  }
}
