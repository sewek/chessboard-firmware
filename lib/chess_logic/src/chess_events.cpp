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
                              ChessCallbackWithColor callback) {
  if (event == ChessEventType::Castling) {
    this->callbacksCastling_[this->callbackCountCastling_++] = callback;
  }

  if (event == ChessEventType::Promotion) {
    this->callbacksPromotion_[this->callbackCountPromotion_++] = callback;
  }

  if (event == ChessEventType::EnPassant) {
    this->callbacksEnPassant_[this->callbackCountEnPassant_++] = callback;
  }

  if (event == ChessEventType::Error) {
    this->callbacksError_[this->callbackCountError_++] = callback;
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

void ChessEvents::removeListener(ChessEventType event,
                                 ChessCallbackWithColor callback) {
  if (event == ChessEventType::Castling) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksCastling_,
                         &this->callbackCountCastling_);
  }

  if (event == ChessEventType::Promotion) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksPromotion_,
                         &this->callbackCountPromotion_);
  }

  if (event == ChessEventType::EnPassant) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksEnPassant_,
                         &this->callbackCountEnPassant_);
  }

  if (event == ChessEventType::Error) {
    this->removeListener((ChessCallbackUnknwon)callback,
                         (ChessCallbackUnknwon*)this->callbacksError_,
                         &this->callbackCountError_);
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
  for (int i = 0; i < this->callbackCountHighlightSquare_; i++) {
    if (this->callbacksHighlightSquare_[i]) {
      this->callbacksHighlightSquare_[i](position, type);
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

void ChessEvents::notifyCastling(ChessColor color) {
  for (int i = 0; i < this->callbackCountCastling_; i++) {
    if (this->callbacksCastling_[i]) {
      this->callbacksCastling_[i](color);
    }
  }
}

void ChessEvents::notifyPromotion(ChessColor color) {
  for (int i = 0; i < this->callbackCountPromotion_; i++) {
    if (this->callbacksPromotion_[i]) {
      this->callbacksPromotion_[i](color);
    }
  }
}

void ChessEvents::notifyEnPassant(ChessColor color) {
  for (int i = 0; i < this->callbackCountEnPassant_; i++) {
    if (this->callbacksEnPassant_[i]) {
      this->callbacksEnPassant_[i](color);
    }
  }
}

void ChessEvents::notifyError(ChessColor color) {
  for (int i = 0; i < this->callbackCountError_; i++) {
    if (this->callbacksError_[i]) {
      this->callbacksError_[i](color);
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
