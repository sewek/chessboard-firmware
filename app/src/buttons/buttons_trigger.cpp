/**
 * @file buttons_trigger.cpp
 * @brief This file contains the implementation of the functions that are used
 */

#include <button.h>
#include <buttons.h>
#include <chess_types.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(buttons_trigger);

extern Buttons buttons;

void buttonPressedCallback(const struct device *dev, struct gpio_callback *cb,
                           uint32_t pins) {
  Button *button = buttons.getButton(cb);
  if (!button) {
    LOG_ERR("Button not found");
    return;
  }

  button->press();

  const char *color = (button->color == ChessColor::White) ? "White" : "Black";
  switch (button->type) {
    case ButtonType::Up:
      LOG_INF("%s up timer button pressed\n", color);
      break;
    case ButtonType::Down:
      LOG_INF("%s down button pressed\n", color);
      break;
    case ButtonType::Accept:
      LOG_INF("%s accept button pressed\n", color);
      break;
    case ButtonType::Cancel:
      LOG_INF("%s cancel button pressed\n", color);
      break;
    case ButtonType::Timer:
      LOG_INF("%s timer button pressed\n", color);
      break;

    default:
      LOG_ERR("Unknown button type\n");
      break;
  }
}
