/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the PromotionScreen class
 */

#include "screens/promotion_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "screens/screen_controller.h"

extern Buttons buttons;
extern ScreenController screenController;
extern Timer whiteTimer;
extern Timer blackTimer;

PromotionScreen::PromotionScreen(ChessColor color) : BaseScreen(color) {}

PromotionScreen::~PromotionScreen() {}

void PromotionScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);
  this->timer = (this->color == ChessColor::White) ? &whiteTimer : &blackTimer;
  timer->pause();

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label52 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label52, lv_pct(90));
  lv_obj_set_height(this->ui_Label52, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label52, 0);
  lv_obj_set_y(this->ui_Label52, -180);
  lv_obj_set_align(this->ui_Label52, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label52, "Wykonałeś\npromocję");
  lv_obj_set_style_text_color(this->ui_Label52, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label52, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label52, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label52, &lv_font_roboto_36,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label53 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label53, lv_pct(90));
  lv_obj_set_height(this->ui_Label53, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label53, 0);
  lv_obj_set_y(this->ui_Label53, -50);
  lv_obj_set_align(this->ui_Label53, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label53,
                    "Doprowadziłeś pionka do linii promocji. Możesz teraz "
                    "wybrać na jaką figurę chcesz go zamienić. Pamiętaj, aby "
                    "zmienić figurę na szachownicy.");
  lv_obj_set_style_text_font(this->ui_Label53, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label54 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label54, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label54, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label54, 0);
  lv_obj_set_y(this->ui_Label54, 200);
  lv_obj_set_align(this->ui_Label54, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label54, "Kontynuuj");
  lv_obj_set_style_text_font(this->ui_Label54, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void PromotionScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Timer)) {
    screenController.navigateTo(this->color, "piece");
  }
}
