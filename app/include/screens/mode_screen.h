/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef MODE_SCREEN_H
#define MODE_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class ModeScreen : public BaseScreen {
 public:
  explicit ModeScreen(ChessColor color);
  ~ModeScreen();

  const char* getName() override { return "mode"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button21 = nullptr;
  lv_obj_t* ui_Button22 = nullptr;
  lv_obj_t* ui_Label33 = nullptr;
  lv_obj_t* ui_Label34 = nullptr;
  lv_obj_t* ui_Label36 = nullptr;
};

inline ModeScreen whiteModeScreen(ChessColor::White);
inline ModeScreen blackModeScreen(ChessColor::Black);

#endif  // MODE_SCREEN_H
