/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef GIVEUP_SCREEN_H
#define GIVEUP_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class GiveUpScreen : public BaseScreen {
 public:
  explicit GiveUpScreen(ChessColor color);
  ~GiveUpScreen();

  const char* getName() override { return "give_up"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button7 = nullptr;
  lv_obj_t* ui_Button6 = nullptr;
  lv_obj_t* ui_Label10 = nullptr;
  lv_obj_t* ui_Label12 = nullptr;
  lv_obj_t* ui_Label11 = nullptr;
};

inline GiveUpScreen whiteGiveUpScreen(ChessColor::White);
inline GiveUpScreen blackGiveUpScreen(ChessColor::Black);

#endif  // GIVEUP_SCREEN_H
