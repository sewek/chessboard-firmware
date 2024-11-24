/**
 * @file button.h
 * @brief
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <chess_types.h>
#include <inttypes.h>
#include <zephyr/drivers/gpio.h>

enum class ButtonType {
  Up = 0,
  Down,
  Accept,
  Cancel,
  Timer,
};

class Button {
 public:
  struct gpio_dt_spec* spec = nullptr;
  struct gpio_callback* callback = nullptr;
  uint8_t state = 0;
  ChessColor color = ChessColor::White;
  ButtonType type = ButtonType::Up;

  Button() = default;
  Button(struct gpio_dt_spec* spec, struct gpio_callback* callback,
         ChessColor color, ButtonType type);
  ~Button();
};

#endif  // BUTTON_H