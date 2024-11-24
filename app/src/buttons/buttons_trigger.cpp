/**
 * @file buttons_trigger.cpp
 * @brief This file contains the implementation of the functions that are used
 */

#include <button.h>
#include <buttons.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(buttons_trigger);

extern Buttons buttons;

K_THREAD_DEFINE(buttons_callback_thread, 1024, buttonPressedHandler, nullptr,
                nullptr, nullptr, 10, 0, 0);
K_SEM_DEFINE(buttons_sem, 1, 1);
K_MSGQ_DEFINE(buttons_queue, sizeof(Button *), 64, 4);

void buttonPressedCallback(const struct device *dev, struct gpio_callback *cb,
                           uint32_t pins) {
  Button *button = buttons.getButton(cb);
  if (!button) {
    LOG_ERR("Button not found");
    return;
  }

  button->state = 1;

  while (k_msgq_put(&buttons_queue, &button, K_NO_WAIT) != 0) {
    k_yield();
  }

  k_sem_give(&buttons_sem);
}

void buttonPressedHandler(void *arg1, void *arg2, void *arg3) {
  ARG_UNUSED(arg1);
  ARG_UNUSED(arg2);
  ARG_UNUSED(arg3);

  Button *button = nullptr;

  while (1) {
    k_sem_take(&buttons_sem, K_FOREVER);

    while (k_msgq_get(&buttons_queue, &button, K_NO_WAIT) == 0) {
      if (!button) {
        continue;
      }

      LOG_INF("Button pressed: %d", button->type);
    }
  }
}