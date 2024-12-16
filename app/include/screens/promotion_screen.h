/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef PROMOTION_SCREEN_H
#define PROMOTION_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"
#include "timer.h"

/**
 * @brief This class represents the home screen of the application
 */
class PromotionScreen : public BaseScreen {
 public:
  explicit PromotionScreen(ChessColor color);
  ~PromotionScreen();

  const char* getName() override { return "promotion"; }
  void init() override;
  void update() override;

 private:
  Timer* timer = nullptr;
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Label52 = nullptr;
  lv_obj_t* ui_Label53 = nullptr;
  lv_obj_t* ui_Label54 = nullptr;
};

inline PromotionScreen whitePromotionScreen(ChessColor::White);
inline PromotionScreen blackPromotionScreen(ChessColor::Black);

#endif  // PROMOTION_SCREEN_H
