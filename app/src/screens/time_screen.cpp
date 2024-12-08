/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the TimeScreen class
 */

#include "screens/time_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

TimeScreen::TimeScreen(ChessColor color) : BaseScreen(color) {}

TimeScreen::~TimeScreen() {}

void TimeScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Button15 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button15, 315);
  lv_obj_set_height(this->ui_Button15, 50);
  lv_obj_set_x(this->ui_Button15, 0);
  lv_obj_set_y(this->ui_Button15, -110);
  lv_obj_set_align(this->ui_Button15, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button15,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button15, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button15, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button15, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button15, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button15, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button15, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button15, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button15, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label26 = lv_label_create(this->ui_Button15);
  lv_obj_set_width(this->ui_Label26, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label26, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label26, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label26, "Brak");
  lv_obj_set_style_text_color(this->ui_Label26, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label26, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label26, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button16 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button16, 315);
  lv_obj_set_height(this->ui_Button16, 50);
  lv_obj_set_x(this->ui_Button16, 0);
  lv_obj_set_y(this->ui_Button16, -60);
  lv_obj_set_align(this->ui_Button16, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button16,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button16, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button16, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button16, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button16, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button16, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button16, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button16, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button16, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label28 = lv_label_create(this->ui_Button16);
  lv_obj_set_width(this->ui_Label28, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label28, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label28, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label28, "5 minut");
  lv_obj_set_style_text_color(this->ui_Label28, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label28, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label28, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button17 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button17, 315);
  lv_obj_set_height(this->ui_Button17, 50);
  lv_obj_set_x(this->ui_Button17, 0);
  lv_obj_set_y(this->ui_Button17, -10);
  lv_obj_set_align(this->ui_Button17, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button17,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button17, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button17, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button17, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button17, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button17, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button17, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button17, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button17, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label30 = lv_label_create(this->ui_Button17);
  lv_obj_set_width(this->ui_Label30, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label30, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label30, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label30, "10 minut");
  lv_obj_set_style_text_color(this->ui_Label30, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label30, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label30, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label32 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label32, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label32, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label32, 0);
  lv_obj_set_y(this->ui_Label32, -180);
  lv_obj_set_align(this->ui_Label32, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label32, "Czas gry");
  lv_obj_set_style_text_color(this->ui_Label32, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label32, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label32, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label32, &lv_font_roboto_34,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button18 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button18, 315);
  lv_obj_set_height(this->ui_Button18, 50);
  lv_obj_set_x(this->ui_Button18, 0);
  lv_obj_set_y(this->ui_Button18, 40);
  lv_obj_set_align(this->ui_Button18, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button18,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button18, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button18, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button18, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button18, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button18, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button18, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button18, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button18, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label27 = lv_label_create(this->ui_Button18);
  lv_obj_set_width(this->ui_Label27, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label27, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label27, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label27, "15 minut");
  lv_obj_set_style_text_color(this->ui_Label27, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label27, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label27, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button19 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button19, 315);
  lv_obj_set_height(this->ui_Button19, 50);
  lv_obj_set_x(this->ui_Button19, 0);
  lv_obj_set_y(this->ui_Button19, 90);
  lv_obj_set_align(this->ui_Button19, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button19,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button19, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button19, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button19, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button19, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button19, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button19, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button19, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button19, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label29 = lv_label_create(this->ui_Button19);
  lv_obj_set_width(this->ui_Label29, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label29, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label29, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label29, "30 minut");
  lv_obj_set_style_text_color(this->ui_Label29, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label29, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label29, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button20 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button20, 315);
  lv_obj_set_height(this->ui_Button20, 50);
  lv_obj_set_x(this->ui_Button20, 0);
  lv_obj_set_y(this->ui_Button20, 140);
  lv_obj_set_align(this->ui_Button20, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button20,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button20, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button20, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button20, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button20, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button20, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button20, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button20, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button20, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label31 = lv_label_create(this->ui_Button20);
  lv_obj_set_width(this->ui_Label31, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label31, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label31, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label31, "60 minut");
  lv_obj_set_style_text_color(this->ui_Label31, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label31, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label31, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void TimeScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 6;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 2) % 6;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 2:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 3:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 4:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 5:
      lv_obj_add_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    switch (this->buttonIndex) {
      case 0:
        // LOG_INF("Null button pressed\n");
        break;
      case 1:
        // LOG_INF("5 button pressed\n");
        break;
      case 2:
        // LOG_INF("10 button pressed\n");
        break;
      case 3:
        // LOG_INF("15 button pressed\n");
        break;
      case 4:
        // LOG_INF("30 button pressed\n");
        break;
      case 5:
        // LOG_INF("60 button pressed\n");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }
}
