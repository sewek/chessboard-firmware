/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef TIME_SCREEN_H
#define TIME_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class TimeScreen : public BaseScreen {
 public:
  explicit TimeScreen(ChessColor color);
  ~TimeScreen();

  const char* getName() override { return "time"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button15 = nullptr;
  lv_obj_t* ui_Button16 = nullptr;
  lv_obj_t* ui_Button17 = nullptr;
  lv_obj_t* ui_Button18 = nullptr;
  lv_obj_t* ui_Button19 = nullptr;
  lv_obj_t* ui_Button20 = nullptr;
  lv_obj_t* ui_Label26 = nullptr;
  lv_obj_t* ui_Label27 = nullptr;
  lv_obj_t* ui_Label28 = nullptr;
  lv_obj_t* ui_Label29 = nullptr;
  lv_obj_t* ui_Label30 = nullptr;
  lv_obj_t* ui_Label31 = nullptr;
  lv_obj_t* ui_Label32 = nullptr;
};

inline TimeScreen whiteTimeScreen(ChessColor::White);
inline TimeScreen blackTimeScreen(ChessColor::Black);

#endif  // TIME_SCREEN_H
