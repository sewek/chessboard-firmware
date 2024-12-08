/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the GiveUpScreen class
 */

#include "screens/giveup_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

GiveUpScreen::GiveUpScreen(ChessColor color) : BaseScreen(color) {}

GiveUpScreen::~GiveUpScreen() {}

void GiveUpScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label10 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label10, lv_pct(100));
  lv_obj_set_height(this->ui_Label10, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label10, 0);
  lv_obj_set_y(this->ui_Label10, -145);
  lv_obj_set_align(this->ui_Label10, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label10, "Chcesz się poddać?");
  lv_obj_set_style_text_color(this->ui_Label10, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label10, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label10, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label10, &lv_font_roboto_34,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button7 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button7, 315);
  lv_obj_set_height(this->ui_Button7, 50);
  lv_obj_set_x(this->ui_Button7, 0);
  lv_obj_set_y(this->ui_Button7, -50);
  lv_obj_set_align(this->ui_Button7, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button7, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button7, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button7, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button7, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button7, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button7, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button7, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button7, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label12 = lv_label_create(this->ui_Button7);
  lv_obj_set_width(this->ui_Label12, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label12, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label12, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label12, "Tak");
  lv_obj_set_style_text_color(this->ui_Label12, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label12, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label12, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button6 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button6, 315);
  lv_obj_set_height(this->ui_Button6, 50);
  lv_obj_set_align(this->ui_Button6, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button6, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button6, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button6, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button6, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button6, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button6, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button6, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button6, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label11 = lv_label_create(this->ui_Button6);
  lv_obj_set_width(this->ui_Label11, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label11, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label11, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label11, "Nie");
  lv_obj_set_style_text_color(this->ui_Label11, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label11, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label11, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void GiveUpScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 2;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 2) % 2;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_clear_state(this->ui_Button7, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button6, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_add_state(this->ui_Button7, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button6, LV_STATE_FOCUSED);
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
