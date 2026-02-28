/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the SettingsScreen class
 */

#include "screens/settings_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "chess.h"
#include "screens/screen_controller.h"
#include "timer.h"

#define SCREEN_WIDTH 320

extern Chess chess;
extern Buttons buttons;
extern ScreenController screenController;
extern Timer whiteTimer;
extern Timer blackTimer;

SettingsScreen::SettingsScreen(ChessColor color) : BaseScreen(color) {}

SettingsScreen::~SettingsScreen() {}

void SettingsScreen::init() {
  this->buttonIndex = 0;
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);
  Timer *timer = (this->color == ChessColor::White) ? &whiteTimer : &blackTimer;

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Button12 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button12, 315);
  lv_obj_set_height(this->ui_Button12, 50);
  lv_obj_set_x(this->ui_Button12, 0);
  lv_obj_set_y(this->ui_Button12, -110);
  lv_obj_set_align(this->ui_Button12, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button12,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button12, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button12, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button12, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button12, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(this->ui_Button12, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button12, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button12, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button12, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button12, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label19 = lv_label_create(this->ui_Button12);
  lv_obj_set_width(this->ui_Label19, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label19, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label19, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label19, "Czas gry");
  lv_obj_set_style_text_color(this->ui_Label19, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label19, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label19, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label22 = lv_label_create(this->ui_Button12);
  lv_obj_set_width(this->ui_Label22, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label22, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label22, LV_ALIGN_RIGHT_MID);
  char time[10] = {0};
  timer->toString(time);
  lv_label_set_text(this->ui_Label22, time);
  lv_obj_set_style_text_color(this->ui_Label22, lv_color_hex(0x645D5D),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label22, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label22, &lv_font_roboto_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button13 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button13, 315);
  lv_obj_set_height(this->ui_Button13, 50);
  lv_obj_set_x(this->ui_Button13, 0);
  lv_obj_set_y(this->ui_Button13, -60);
  lv_obj_set_align(this->ui_Button13, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button13,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button13, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button13, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button13, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button13, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(this->ui_Button13, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button13, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button13, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button13, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button13, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label20 = lv_label_create(this->ui_Button13);
  lv_obj_set_width(this->ui_Label20, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label20, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label20, LV_ALIGN_LEFT_MID);
  lv_label_set_text(this->ui_Label20, "Tryb gry");
  lv_obj_set_style_text_color(this->ui_Label20, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label20, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label20, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label23 = lv_label_create(this->ui_Button13);
  lv_obj_set_width(this->ui_Label23, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label23, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label23, LV_ALIGN_RIGHT_MID);
  if (chess.getHighlightAvailablePositions(this->color)) {
    lv_label_set_text(this->ui_Label23, "Podświetlenie");
  } else {
    lv_label_set_text(this->ui_Label23, "Brak podświetlenia");
  }
  lv_obj_set_style_text_color(this->ui_Label23, lv_color_hex(0x645D5D),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label23, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label23, &lv_font_roboto_16,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  if (this->color == ChessColor::White) {
    this->ui_Button14 = lv_btn_create(this->screen);
    lv_obj_set_width(this->ui_Button14, 315);
    lv_obj_set_height(this->ui_Button14, 50);
    lv_obj_set_x(this->ui_Button14, 0);
    lv_obj_set_y(this->ui_Button14, -10);
    lv_obj_set_align(this->ui_Button14, LV_ALIGN_CENTER);
    lv_obj_add_flag(
        this->ui_Button14,
        LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
    lv_obj_clear_flag(this->ui_Button14, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
    lv_obj_set_style_radius(this->ui_Button14, 0,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(this->ui_Button14, lv_color_hex(0xFFFFFF),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(this->ui_Button14, lv_color_hex(0xD9EAFD),
                              LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(this->ui_Button14, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(this->ui_Button14, lv_color_hex(0xFFFFFF),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(this->ui_Button14, 255,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(this->ui_Button14, lv_color_hex(0x000000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(this->ui_Button14, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);

    this->ui_Label21 = lv_label_create(this->ui_Button14);
    lv_obj_set_width(this->ui_Label21, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(this->ui_Label21, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_align(this->ui_Label21, LV_ALIGN_LEFT_MID);
    lv_label_set_text(this->ui_Label21, "Otwarcie");
    lv_obj_set_style_text_color(this->ui_Label21, lv_color_hex(0x000000),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(this->ui_Label21, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(this->ui_Label21, &lv_font_roboto_26,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    this->ui_Label25 = lv_label_create(this->ui_Button14);
    int openingIndex = chess.getOpeningIndex();
    ChessOpening *opening = chess.getOpening(openingIndex);

    if (opening == nullptr || openingIndex < 0) {
      lv_obj_set_width(this->ui_Label25, LV_SIZE_CONTENT);   /// 1
      lv_obj_set_height(this->ui_Label25, LV_SIZE_CONTENT);  /// 1
      lv_label_set_text(this->ui_Label25, "Brak");
    } else {
      lv_obj_set_width(this->ui_Label25, 180);  /// 1
      lv_obj_set_height(this->ui_Label25, 18);  /// 1
      lv_label_set_text(this->ui_Label25, opening->name);
      lv_label_set_long_mode(this->ui_Label25, LV_LABEL_LONG_SCROLL_CIRCULAR);
    }

    lv_obj_set_align(this->ui_Label25, LV_ALIGN_RIGHT_MID);
    lv_obj_set_style_text_color(this->ui_Label25, lv_color_hex(0x645D5D),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(this->ui_Label25, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(this->ui_Label25, &lv_font_roboto_16,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
  }

  this->ui_Label24 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label24, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label24, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label24, 0);
  lv_obj_set_y(this->ui_Label24, -180);
  lv_obj_set_align(this->ui_Label24, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label24, "Ustawienia");
  lv_obj_set_style_text_color(this->ui_Label24, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label24, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label24, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label24, &lv_font_roboto_36,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void SettingsScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 2) % 3;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 1) % 3;
  }

  if (this->ui_Button14 == nullptr && this->buttonIndex == 2) {
    this->buttonIndex = 0;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_add_state(this->ui_Button12, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button13, LV_STATE_FOCUSED);
      if (this->ui_Button14 != nullptr)
        lv_obj_clear_state(this->ui_Button14, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_clear_state(this->ui_Button12, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button13, LV_STATE_FOCUSED);
      if (this->ui_Button14 != nullptr)
        lv_obj_clear_state(this->ui_Button14, LV_STATE_FOCUSED);
      break;
    case 2:
      lv_obj_clear_state(this->ui_Button12, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button13, LV_STATE_FOCUSED);
      if (this->ui_Button14 != nullptr)
        lv_obj_add_state(this->ui_Button14, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    bool curr_highlight = chess.getHighlightAvailablePositions(this->color);

    switch (this->buttonIndex) {
      case 0:
        screenController.navigateTo(this->color, "time");
        break;
      case 1:
        chess.setHighlightAvailablePositions(this->color, !curr_highlight);
        if (!curr_highlight) {
          lv_label_set_text(this->ui_Label23, "Podświetlenie");
        } else {
          lv_label_set_text(this->ui_Label23, "Brak podświetlenia");
        }
        break;
      case 2:
        screenController.navigateTo(this->color, "open");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }

  if (buttons.isPressed(this->color, ButtonType::Cancel)) {
    screenController.navigateTo(this->color, "home");
  }
}
