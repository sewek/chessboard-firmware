/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class WinScreen : public BaseScreen {
 public:
  explicit WinScreen(ChessColor color);
  ~WinScreen();

  const char* getName() override { return "win"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Label43 = nullptr;
  lv_obj_t* ui_Label64 = nullptr;
};

inline WinScreen whiteWinScreen(ChessColor::White);
inline WinScreen blackWinScreen(ChessColor::Black);

#endif  // WIN_SCREEN_H
