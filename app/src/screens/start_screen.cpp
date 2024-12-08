/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the StartScreen class
 */

#include "screens/start_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

StartScreen::StartScreen(ChessColor color) : BaseScreen(color) {}

StartScreen::~StartScreen() {}

void StartScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Button5 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button5, 315);
  lv_obj_set_height(this->ui_Button5, 50);
  lv_obj_set_align(this->ui_Button5, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button5, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button5, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button5, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button5, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button5, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button5, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button5, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button5, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label6 = lv_label_create(this->ui_Button5);
  lv_obj_set_width(this->ui_Label6, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label6, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label6, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label6, "Poddaj się");
  lv_obj_set_style_text_color(this->ui_Label6, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label6, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label6, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button4 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button4, 315);
  lv_obj_set_height(this->ui_Button4, 50);
  lv_obj_set_x(this->ui_Button4, 0);
  lv_obj_set_y(this->ui_Button4, -50);
  lv_obj_set_align(this->ui_Button4, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button4, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button4, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button4, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button4, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button4, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button4, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button4, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button4, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label5 = lv_label_create(this->ui_Button4);
  lv_obj_set_width(this->ui_Label5, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label5, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label5, 0);
  lv_obj_set_y(this->ui_Label5, 5);
  lv_obj_set_align(this->ui_Label5, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label5, "Zaproponuj remis");
  lv_obj_set_style_text_color(this->ui_Label5, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label5, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label5, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label7 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label7, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label7, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label7, -75);
  lv_obj_set_y(this->ui_Label7, 200);
  lv_obj_set_align(this->ui_Label7, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label7, "Ilość błędów:");
  lv_obj_set_style_text_color(this->ui_Label7, lv_color_hex(0x282626),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label7, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label7, &lv_font_roboto_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label8 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label8, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label8, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label8, 0);
  lv_obj_set_y(this->ui_Label8, 200);
  lv_obj_set_align(this->ui_Label8, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label8, "0");
  lv_obj_set_style_text_color(this->ui_Label8, lv_color_hex(0x282626),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label8, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label8, &lv_font_roboto_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label9 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label9, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label9, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label9, 0);
  lv_obj_set_y(this->ui_Label9, -150);
  lv_obj_set_align(this->ui_Label9, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label9, "00:00");
  lv_obj_set_style_text_font(this->ui_Label9, &lv_font_roboto_46,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void StartScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 2;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 2) % 2;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_clear_state(this->ui_Button4, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button5, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_add_state(this->ui_Button4, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button5, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    switch (this->buttonIndex) {
      case 0:
        // LOG_INF("Draw button pressed\n");
        break;
      case 1:
        // LOG_INF("Give up button pressed\n");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }
}
