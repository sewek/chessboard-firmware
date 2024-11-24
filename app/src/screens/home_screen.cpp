/**
 * @file home_screen.cpp
 * @brief This file contains the implementation of the HomeScreen class
 */

#include <home_screen.h>

HomeScreen::HomeScreen() : BaseScreen() {}

HomeScreen::~HomeScreen() : ~BaseScreen() {}

void HomeScreen::init() {
  lv_obj_t *label = lv_label_create(this->screen, nullptr);
  lv_label_set_text(label, "Home Screen");
  lv_obj_align(label, nullptr, LV_ALIGN_CENTER, 0, 0);
}

void HomeScreen::update() {}
