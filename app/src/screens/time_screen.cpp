/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the TimeScreen class
 */

#include "screens/time_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "screens/screen_controller.h"
#include "timer.h"

extern Buttons buttons;
extern ScreenController screenController;
extern Timer whiteTimer;
extern Timer blackTimer;

TimeScreen::TimeScreen(ChessColor color) : BaseScreen(color) {}

TimeScreen::~TimeScreen() {}

void TimeScreen::init() {
  this->buttonIndex = 0;
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);
  this->timer = (this->color == ChessColor::White) ? &whiteTimer : &blackTimer;

  switch (this->timer->getElapsedTime()) {
    case 60 * 5:
      this->buttonIndex = 1;
      break;
    case 60 * 10:
      this->buttonIndex = 2;
      break;
    case 60 * 15:
      this->buttonIndex = 3;
      break;
    case 60 * 30:
      this->buttonIndex = 4;
      break;
    case 60 * 60:
      this->buttonIndex = 5;
      break;
    default:
      this->buttonIndex = 0;
      break;
  }

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
  lv_obj_set_style_bg_color(this->ui_Button15, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
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
  lv_obj_set_style_bg_color(this->ui_Button16, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
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
  lv_obj_set_style_bg_color(this->ui_Button17, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
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
  lv_obj_set_style_text_font(this->ui_Label32, &lv_font_roboto_36,
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
  lv_obj_set_style_bg_color(this->ui_Button18, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
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
  lv_obj_set_style_bg_color(this->ui_Button19, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
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
  lv_obj_set_style_bg_color(this->ui_Button20, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
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
    this->buttonIndex = (this->buttonIndex + 5) % 6;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 1) % 6;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_add_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 2:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 3:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 4:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    case 5:
      lv_obj_clear_state(this->ui_Button15, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button16, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button17, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button18, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button19, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button20, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    switch (this->buttonIndex) {
      case 1:
        this->timer->setElapsedTime(60 * 5);
        break;
      case 2:
        this->timer->setElapsedTime(60 * 10);
        break;
      case 3:
        this->timer->setElapsedTime(60 * 15);
        break;
      case 4:
        this->timer->setElapsedTime(60 * 30);
        break;
      case 5:
        this->timer->setElapsedTime(60 * 60);
        break;
      default:
        this->timer->setElapsedTime(0);
        break;
    }
    screenController.navigateTo(this->color, "settings");
  }

  if (buttons.isPressed(this->color, ButtonType::Cancel)) {
    screenController.navigateTo(this->color, "settings");
  }
}
