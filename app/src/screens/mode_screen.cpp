/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the ModeScreen class
 */

#include "screens/mode_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "screens/screen_controller.h"

extern Buttons buttons;
extern ScreenController screenController;

ModeScreen::ModeScreen(ChessColor color) : BaseScreen(color) {}

ModeScreen::~ModeScreen() {}

void ModeScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Button21 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button21, 315);
  lv_obj_set_height(this->ui_Button21, 50);
  lv_obj_set_x(this->ui_Button21, 0);
  lv_obj_set_y(this->ui_Button21, -110);
  lv_obj_set_align(this->ui_Button21, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button21,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button21, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button21, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button21, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button21, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(this->ui_Button21, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button21, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button21, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button21, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button21, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label33 = lv_label_create(this->ui_Button21);
  lv_obj_set_width(this->ui_Label33, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label33, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label33, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label33, "Z podswietleniem");
  lv_obj_set_style_text_color(this->ui_Label33, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label33, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label33, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button22 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button22, 315);
  lv_obj_set_height(this->ui_Button22, 50);
  lv_obj_set_x(this->ui_Button22, 0);
  lv_obj_set_y(this->ui_Button22, -60);
  lv_obj_set_align(this->ui_Button22, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button22,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button22, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button22, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button22, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button22, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(this->ui_Button22, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button22, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button22, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button22, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button22, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label34 = lv_label_create(this->ui_Button22);
  lv_obj_set_width(this->ui_Label34, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label34, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label34, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label34, "Bez podświetlenia");
  lv_obj_set_style_text_color(this->ui_Label34, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label34, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label34, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label36 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label36, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label36, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label36, 0);
  lv_obj_set_y(this->ui_Label36, -180);
  lv_obj_set_align(this->ui_Label36, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label36, "Tryb gry");
  lv_obj_set_style_text_color(this->ui_Label36, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label36, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label36, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label36, &lv_font_roboto_36,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ModeScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 2;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 1) % 2;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_add_state(this->ui_Button21, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button22, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_clear_state(this->ui_Button21, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button22, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    switch (this->buttonIndex) {
      case 0:
        // LOG_INF("With button pressed\n");
        break;
      case 1:
        // LOG_INF("Without button pressed\n");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }

  if (buttons.isPressed(this->color, ButtonType::Cancel)) {
    screenController.navigateTo(this->color, "settings");
  }
}
