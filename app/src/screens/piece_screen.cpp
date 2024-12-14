/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the PieceScreen class
 */

#include "screens/piece_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

PieceScreen::PieceScreen(ChessColor color) : BaseScreen(color) {}

PieceScreen::~PieceScreen() {}

void PieceScreen::init() {
  if (this->screen == nullptr) this->screen = lv_obj_create(nullptr);

  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_bg_color(this->screen, lv_color_hex(0xFFFFFF),
                            LV_STATE_DEFAULT);

  this->ui_Label55 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label55, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label55, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label55, 0);
  lv_obj_set_y(this->ui_Label55, -145);
  lv_obj_set_align(this->ui_Label55, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label55, "Wybierz figurę");
  lv_obj_set_style_text_color(this->ui_Label55, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label55, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(this->ui_Label55, LV_TEXT_ALIGN_CENTER,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label55, &lv_font_roboto_36,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button29 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button29, 315);
  lv_obj_set_height(this->ui_Button29, 50);
  lv_obj_set_x(this->ui_Button29, 0);
  lv_obj_set_y(this->ui_Button29, -50);
  lv_obj_set_align(this->ui_Button29, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button29,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button29, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button29, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button29, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button29, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button29, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button29, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button29, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button29, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label56 = lv_label_create(this->ui_Button29);
  lv_obj_set_width(this->ui_Label56, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label56, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label56, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label56, "Hetman");
  lv_obj_set_style_text_color(this->ui_Label56, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label56, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label56, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button30 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button30, 315);
  lv_obj_set_height(this->ui_Button30, 50);
  lv_obj_set_align(this->ui_Button30, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button30,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button30, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button30, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button30, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button30, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button30, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button30, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button30, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button30, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label57 = lv_label_create(this->ui_Button30);
  lv_obj_set_width(this->ui_Label57, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label57, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label57, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label57, "Wieża");
  lv_obj_set_style_text_color(this->ui_Label57, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label57, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label57, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button31 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button31, 315);
  lv_obj_set_height(this->ui_Button31, 50);
  lv_obj_set_x(this->ui_Button31, 0);
  lv_obj_set_y(this->ui_Button31, 50);
  lv_obj_set_align(this->ui_Button31, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button31,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button31, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button31, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button31, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button31, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button31, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button31, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button31, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button31, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label58 = lv_label_create(this->ui_Button31);
  lv_obj_set_width(this->ui_Label58, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label58, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label58, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label58, "Goniec");
  lv_obj_set_style_text_color(this->ui_Label58, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label58, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label58, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button32 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button32, 315);
  lv_obj_set_height(this->ui_Button32, 50);
  lv_obj_set_x(this->ui_Button32, 0);
  lv_obj_set_y(this->ui_Button32, 100);
  lv_obj_set_align(this->ui_Button32, LV_ALIGN_CENTER);
  lv_obj_add_flag(
      this->ui_Button32,
      LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);      /// Flags
  lv_obj_clear_flag(this->ui_Button32, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_obj_set_style_radius(this->ui_Button32, 0,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button32, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button32, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button32, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button32, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button32, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button32, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label59 = lv_label_create(this->ui_Button32);
  lv_obj_set_width(this->ui_Label59, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label59, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label59, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label59, "Skoczek");
  lv_obj_set_style_text_color(this->ui_Label59, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label59, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label59, &lv_font_roboto_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Image8 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image8, &ui_img_chess_blt45_svg_png);
  lv_obj_set_width(this->ui_Image8, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image8, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image8, -66);
  lv_obj_set_y(this->ui_Image8, 50);
  lv_obj_set_align(this->ui_Image8, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image8, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image8, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_img_set_zoom(this->ui_Image8, 170);

  this->ui_Image3 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image3, &ui_img_chess_nlt45_svg_png);
  lv_obj_set_width(this->ui_Image3, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image3, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image3, -72);
  lv_obj_set_y(this->ui_Image3, 100);
  lv_obj_set_align(this->ui_Image3, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image3, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_img_set_zoom(this->ui_Image3, 170);

  this->ui_Image4 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image4, &ui_img_chess_qlt45_svg_png);
  lv_obj_set_width(this->ui_Image4, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image4, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image4, -75);
  lv_obj_set_y(this->ui_Image4, -50);
  lv_obj_set_align(this->ui_Image4, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image4, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_img_set_zoom(this->ui_Image4, 170);

  this->ui_Image5 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image5, &ui_img_chess_rlt45_svg_png);
  lv_obj_set_width(this->ui_Image5, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image5, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image5, -62);
  lv_obj_set_y(this->ui_Image5, 0);
  lv_obj_set_align(this->ui_Image5, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image5, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image5, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
  lv_img_set_zoom(this->ui_Image5, 170);
}

void PieceScreen::update() {
  if (buttons.isPressed(this->color, ButtonType::Up)) {
    this->buttonIndex = (this->buttonIndex + 1) % 4;
  }

  if (buttons.isPressed(this->color, ButtonType::Down)) {
    this->buttonIndex = (this->buttonIndex + 2) % 4;
  }

  switch (this->buttonIndex) {
    case 0:
      lv_obj_clear_state(this->ui_Button29, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button30, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button31, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button32, LV_STATE_FOCUSED);
      break;
    case 1:
      lv_obj_clear_state(this->ui_Button29, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button30, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button31, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button32, LV_STATE_FOCUSED);
      break;
    case 2:
      lv_obj_clear_state(this->ui_Button29, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button30, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button31, LV_STATE_FOCUSED);
      lv_obj_add_state(this->ui_Button32, LV_STATE_FOCUSED);
      break;
    case 3:
      lv_obj_add_state(this->ui_Button29, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button30, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button31, LV_STATE_FOCUSED);
      lv_obj_clear_state(this->ui_Button32, LV_STATE_FOCUSED);
      break;
    default:
      break;
  }

  if (buttons.isPressed(this->color, ButtonType::Accept)) {
    switch (this->buttonIndex) {
      case 0:
        // LOG_INF("Queen button pressed\n");
        break;
      case 1:
        // LOG_INF("Rock button pressed\n");
        break;
      case 2:
        // LOG_INF("Bishop button pressed\n");
        break;
      case 3:
        // LOG_INF("Knight button pressed\n");
        break;
      default:
        // LOG_ERR("Unknown button index\n");
        break;
    }
  }
}
