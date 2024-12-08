/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the HomeScreen class
 */

#include "screens/home_screen.h"

#include <zephyr/kernel.h>

#include "buttons.h"

extern Buttons buttons;

HomeScreen::HomeScreen(ChessColor color) : BaseScreen(color) {}

HomeScreen::~HomeScreen() {}

void HomeScreen::init() {
  lv_obj_clear_flag(this->screen, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

  this->ui_Button2 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button2, 315);
  lv_obj_set_height(this->ui_Button2, 50);
  lv_obj_set_x(this->ui_Button2, 0);
  lv_obj_set_y(this->ui_Button2, -110);
  lv_obj_set_align(this->ui_Button2, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button2, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button2, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button2, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button2, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button2, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button2, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button2, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button2, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label1 = lv_label_create(this->ui_Button2);
  lv_obj_set_width(this->ui_Label1, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label1, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label1, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label1, "Start");
  lv_obj_set_style_text_color(this->ui_Label1, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label1, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label1, &lv_font_montserrat_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button1 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button1, 315);
  lv_obj_set_height(this->ui_Button1, 50);
  lv_obj_set_x(this->ui_Button1, 0);
  lv_obj_set_y(this->ui_Button1, -60);
  lv_obj_set_align(this->ui_Button1, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button1, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button1, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button1, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button1, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button1, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button1, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button1, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button1, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label2 = lv_label_create(this->ui_Button1);
  lv_obj_set_width(this->ui_Label2, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label2, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label2, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label2, "Ustawienia");
  lv_obj_set_style_text_color(this->ui_Label2, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label2, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label2, &lv_font_montserrat_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Button3 = lv_btn_create(this->screen);
  lv_obj_set_width(this->ui_Button3, 315);
  lv_obj_set_height(this->ui_Button3, 50);
  lv_obj_set_x(this->ui_Button3, 0);
  lv_obj_set_y(this->ui_Button3, -10);
  lv_obj_set_align(this->ui_Button3, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Button3, LV_OBJ_FLAG_CHECKABLE |
                                        LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
  lv_obj_clear_flag(this->ui_Button3, LV_OBJ_FLAG_SCROLLABLE);         /// Flags
  lv_obj_set_style_radius(this->ui_Button3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(this->ui_Button3, lv_color_hex(0xFFFFFF),
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(this->ui_Button3, 255,
                          LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_color(this->ui_Button3, lv_color_hex(0xFFFFFF),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_opa(this->ui_Button3, 255,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(this->ui_Button3, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Button3, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label3 = lv_label_create(this->ui_Button3);
  lv_obj_set_width(this->ui_Label3, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label3, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_align(this->ui_Label3, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label3, "Informacje");
  lv_obj_set_style_text_color(this->ui_Label3, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label3, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label3, &lv_font_montserrat_26,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Label4 = lv_label_create(this->screen);
  lv_obj_set_width(this->ui_Label4, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Label4, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Label4, 0);
  lv_obj_set_y(this->ui_Label4, -184);
  lv_obj_set_align(this->ui_Label4, LV_ALIGN_CENTER);
  lv_label_set_text(this->ui_Label4, "CHESS");
  lv_obj_set_style_text_color(this->ui_Label4, lv_color_hex(0x000000),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_opa(this->ui_Label4, 255,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(this->ui_Label4, -3,
                                     LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(this->ui_Label4, 0,
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(this->ui_Label4, &lv_font_montserrat_46,
                             LV_PART_MAIN | LV_STATE_DEFAULT);

  this->ui_Image6 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image6, &ui_img_chess_plt45_svg_png);
  lv_obj_set_width(this->ui_Image6, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image6, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image6, 87);
  lv_obj_set_y(this->ui_Image6, -188);
  lv_obj_set_align(this->ui_Image6, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image6, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image6, LV_OBJ_FLAG_SCROLLABLE);  /// Flags

  this->ui_Image1 = lv_img_create(this->screen);
  lv_img_set_src(this->ui_Image1, &ui_img_chess_plt45_svg_png);
  lv_obj_set_width(this->ui_Image1, LV_SIZE_CONTENT);   /// 1
  lv_obj_set_height(this->ui_Image1, LV_SIZE_CONTENT);  /// 1
  lv_obj_set_x(this->ui_Image1, -84);
  lv_obj_set_y(this->ui_Image1, -188);
  lv_obj_set_align(this->ui_Image1, LV_ALIGN_CENTER);
  lv_obj_add_flag(this->ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);   /// Flags
  lv_obj_clear_flag(this->ui_Image1, LV_OBJ_FLAG_SCROLLABLE);  /// Flags
}

void HomeScreen::update() {}
