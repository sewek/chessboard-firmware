/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the CastlingScreen class
 */

#include "screens/castling_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "screens/screen_controller.h"

extern ScreenController screenController;
extern Timer whiteTimer;
extern Timer blackTimer;
extern Buttons buttons;

CastlingScreen::CastlingScreen(ChessColor color) : BaseScreen(color) {}

CastlingScreen::~CastlingScreen() {}

void CastlingScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);
  this->timer = (this->color == ChessColor::White) ? &whiteTimer : &blackTimer;
  this->timer->pause();

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label48 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label48, lv_pct(100));
  lv_obj_set_height(this->ui_Label48, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label48, 0);
  lv_obj_set_y(this->ui_Label48, -180);
  lv_obj_set_align(this->ui_Label48, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label48, "Wykonałeś roszadę");
  lv_obj_set_style_text_color(this->ui_Label48, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label48, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label48, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label48, &lv_font_roboto_36,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  /* this->ui_Image7 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image7, &ui_img_roszada_png);
  lv_obj_set_width(this->ui_Image7, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image7, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image7, 0);
  lv_obj_set_y(this->ui_Image7, -50);
  lv_obj_set_align(this->ui_Image7, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image7, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image7, LV_OBJ_FLAG_SCROLLABLE);  /// Flags */

  this->ui_Label46 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label46, lv_pct(90));
  lv_obj_set_height(this->ui_Label46, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label46, 0);
  lv_obj_set_y(this->ui_Label46, 105);
  lv_obj_set_align(this->ui_Label46, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label46,
                    "Aby dokończyć roszadę ustaw wieżę na podświetlonym polu, "
                    "które minął król.");
  lv_obj_set_style_text_font(this->ui_Label46, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label47 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label47, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label47, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label47, 0);
  lv_obj_set_y(this->ui_Label47, 200);
  lv_obj_set_align(this->ui_Label47, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label47, "Kontynuuj");
  lv_obj_set_style_text_font(this->ui_Label47, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void CastlingScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Timer)) {
    this->timer->resume();
    screenController.navigateTo(this->color, "start");
  }
}
