/**
 * @file display.cpp
 * @brief Display driver implementation.
 */

#include "display.h"

#include <lvgl_mem.h>

LOG_MODULE_REGISTER(display, LOG_LEVEL_DBG);

#if CONFIG_LV_Z_LOG_LEVEL != 0
static void lvgl_log(const char *buf) {
  switch (buf[1]) {
    case 'E':
      LOG_ERR("%s", buf + strlen("[Error] "));
      break;
    case 'W':
      LOG_WRN("%s", buf + strlen("[Warn] "));
      break;
    case 'I':
      LOG_INF("%s", buf + strlen("[Info] "));
      break;
    case 'T':
      LOG_DBG("%s", buf + strlen("[Trace] "));
      break;
    case 'U':
      LOG_INF("%s", buf + strlen("[User] "));
      break;
  }
}
#endif

int Display::init() {
  int err = 0;

  if (!device_is_ready(this->dev)) {
    LOG_ERR("Display device is not ready\n");
    return -ENODEV;
  }

#ifdef CONFIG_LV_Z_MEM_POOL_SYS_HEAP
  lvgl_heap_init();
#endif

#if CONFIG_LV_Z_LOG_LEVEL != 0
  lv_log_register_print_cb(lvgl_log);
#endif

  lv_init();

  this->data.display_dev = this->dev;
  display_get_capabilities(this->dev, &this->data.cap);

  lv_disp_drv_init(&this->driver);
  this->driver.user_data = (void *)&this->data;

#ifdef CONFIG_LV_Z_FULL_REFRESH
  this->driver.full_refresh = 1;
#endif

  err = this->allocateBuffers();
  if (err != 0) {
    return err;
  }

  if (set_lvgl_rendering_cb(&this->driver) != 0) {
    LOG_ERR("Display not supported.");
    return -ENOTSUP;
  }

  this->display = lv_disp_drv_register(&this->driver);
  if (this->display == nullptr) {
    LOG_ERR("Failed to register display device.");
    return -EPERM;
  }

  return err;
}

int Display::allocateBuffers() {
  struct lvgl_disp_data *data = (struct lvgl_disp_data *)this->driver.user_data;
  int err = 0;

  if (data->cap.x_resolution <= this->width) {
    this->driver.hor_res = data->cap.x_resolution;
  } else {
    LOG_ERR("Horizontal resolution is larger than maximum");
    err = -ENOTSUP;
  }

  if (data->cap.y_resolution <= this->height) {
    this->driver.ver_res = data->cap.y_resolution;
  } else {
    LOG_ERR("Vertical resolution is larger than maximum");
    err = -ENOTSUP;
  }

  if (this->nbr_pixels == 0) {
    LOG_ERR("Buffer size is 0");
    return -EINVAL;
  }

  this->driver.draw_buf = &this->display_buf;
#ifdef CONFIG_LV_Z_DOUBLE_VDB
  lv_disp_draw_buf_init(this->driver.draw_buf, &this->buf0, &this->buf1,
                        this->nbr_pixels);
#else
  lv_disp_draw_buf_init(this->driver.draw_buf, &this->buf0, NULL,
                        this->nbr_pixels);
#endif /* CONFIG_LV_Z_DOUBLE_VDB  */

  return err;
}