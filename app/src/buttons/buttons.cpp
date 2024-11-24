/**
 * @file buttons.cpp
 * @brief This file contains the implementation of the functions that are used
 * to
 */

#include <buttons.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(buttons);

Buttons::~Buttons() {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    this->buttons[i].~Button();
  }

  struct gpio_dt_spec *button = nullptr;
  struct gpio_callback *callback = nullptr;
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    button = &this->buttons_spec[i];
    callback = &this->buttons_cb[i];
    gpio_remove_callback_dt(button, callback);
  }
}

int Buttons::init() {
  int ret = 0;

  Button *button = nullptr;
  struct gpio_dt_spec *spec = nullptr;
  struct gpio_callback *callback = nullptr;
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    button = &this->buttons[i];
    spec = &this->buttons_spec[i];
    callback = &this->buttons_cb[i];

    if (!gpio_is_ready_dt(spec)) {
      LOG_ERR("Button %d is not ready", i);
      return -ENODEV;
    }

    ret = gpio_pin_configure_dt(spec, GPIO_INPUT);
    if (ret != 0) {
      LOG_ERR("Failed to configure button %d", i);
      return ret;
    }

    ret = gpio_pin_interrupt_configure_dt(spec, GPIO_INT_EDGE_TO_ACTIVE);
    if (ret != 0) {
      LOG_ERR("Failed to configure interrupt for button %d", i);
      return ret;
    }

    gpio_init_callback(callback, buttonPressedCallback, BIT(spec->pin));
    ret = gpio_add_callback_dt(spec, callback);
    if (ret != 0) {
      LOG_ERR("Failed to add callback for button %d", i);
      return ret;
    }

    button->spec = spec;
    button->callback = callback;
    button->state = 0;
    button->type = ButtonType::Up + (i % 5);
    button->color = i < 5 ? ChessColor::White : ChessColor::Black;
  }

  return ret;
}

Button *Buttons::getButton(ChessColor color, ButtonType type) {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    if (this->buttons[i].color == color && this->buttons[i].type == type) {
      return &this->buttons[i];
    }
  }

  return nullptr;
}

Button *Buttons::getButton(uint8_t index) {
  if (index >= BUTTONS_COUNT) {
    return nullptr;
  }

  return &this->buttons[index];
}

Button *Buttons::getButton(struct gpio_dt_spec *spec) {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    if (this->buttons[i].spec == spec) {
      return &this->buttons[i];
    }
  }

  return nullptr;
}

Button *Buttons::getButton(struct gpio_callback *callback) {
  for (int i = 0; i < BUTTONS_COUNT; i++) {
    if (this->buttons[i].callback == callback) {
      return &this->buttons[i];
    }
  }

  return nullptr;
}