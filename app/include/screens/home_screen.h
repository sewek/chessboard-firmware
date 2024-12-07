/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <base_screen.h>

#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class HomeScreen : public BaseScreen {
 public:
  HomeScreen();
  ~HomeScreen();

  void init() override;
  void update() override;

 private:
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

#endif  // HOME_SCREEN_H
