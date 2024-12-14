/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include "base_screen.h"
#include "fonts.h"
#include "images.h"

/**
 * @brief This class represents the home screen of the application
 */
class SettingsScreen : public BaseScreen {
 public:
  explicit SettingsScreen(ChessColor color);
  ~SettingsScreen();

  const char* getName() override { return "settings"; }
  void init() override;
  void update() override;

 private:
  uint8_t buttonIndex = 0;
  lv_obj_t* ui_Button12 = nullptr;
  lv_obj_t* ui_Button13 = nullptr;
  lv_obj_t* ui_Button14 = nullptr;
  lv_obj_t* ui_Label19 = nullptr;
  lv_obj_t* ui_Label22 = nullptr;
  lv_obj_t* ui_Label20 = nullptr;
  lv_obj_t* ui_Label23 = nullptr;
  lv_obj_t* ui_Label21 = nullptr;
  lv_obj_t* ui_Label25 = nullptr;
  lv_obj_t* ui_Label24 = nullptr;
};

inline SettingsScreen whiteSettingsScreen(ChessColor::White);
inline SettingsScreen blackSettingsScreen(ChessColor::Black);

#endif  // SETTINGS_SCREEN_H
