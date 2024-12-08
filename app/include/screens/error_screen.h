/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef ERROR_SCREEN_H
#define ERROR_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class ErrorScreen : public BaseScreen {
 public:
  explicit ErrorScreen(ChessColor color);
  ~ErrorScreen();

  const char* getName() override { return "error"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Label60 = nullptr;
  lv_obj_t* ui_Label61 = nullptr;
  lv_obj_t* ui_Label62 = nullptr;
};

inline ErrorScreen whiteErrorScreen(ChessColor::White);
inline ErrorScreen blackErrorScreen(ChessColor::Black);

#endif  // ERROR_SCREEN_H
