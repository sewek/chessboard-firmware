/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class StartScreen : public BaseScreen {
 public:
  explicit StartScreen(ChessColor color);
  ~StartScreen();

  const char* getName() override { return "start"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button5 = nullptr;
  lv_obj_t* ui_Button4 = nullptr;
  lv_obj_t* ui_Label6 = nullptr;
  lv_obj_t* ui_Label5 = nullptr;
  lv_obj_t* ui_Label7 = nullptr;
  lv_obj_t* ui_Label8 = nullptr;
  lv_obj_t* ui_Label9 = nullptr;
};

inline StartScreen whiteStartScreen(ChessColor::White);
inline StartScreen blackStartScreen(ChessColor::Black);

#endif  // START_SCREEN_H
