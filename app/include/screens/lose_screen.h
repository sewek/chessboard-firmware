/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef LOSE_SCREEN_H
#define LOSE_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class LoseScreen : public BaseScreen {
 public:
  explicit LoseScreen(ChessColor color);
  ~LoseScreen();

  const char* getName() override { return "lose"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Label45 = nullptr;
  lv_obj_t* ui_Label66 = nullptr;
};

inline LoseScreen whiteLoseScreen(ChessColor::White);
inline LoseScreen blackLoseScreen(ChessColor::Black);

#endif  // LOSE_SCREEN_H
