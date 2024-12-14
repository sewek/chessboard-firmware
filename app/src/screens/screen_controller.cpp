#include "screens/screen_controller.h"

#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(screen_controller);

ScreenController::ScreenController() {}

ScreenController::~ScreenController() {}

int ScreenController::init() {
  int ret = 0;
  Display *display = nullptr;

  for (int i = 0; i < this->display_count; i++) {
    display = &this->displays[i];

    ret = display->init();
    if (ret < 0) {
      LOG_ERR("Failed to initialize display\n");
      return ret;
    }

    display_blanking_off(display->dev);

    if (i == 0) {
      ret = this->navigateTo(ChessColor::White, "home");
    } else {
      ret = this->navigateTo(ChessColor::Black, "home");
    }

    if (ret < 0) {
      LOG_ERR("Failed to navigate to home screen\n");
      return ret;
    }
  }

  return 0;
}

int ScreenController::navigateTo(ChessColor color, const char *screen) {
  LOG_INF("Navigating to screen: %s\n", screen);

  int colorIndex = (int)color;
  Display *display = &this->displays[colorIndex];
  if (!display->dev) {
    LOG_ERR("Display not initialized\n");
    return -1;
  }

  // Set display as active display
  lv_disp_set_default(display->display);

  BaseScreen *currentScreen = this->getCurrentScreen(color);
  if (currentScreen != nullptr && currentScreen->getScreen() != nullptr) {
    lv_obj_del(currentScreen->getScreen());
    currentScreen->setScreen(nullptr);
  }

  for (int i = 0; i < this->screen_count; i++) {
    if (this->screens[i] == nullptr) {
      continue;
    }

    LOG_INF("Screen: %s\n", this->screens[i]->getName());
    if (this->screens[i]->getColor() != color) {
      continue;
    }

    if (strcmp(this->screens[i]->getName(), screen) == 0) {
      this->showScreen(this->screens[i]);
      return 0;
    }
  }

  LOG_ERR("Screen not found\n");
  return -1;
}

int ScreenController::run() {
  BaseScreen *currentScreen = this->getCurrentScreen(ChessColor::White);
  if (currentScreen) {
    currentScreen->update();
  }

  currentScreen = this->getCurrentScreen(ChessColor::Black);
  if (currentScreen) {
    currentScreen->update();
  }

  lv_task_handler();

  return 0;
}

int ScreenController::showScreen(BaseScreen *screen) {
  this->setCurrentScreen(screen->getColor(), screen);
  screen->init();
  lv_scr_load(screen->getScreen());
  return 0;
}