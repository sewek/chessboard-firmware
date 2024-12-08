/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the EnPassantScreen class
 */

#include "screens/en_passant_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

EnPassantScreen::EnPassantScreen(ChessColor color) : BaseScreen(color) {}

EnPassantScreen::~EnPassantScreen() {}

void EnPassantScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label49 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label49, lv_pct(90));
  lv_obj_set_height(this->ui_Label49, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label49, 0);
  lv_obj_set_y(this->ui_Label49, -180);
  lv_obj_set_align(this->ui_Label49, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label49, "Wykonałeś en passant");
  lv_obj_set_style_text_color(this->ui_Label49, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label49, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label49, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label49, &lv_font_roboto_34,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Image2 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image2, &ui_img_en_passant_png);
  lv_obj_set_width(this->ui_Image2, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image2, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image2, 0);
  lv_obj_set_y(this->ui_Image2, -50);
  lv_obj_set_align(this->ui_Image2, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image2, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_img_set_zoom(this->ui_Image2, 200);

  this->ui_Label50 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label50, lv_pct(90));
  lv_obj_set_height(this->ui_Label50, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label50, 0);
  lv_obj_set_y(this->ui_Label50, 105);
  lv_obj_set_align(this->ui_Label50, LV_ALIGN_CENTER);
  lv_label_set_text(
      this->ui_Label50,
      "Aby dokończyć bicie zdejmij pionka przeciwnika z podświetlonego pola.");
  lv_obj_set_style_text_font(this->ui_Label50, &lv_font_roboto_22,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label51 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label51, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label51, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label51, 0);
  lv_obj_set_y(this->ui_Label51, 200);
  lv_obj_set_align(this->ui_Label51, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label51, "Kontynuuj");
  lv_obj_set_style_text_font(this->ui_Label51, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void EnPassantScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Timer)) {
    break;
  }
}
