/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef OPEN_SCREEN_H
#define OPEN_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class OpenScreen : public BaseScreen {
 public:
  explicit OpenScreen(ChessColor color);
  ~OpenScreen();

  const char* getName() override { return "open"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button23 = nullptr;
  lv_obj_t* ui_Button24 = nullptr;
  lv_obj_t* ui_Button25 = nullptr;
  lv_obj_t* ui_Button26 = nullptr;
  lv_obj_t* ui_Button27 = nullptr;
  lv_obj_t* ui_Button28 = nullptr;
  lv_obj_t* ui_Label35 = nullptr;
  lv_obj_t* ui_Label37 = nullptr;
  lv_obj_t* ui_Label38 = nullptr;
  lv_obj_t* ui_Label39 = nullptr;
  lv_obj_t* ui_Label40 = nullptr;
  lv_obj_t* ui_Label41 = nullptr;
  lv_obj_t* ui_Label42 = nullptr;
};

inline OpenScreen whiteOpenScreen(ChessColor::White);
inline OpenScreen blackOpenScreen(ChessColor::Black);

#endif  // OPEN_SCREEN_H
