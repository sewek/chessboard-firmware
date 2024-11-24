/**
 * @file home_screen.h
 * @brief This file contains the declaration of the HomeScreen class
 */

#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <base_screen.h>

/**
 * @brief This class represents the home screen of the application
 */
class HomeScreen : public BaseScreen {
 public:
  HomeScreen();
  ~HomeScreen();

  void init() override;
  void update() override;
};

#endif  // HOME_SCREEN_H