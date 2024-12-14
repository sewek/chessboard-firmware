/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef CASTLING_SCREEN_H
#define CASTLING_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class CastlingScreen : public BaseScreen {
 public:
  explicit CastlingScreen(ChessColor color);
  ~CastlingScreen();

  const char* getName() override { return "castling"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Label47 = nullptr;
  lv_obj_t* ui_Label46 = nullptr;
  lv_obj_t* ui_Label48 = nullptr;
  lv_obj_t* ui_Image7 = nullptr;
};

inline CastlingScreen whiteCastlingScreen(ChessColor::White);
inline CastlingScreen blackCastlingScreen(ChessColor::Black);

#endif  // CASTLING_SCREEN_H
