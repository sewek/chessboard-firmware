/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the WinScreen class
 */

#include "screens/win_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "screens/screen_controller.h"

extern Buttons buttons;
extern ScreenController screenController;

WinScreen::WinScreen(ChessColor color) : BaseScreen(color) {}

WinScreen::~WinScreen() {}

void WinScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label43 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label43, lv_pct(100));
  lv_obj_set_height(this->ui_Label43, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label43, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label43, "Brawo! Wygrałeś");
  lv_obj_set_style_text_color(this->ui_Label43, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label43, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label43, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label43, &lv_font_roboto_46,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label64 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label64, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label64, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label64, 0);
  lv_obj_set_y(this->ui_Label64, 200);
  lv_obj_set_align(this->ui_Label64, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label64, "Kontynuuj");
  lv_obj_set_style_text_font(this->ui_Label64, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void WinScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Timer)) {
    screenController.navigateTo(this->color, "home");
  }
}
