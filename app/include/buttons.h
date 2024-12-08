/**
 * @file buttons.h
 * @brief This file contains the declaration of the functions that are used to
 * handle the buttons.
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include "button.h"

#define BUTTONS_COUNT 10

class Buttons {
 public:
  Button buttons[BUTTONS_COUNT];

  Buttons() = default;
  ~Buttons();

  /**
   * @brief This function is used to initialize the buttons.
   */
  int init();

  Button *getButton(ChessColor color, ButtonType type);
  Button *getButton(uint8_t index);
  Button *getButton(struct gpio_dt_spec *spec);
  Button *getButton(struct gpio_callback *callback);

  bool isPressed(ChessColor color, ButtonType type);

 private:
  struct gpio_dt_spec buttons_spec[BUTTONS_COUNT] = {
      GPIO_DT_SPEC_GET(DT_ALIAS(btn0), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn1), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn2), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn3), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn4), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn5), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn6), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn7), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn8), gpios),
      GPIO_DT_SPEC_GET(DT_ALIAS(btn9), gpios),
  };
  struct gpio_callback buttons_cb[BUTTONS_COUNT];
};

void buttonPressedCallback(const struct device *dev, struct gpio_callback *cb,
                           uint32_t pins);

#endif  // BUTTONS_H