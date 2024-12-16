/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef ENPASSANT_SCREEN_H
#define ENPASSANT_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"
#include "timer.h"

/**
 * @brief This class represents the home screen of the application
 */
class EnPassantScreen : public BaseScreen {
 public:
  explicit EnPassantScreen(ChessColor color);
  ~EnPassantScreen();

  const char* getName() override { return "en_passant"; }
  void init() override;
  void update() override;

 private:
  Timer* timer = nullptr;
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Label49 = nullptr;
  lv_obj_t* ui_Label50 = nullptr;
  lv_obj_t* ui_Label51 = nullptr;
  lv_obj_t* ui_Image2 = nullptr;
};

inline EnPassantScreen whiteEnPassantScreen(ChessColor::White);
inline EnPassantScreen blackEnPassantScreen(ChessColor::Black);

#endif  // ENPASSANT_SCREEN_H
