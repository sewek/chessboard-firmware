/**
 * @file screen_controller.h
 * @brief This file contains the declaration of the ScreenController class
 */

#ifndef SCREEN_CONTROLLER_H
#define SCREEN_CONTROLLER_H

#include <chess_types.h>

#include "base_screen.h"
#include "castling_screen.h"
#include "display.h"
#include "draw1_screen.h"
#include "draw2_screen.h"
#include "draw_screen.h"
#include "en_passant_screen.h"
#include "error_screen.h"
#include "giveup_screen.h"
#include "home_screen.h"
#include "lose_screen.h"
#include "mode_screen.h"
#include "open_screen.h"
#include "piece_screen.h"
#include "promotion_screen.h"
#include "settings_screen.h"
#include "start_screen.h"
#include "time_screen.h"
#include "win_screen.h"

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

  BaseScreen *screens[34] = {
      &whiteHomeScreen,      &blackHomeScreen,      &whiteSettingsScreen,
      &blackSettingsScreen,  &whiteStartScreen,     &blackStartScreen,
      &whitePieceScreen,     &blackPieceScreen,     &whiteModeScreen,
      &blackModeScreen,      &whiteTimeScreen,      &blackTimeScreen,
      &whiteOpenScreen,      &blackOpenScreen,      &whiteDraw2Screen,
      &blackDraw2Screen,     &whiteWinScreen,       &blackWinScreen,
      &whiteLoseScreen,      &blackLoseScreen,      &whiteCastlingScreen,
      &blackCastlingScreen,  &whitePromotionScreen, &blackPromotionScreen,
      &whiteEnPassantScreen, &blackEnPassantScreen, &whiteErrorScreen,
      &blackErrorScreen,     &whiteDraw1Screen,     &blackDraw1Screen,
      &whiteGiveUpScreen,    &blackGiveUpScreen,    &whiteDrawScreen,
      &blackDrawScreen,
  };
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
