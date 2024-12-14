/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the DrawScreen class
 */

#include "screens/draw_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

DrawScreen::DrawScreen(ChessColor color) : BaseScreen(color) {}

DrawScreen::~DrawScreen() {}

void DrawScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label13 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label13, lv_pct(100));
  lv_obj_set_height(this->ui_Label13, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label13, 0);
  lv_obj_set_y(this->ui_Label13, -145);
  lv_obj_set_align(this->ui_Label13, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label13, "Chcesz zaproponować remis?");
  lv_obj_set_style_text_color(this->ui_Label13, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label13, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label13, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label13, &lv_font_roboto_36,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button8 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button8, 315);
  lv_obj_set_height(this->ui_Button8, 50);
  lv_obj_set_x(this->ui_Button8, 0);
  lv_obj_set_y(this->ui_Button8, -50);
  lv_obj_set_align(this->ui_Button8, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button8, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button8, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button8, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button8, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button8, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button8, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button8, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button8, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label14 = lv_label_create(this->ui_Button8);
  lv_obj_set_width(this->ui_Label14, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label14, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label14, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label14, "Tak");
  lv_obj_set_style_text_color(this->ui_Label14, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label14, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label14, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button9 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button9, 315);
  lv_obj_set_height(this->ui_Button9, 50);
  lv_obj_set_align(this->ui_Button9, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button9, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button9, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button9, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button9, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button9, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button9, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button9, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button9, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label15 = lv_label_create(this->ui_Button9);
  lv_obj_set_width(this->ui_Label15, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label15, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label15, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label15, "Nie");
  lv_obj_set_style_text_color(this->ui_Label15, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label15, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label15, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void DrawScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 2;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 2) % 2;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_clear_state(this->ui_Button8, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button9, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_add_state(this->ui_Button8, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button9, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    switch (this->buttonIndex) {
      case 0:
        // LOG_INF("Yes button pressed\n");
        break;
      case 1:
        // LOG_INF("No button pressed\n");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }
}
