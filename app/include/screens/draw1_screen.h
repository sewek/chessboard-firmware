/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef DRAW1_SCREEN_H
#define DRAW1_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class Draw1Screen : public BaseScreen {
 public:
  explicit Draw1Screen(ChessColor color);
  ~Draw1Screen();

  const char* getName() override { return "draw1"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button10 = nullptr;
  lv_obj_t* ui_Button11 = nullptr;
  lv_obj_t* ui_Label16 = nullptr;
  lv_obj_t* ui_Label17 = nullptr;
  lv_obj_t* ui_Label18 = nullptr;
};

inline Draw1Screen whiteDraw1Screen(ChessColor::White);
inline Draw1Screen blackDraw1Screen(ChessColor::Black);

#endif  // DRAW1_SCREEN_H
