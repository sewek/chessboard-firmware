/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef DRAW_SCREEN_H
#define DRAW_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"
#include "timer.h"

/**
 * @brief This class represents the home screen of the application
 */
class DrawScreen : public BaseScreen {
 public:
  explicit DrawScreen(ChessColor color);
  ~DrawScreen();

  const char* getName() override { return "draw"; }
  void init() override;
  void update() override;

 private:
  Timer* timer = nullptr;
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button8 = nullptr;
  lv_obj_t* ui_Button9 = nullptr;
  lv_obj_t* ui_Label13 = nullptr;
  lv_obj_t* ui_Label14 = nullptr;
  lv_obj_t* ui_Label15 = nullptr;
};

inline DrawScreen whiteDrawScreen(ChessColor::White);
inline DrawScreen blackDrawScreen(ChessColor::Black);

#endif  // DRAW_SCREEN_H
