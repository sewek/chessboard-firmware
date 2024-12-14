/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the LoseScreen class
 */

#include "screens/lose_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

LoseScreen::LoseScreen(ChessColor color) : BaseScreen(color) {}

LoseScreen::~LoseScreen() {}

void LoseScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label45 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label45, lv_pct(100));
  lv_obj_set_height(this->ui_Label45, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label45, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label45, "Przegrałeś");
  lv_obj_set_style_text_color(this->ui_Label45, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label45, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label45, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label45, &lv_font_roboto_46,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label66 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label66, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label66, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label66, 0);
  lv_obj_set_y(this->ui_Label66, 200);
  lv_obj_set_align(this->ui_Label66, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label66, "Kontynuuj");
  lv_obj_set_style_text_font(this->ui_Label66, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void LoseScreen::update() {
  /*
  What is this?
  if (buttons.isPressed(this->color, ButtonType::Timer)) {
    break;
  }
  */
}
