/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the ErrorScreen class
 */

#include "screens/error_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

ErrorScreen::ErrorScreen(ChessColor color) : BaseScreen(color) {}

ErrorScreen::~ErrorScreen() {}

void ErrorScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label60 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label60, lv_pct(90));
  lv_obj_set_height(this->ui_Label60, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label60, 1);
  lv_obj_set_y(this->ui_Label60, -160);
  lv_obj_set_align(this->ui_Label60, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label60, "Wykonałeś niedozwolony ruch");
  lv_obj_set_style_text_color(this->ui_Label60, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label60, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label60, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label60, &lv_font_roboto_34,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label61 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label61, lv_pct(90));
  lv_obj_set_height(this->ui_Label61, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label61, 0);
  lv_obj_set_y(this->ui_Label61, 9);
  lv_obj_set_align(this->ui_Label61, LV_ALIGN_CENTER);
  lv_label_set_text(
      this->ui_Label61,
      "Twój ruch jest nieedozwolony. Cofnij ostatni ruch figury na zaznaczone "
      "pole.\n\n\n\nJeśli popełnisz 3 błędy przegrywasz!");
  lv_obj_set_style_text_font(this->ui_Label61, &lv_font_roboto_22,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label62 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label62, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label62, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label62, 0);
  lv_obj_set_y(this->ui_Label62, 200);
  lv_obj_set_align(this->ui_Label62, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label62, "Kontynuuj");
  lv_obj_set_style_text_font(this->ui_Label62, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ErrorScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Timer)) {
    break;
  }
}
