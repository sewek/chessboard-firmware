/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the OpenScreen class
 */

#include "screens/open_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

OpenScreen::OpenScreen(ChessColor color) : BaseScreen(color) {}

OpenScreen::~OpenScreen() {}

void OpenScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Button23 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button23, 315);
  lv_obj_set_height(this->ui_Button23, 50);
  lv_obj_set_x(this->ui_Button23, 0);
  lv_obj_set_y(this->ui_Button23, -110);
  lv_obj_set_align(this->ui_Button23, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button23,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button23, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button23, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button23, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button23, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button23, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button23, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button23, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button23, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label35 = lv_label_create(this->ui_Button23);
  lv_obj_set_width(this->ui_Label35, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label35, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label35, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label35, "Brak");
  lv_obj_set_style_text_color(this->ui_Label35, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label35, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label35, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button24 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button24, 315);
  lv_obj_set_height(this->ui_Button24, 50);
  lv_obj_set_x(this->ui_Button24, 0);
  lv_obj_set_y(this->ui_Button24, -60);
  lv_obj_set_align(this->ui_Button24, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button24,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button24, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button24, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button24, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button24, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button24, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button24, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button24, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button24, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label37 = lv_label_create(this->ui_Button24);
  lv_obj_set_width(this->ui_Label37, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label37, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label37, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label37, "Otwarcie 1");
  lv_obj_set_style_text_color(this->ui_Label37, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label37, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label37, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button25 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button25, 315);
  lv_obj_set_height(this->ui_Button25, 50);
  lv_obj_set_x(this->ui_Button25, 0);
  lv_obj_set_y(this->ui_Button25, -10);
  lv_obj_set_align(this->ui_Button25, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button25,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button25, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button25, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button25, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button25, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button25, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button25, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button25, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button25, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label38 = lv_label_create(this->ui_Button25);
  lv_obj_set_width(this->ui_Label38, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label38, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label38, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label38, "Otwarcie 2");
  lv_obj_set_style_text_color(this->ui_Label38, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label38, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label38, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label39 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label39, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label39, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label39, 0);
  lv_obj_set_y(this->ui_Label39, -180);
  lv_obj_set_align(this->ui_Label39, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label39, "Otwarcie");
  lv_obj_set_style_text_color(this->ui_Label39, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label39, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label39, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label39, &lv_font_roboto_34,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button26 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button26, 315);
  lv_obj_set_height(this->ui_Button26, 50);
  lv_obj_set_x(this->ui_Button26, 0);
  lv_obj_set_y(this->ui_Button26, 40);
  lv_obj_set_align(this->ui_Button26, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button26,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button26, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button26, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button26, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button26, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button26, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button26, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button26, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button26, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label40 = lv_label_create(this->ui_Button26);
  lv_obj_set_width(this->ui_Label40, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label40, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label40, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label40, "Otwarcie 3");
  lv_obj_set_style_text_color(this->ui_Label40, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label40, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label40, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button27 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button27, 315);
  lv_obj_set_height(this->ui_Button27, 50);
  lv_obj_set_x(this->ui_Button27, 0);
  lv_obj_set_y(this->ui_Button27, 90);
  lv_obj_set_align(this->ui_Button27, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button27,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button27, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button27, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button27, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button27, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button27, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button27, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button27, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button27, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label41 = lv_label_create(this->ui_Button27);
  lv_obj_set_width(this->ui_Label41, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label41, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label41, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label41, "Otwarcie 4");
  lv_obj_set_style_text_color(this->ui_Label41, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label41, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label41, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button28 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button28, 315);
  lv_obj_set_height(this->ui_Button28, 50);
  lv_obj_set_x(this->ui_Button28, 0);
  lv_obj_set_y(this->ui_Button28, 140);
  lv_obj_set_align(this->ui_Button28, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button28,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button28, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button28, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button28, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button28, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button28, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button28, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button28, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button28, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label42 = lv_label_create(this->ui_Button28);
  lv_obj_set_width(this->ui_Label42, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label42, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label42, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label42, "Otwarcie 5");
  lv_obj_set_style_text_color(this->ui_Label42, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label42, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label42, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void OpenScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 6;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 2) % 6;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_clear_state(this->ui_Button23, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button24, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button25, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button26, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button27, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button28, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_clear_state(this->ui_Button23, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button24, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button25, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button26, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button27, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button28, LV_STATE_FOCUSED);
      break;
    case 2:
      lv_obj_clear_state(this->ui_Button23, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button24, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button25, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button26, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button27, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button28, LV_STATE_FOCUSED);
      break;
    case 3:
      lv_obj_clear_state(this->ui_Button23, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button24, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button25, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button26, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button27, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button28, LV_STATE_FOCUSED);
      break;
    case 4:
      lv_obj_clear_state(this->ui_Button23, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button24, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button25, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button26, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button27, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button28, LV_STATE_FOCUSED);
      break;
    case 5:
      lv_obj_add_state(this->ui_Button23, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button24, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button25, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button26, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button27, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button28, LV_STATE_FOCUSED);
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
        // LOG_INF("Open 1 button pressed\n");
        break;
      case 2:
        // LOG_INF("Open 2 button pressed\n");
        break;
      case 3:
        // LOG_INF("Open 3 button pressed\n");
        break;
      case 4:
        // LOG_INF("Open 4 button pressed\n");
        break;
      case 5:
        // LOG_INF("Open 5 button pressed\n");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }
}
