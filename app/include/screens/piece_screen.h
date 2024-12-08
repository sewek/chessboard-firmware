/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef PIECE_SCREEN_H
#define PIECE_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class PieceScreen : public BaseScreen {
 public:
  explicit PieceScreen(ChessColor color);
  ~PieceScreen();

  const char* getName() override { return "piece"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button29 = nullptr;
  lv_obj_t* ui_Button30 = nullptr;
  lv_obj_t* ui_Button31 = nullptr;
  lv_obj_t* ui_Button32 = nullptr;
  lv_obj_t* ui_Label55 = nullptr;
  lv_obj_t* ui_Label56 = nullptr;
  lv_obj_t* ui_Label57 = nullptr;
  lv_obj_t* ui_Label58 = nullptr;
  lv_obj_t* ui_Label59 = nullptr;
  lv_obj_t* ui_Image8 = nullptr;
  lv_obj_t* ui_Image3 = nullptr;
  lv_obj_t* ui_Image4 = nullptr;
  lv_obj_t* ui_Image5 = nullptr;
};

inline PieceScreen whitePieceScreen(ChessColor::White);
inline PieceScreen blackPieceScreen(ChessColor::Black);

#endif  // PIECE_SCREEN_H
