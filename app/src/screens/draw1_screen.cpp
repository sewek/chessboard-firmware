/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the Draw1Screen class
 */

#include "screens/draw1_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"
#include "chess.h"
#include "screens/screen_controller.h"
#include "timer.h"

extern Buttons buttons;
extern ScreenController screenController;
extern Timer whiteTimer;
extern Timer blackTimer;
extern Chess chess;

Draw1Screen::Draw1Screen(ChessColor color) : BaseScreen(color) {}

Draw1Screen::~Draw1Screen() {}

void Draw1Screen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label16 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label16, lv_pct(100));
  lv_obj_set_height(this->ui_Label16, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label16, 0);
  lv_obj_set_y(this->ui_Label16, -145);
  lv_obj_set_align(this->ui_Label16, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label16, "Przeciwnik proponuje remis");
  lv_obj_set_style_text_color(this->ui_Label16, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label16, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label16, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label16, &lv_font_roboto_36,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button10 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button10, 315);
  lv_obj_set_height(this->ui_Button10, 50);
  lv_obj_set_x(this->ui_Button10, 0);
  lv_obj_set_y(this->ui_Button10, -50);
  lv_obj_set_align(this->ui_Button10, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button10,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button10, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button10, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button10, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button10, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(this->ui_Button10, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button10, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button10, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button10, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button10, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label17 = lv_label_create(this->ui_Button10);
  lv_obj_set_width(this->ui_Label17, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label17, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label17, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label17, "Przyjmij");
  lv_obj_set_style_text_color(this->ui_Label17, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label17, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label17, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button11 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button11, 315);
  lv_obj_set_height(this->ui_Button11, 50);
  lv_obj_set_align(this->ui_Button11, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button11,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button11, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button11, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button11, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button11, lv_color_hex(0xD9EAFD),
                            LV_PART_MAIN | LV_STATE_FOCUSED);
  lv_obj_set_style_bg_opa(this->ui_Button11, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button11, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button11, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button11, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button11, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label18 = lv_label_create(this->ui_Button11);
  lv_obj_set_width(this->ui_Label18, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label18, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label18, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label18, "Odrzuć");
  lv_obj_set_style_text_color(this->ui_Label18, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label18, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label18, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);
}

void Draw1Screen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 2;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 1) % 2;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_add_state(this->ui_Button10, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button11, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_clear_state(this->ui_Button10, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button11, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    switch (this->buttonIndex) {
      case 0:
        chess.finishGame(ChessGameResult::Draw);
        /* whiteTimer.stop();
        blackTimer.stop();
        screenController.navigateTo(this->color == ChessColor::White
                                        ? ChessColor::Black
                                        : ChessColor::White,
                                    "draw2");
        screenController.navigateTo(this->color, "draw2"); */
        break;
      case 1:
        if (this->color == ChessColor::White) {
          blackTimer.resume();
        } else {
          whiteTimer.resume();
        }
        screenController.navigateTo(this->color == ChessColor::White
                                        ? ChessColor::Black
                                        : ChessColor::White,
                                    "start");
        screenController.navigateTo(this->color, "start");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }
}
