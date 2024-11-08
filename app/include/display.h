/**
 * @file display.h
 * @brief Display driver API.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <lvgl.h>
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "lvgl_display.h"

class Display {
 public:
  Display(const struct device *dev, uint32_t width, uint32_t height,
          uint8_t bits_per_pixel)
      : dev(dev),
        width(width),
        height(height),
        bits_per_pixel(bits_per_pixel),
        nbr_pixels(this->buffer_size / (bits_per_pixel / 8)) {}
  ~Display() { lv_disp_remove(this->display); }

  const struct device *dev;
  uint32_t width;
  uint32_t height;
  uint32_t buffer_size = CONFIG_LV_BUFFER_SIZE;
  uint8_t bits_per_pixel;
  uint32_t nbr_pixels;
  lv_disp_drv_t driver;
  lv_disp_draw_buf_t display_buf;
  struct lvgl_disp_data data = {
      .blanking_on = false,
  };
  lv_disp_t *display = nullptr;

  int init();

  void setAsActive() { lv_disp_set_default(this->display); }

 private:
  uint8_t buf0[CONFIG_LV_BUFFER_SIZE];
#ifdef CONFIG_LV_Z_DOUBLE_VDB
  uint8_t buf1[CONFIG_LV_BUFFER_SIZE];
#endif

  int allocateBuffers();
};

#endif  // DISPLAY_H