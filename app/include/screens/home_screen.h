/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include "base_screen.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class HomeScreen : public BaseScreen {
 public:
  explicit HomeScreen(ChessColor color);
  ~HomeScreen();

  const char* getName() override { return "home"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button1 = nullptr;
  lv_obj_t* ui_Button2 = nullptr;
  lv_obj_t* ui_Button3 = nullptr;
  lv_obj_t* ui_Label1 = nullptr;
  lv_obj_t* ui_Label2 = nullptr;
  lv_obj_t* ui_Label3 = nullptr;
  lv_obj_t* ui_Label4 = nullptr;
  lv_obj_t* ui_Image1 = nullptr;
  lv_obj_t* ui_Image6 = nullptr;
};

inline HomeScreen whiteHomeScreen(ChessColor::White);
inline HomeScreen blackHomeScreen(ChessColor::Black);

#endif  // HOME_SCREEN_H
