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
  this->screen = lv_obj_create(nullptr);

  lv_obj_t *label = lv_label_create(this->screen);
  lv_label_set_text(label, "Home Screen");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}

void HomeScreen::update() {}
