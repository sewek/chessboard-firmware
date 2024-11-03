#include "chess_events.h"

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
  if (event == ChessEventType::HighlightSquare) {
    this->callbacksHighlightSquare_[this->callbackCountHighlightSquare_++] =
        callback;
  }

  if (event == ChessEventType::UnhighlightSquare) {
    this->callbacksUnhighlightSquare_[this->callbackCountUnhighlightSquare_++] =
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
  if (event == ChessEventType::HighlightSquare) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksHighlightSquare_,
                         &this->callbackCountHighlightSquare_);
  }

  if (event == ChessEventType::UnhighlightSquare) {
    this->removeListener(
        (ChessCallbackUnknwon)callback,
        (ChessCallbackUnknwon*)this->callbacksUnhighlightSquare_,
        &this->callbackCountUnhighlightSquare_);
  }
}

void ChessEvents::notifyGameStarted() {
  for (const auto& callback : this->callbacksGameStarted_) {
    if (callback != nullptr) {
      callback();
    }
  }
}

void ChessEvents::notifyGameEnded() {
  for (const auto& callback : this->callbacksGameEnded_) {
    if (callback != nullptr) {
      callback();
    }
  }
}

void ChessEvents::notifyMoveMade(ChessMove move) {
  for (const auto& callback : this->callbacksMoveMade_) {
    if (callback != nullptr) {
      callback(move);
    }
  }
}

void ChessEvents::notifyHighlightSquare(ChessPosition position) {
  for (const auto& callback : this->callbacksHighlightSquare_) {
    if (callback != nullptr) {
      callback(position);
    }
  }
}

void ChessEvents::notifyUnhighlightSquare(ChessPosition position) {
  for (const auto& callback : this->callbacksUnhighlightSquare_) {
    if (callback != nullptr) {
      callback(position);
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
