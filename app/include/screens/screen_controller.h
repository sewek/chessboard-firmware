/**
 * @file screen_controller.h
 * @brief This file contains the declaration of the ScreenController class
 */

#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include <chess_types.h>

#include "base_screen.h"
#include "display.h"
#include "home_screen.h"

/**
 * @brief This class represents the screen controller of the application
 */
class ScreenController {
 public:
  ScreenController();
  ~ScreenController();

  /**
   * @brief Initialize the screen controller
   * @return 0 on success, negative error code on failure
   */
  int init();

  /**
   * @brief Get the current screen
   * @return The current screen
   */
  BaseScreen *getCurrentScreen(ChessColor color) {
    return this->currentScreen[(int)color];
  }

  /**
   * @brief Set the current screen
   * @param screen The screen to set
   */
  void setCurrentScreen(ChessColor color, BaseScreen *screen) {
    this->currentScreen[(int)color] = screen;
  }

  /**
   * @brief Navigate to the specified screen
   * @param color The color of the screen
   * @param screen The screen to navigate to
   * @return 0 on success, negative error code on failure
   */
  int navigateTo(ChessColor color, const char *screen);

  /**
   * @brief Run the screen controller task handler
   * @return 0 on success, negative error code on failure
   */
  int run();

 private:
  BaseScreen *currentScreen[2] = {nullptr, nullptr};

  BaseScreen *screens[2] = {&whiteHomeScreen, &blackHomeScreen};
  uint8_t screen_count = sizeof(screens) / sizeof(screens[0]);

  Display displays[2] = {
      Display(DEVICE_DT_GET(DT_NODELABEL(display_white)),
              DT_PROP(DT_NODELABEL(display_white), width),
              DT_PROP(DT_NODELABEL(display_white), height), 24),
      Display(DEVICE_DT_GET(DT_NODELABEL(display_black)),
              DT_PROP(DT_NODELABEL(display_black), width),
              DT_PROP(DT_NODELABEL(display_black), height), 24),
  };
  uint8_t display_count = 2;

  int showScreen(BaseScreen *screen);
};

#endif  // SCREEN_CONTROLLER_H
