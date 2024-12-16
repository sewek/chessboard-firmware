/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the Draw2Screen class
 */

#include "screens/draw2_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "screens/screen_controller.h"

extern Buttons buttons;
extern ScreenController screenController;

Draw2Screen::Draw2Screen(ChessColor color) : BaseScreen(color) {}

Draw2Screen::~Draw2Screen() {}

void Draw2Screen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label44 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label44, lv_pct(100));
  lv_obj_set_height(this->ui_Label44, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label44, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label44, "Remis");
  lv_obj_set_style_text_color(this->ui_Label44, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label44, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label44, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label44, &lv_font_roboto_46,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label65 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label65, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label65, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label65, 0);
  lv_obj_set_y(this->ui_Label65, 200);
  lv_obj_set_align(this->ui_Label65, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label65, "Kontynuuj");
  lv_obj_set_style_text_font(this->ui_Label65, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void Draw2Screen::update() {
  if (buttons.isPressed(this->color, ButtonType::Timer)) {
    screenController.navigateTo(this->color, "home");
  }
}
