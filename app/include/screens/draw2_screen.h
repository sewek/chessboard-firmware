/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef DRAW2_SCREEN_H
#define DRAW2_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class Draw2Screen : public BaseScreen {
 public:
  explicit Draw2Screen(ChessColor color);
  ~Draw2Screen();

  const char* getName() override { return "draw2"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Label44 = nullptr;
  lv_obj_t* ui_Label65 = nullptr;
};

inline Draw2Screen whiteDraw2Screen(ChessColor::White);
inline Draw2Screen blackDraw2Screen(ChessColor::Black);

#endif  // DRAW2_SCREEN_H
