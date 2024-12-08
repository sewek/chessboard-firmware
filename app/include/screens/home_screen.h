/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include "base_screen.h"

/**
 * @brief This class represents the home screen of the application
 */
class HomeScreen : public BaseScreen {
 public:
  explicit HomeScreen(ChessColor color);
  ~HomeScreen();

  void init() override;
  void update() override;

  const char *getName() override { return "home"; }
};

inline HomeScreen whiteHomeScreen(ChessColor::White);
inline HomeScreen blackHomeScreen(ChessColor::Black);

#endif  // HOME_SCREEN_H