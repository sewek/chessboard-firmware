/**
 * @file base_screen.h
 * @brief This file contains the abstract class for the screens of the
 * application.
 */

#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include <chess_types.h>
#include <lvgl.h>

/**
 * @brief This class represents the abstract class for the screen.
 */
class BaseScreen {
 public:
  BaseScreen() { this->screen = lv_obj_create(nullptr); }
  ~BaseScreen() = default;

  /**
   * @brief This function is used to draw the screen on startup.
   */
  virtual void init() = 0;

  /**
   * @brief This function is used to update the screen.
   */
  virtual void update() = 0;

  /**
   * @brief This function is used to get the color of the screen.
   * @return The color of the screen
   */
  ChessColor getColor() { return this->color; }

  /**
   * @brief This function is used to get the screen object.
   * @return The screen object
   */
  lv_obj_t *getScreen() { return this->screen; }

  /**
   * @brief This function is used to set the color of the screen.
   */
  void setColor(ChessColor color) { this->color = color; }

 protected:
  ChessColor color = ChessColor::White;
  lv_obj_t *screen = nullptr;
};

#endif  // BASE_SCREEN_H