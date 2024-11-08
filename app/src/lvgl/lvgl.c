/*
 * Copyright (c) 2018-2019 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <lvgl.h>
#include <zephyr/init.h>
#include <zephyr/kernel.h>

#include "lvgl_common_input.h"
#include "lvgl_display.h"
#ifdef CONFIG_LV_Z_USE_FILESYSTEM
#include "lvgl_fs.h"
#endif
#ifdef CONFIG_LV_Z_MEM_POOL_SYS_HEAP
#include "lvgl_mem.h"
#endif
#include LV_MEM_CUSTOM_INCLUDE

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(lvgl, CONFIG_LV_Z_LOG_LEVEL);

#define DISPLAYS_NODE DT_NODELABEL(display_white), DT_NODELABEL(display_black)
#define DISPLAYS_LEN 2

// Types
struct display_data {
  const struct device *dev;
  uint8_t *buf0;
#ifdef CONFIG_LV_Z_DOUBLE_VDB
  uint8_t *buf1;
#endif
  uint32_t width;
  uint32_t height;
  uint32_t buffer_size;
  uint32_t nbr_pixels;
  lv_disp_drv_t driver;
  lv_disp_draw_buf_t display_buf;
  struct lvgl_disp_data data;
};

// Static buffer
#ifdef CONFIG_LV_Z_BUFFER_ALLOC_STATIC
#define BUFF_SIZE(width, height) \
  (CONFIG_LV_Z_BITS_PER_PIXEL *  \
   ((CONFIG_LV_Z_VDB_SIZE * width * height) / 100) / 8)
#define BUFF_ATTRS                              \
  __aligned(CONFIG_LV_Z_VDB_ALIGN) COND_CODE_1( \
      CONFIG_LV_Z_VBD_CUSTOM_SECTION, (Z_GENERIC_SECTION(.lvgl_buf)), ())
#ifdef CONFIG_LV_Z_VDB_ALIGN
#define STATIC_BUFF(node_id)               \
  static uint8_t buf0_##node_id[BUFF_SIZE( \
      DT_PROP(node_id, width), DT_PROP(node_id, height))] BUFF_ATTRS;
#else /* CONFIG_LV_Z_VDB_ALIGN */
#define STATIC_BUFF(node_id)                                          \
  static uint8_t buf0_##node_id[BUFF_SIZE(                            \
      DT_PROP(node_id, width), DT_PROP(node_id, height))] BUFF_ATTRS; \
  static uint8_t buf1_##node_id[BUFF_SIZE(                            \
      DT_PROP(node_id, width), DT_PROP(node_id, height))] BUFF_ATTRS;
#endif /* CONFIG_LV_Z_VDB_ALIGN */
// Display data structure for each display
#define INIT_DISPLAY_STRUCT(node_id)                                       \
  {.dev = DEVICE_DT_GET(node_id),                                          \
   .buf0 = buf0_##node_id,                                                 \
   .width = DT_PROP(node_id, width),                                       \
   .height = DT_PROP(node_id, height),                                     \
   .buffer_size =                                                          \
       BUFF_SIZE(DT_PROP(node_id, width), DT_PROP(node_id, height)),       \
   .nbr_pixels =                                                           \
       (BUFF_SIZE(DT_PROP(node_id, width), DT_PROP(node_id, height)) * 8 / \
        CONFIG_LV_Z_BITS_PER_PIXEL),                                       \
   .data = {.blanking_on = false},                                         \
   COND_CODE_1(CONFIG_LV_Z_DOUBLE_VDB, (.buf1 = buf1_##node_id, ), ())}
#else /* CONFIG_LV_Z_BUFFER_ALLOC_STATIC */
#define STATIC_BUFF(node_id)
#define INIT_DISPLAY_STRUCT(node_id)   \
  {.dev = DEVICE_DT_GET(node_id),      \
   .buf0 = NULL,                       \
   .width = DT_PROP(node_id, width),   \
   .height = DT_PROP(node_id, height), \
   .buffer_size = 0,                   \
   .nbr_pixels = 0,                    \
   .data = {.blanking_on = false},     \
   COND_CODE_1(CONFIG_LV_Z_DOUBLE_VDB, (.buf1 = buf1_##node_id, ), ())}
#endif /* CONFIG_LV_Z_BUFFER_ALLOC_STATIC */

FOR_EACH(STATIC_BUFF, (), DISPLAYS_NODE);
static struct display_data displays[] = {
    FOR_EACH(INIT_DISPLAY_STRUCT, (, ), DISPLAYS_NODE)};
static const uint8_t displays_num = DISPLAYS_LEN;

#if CONFIG_LV_Z_LOG_LEVEL != 0
/*
 * In LVGLv8 the signature of the logging callback has changes and it no longer
 * takes the log level as an integer argument. Instead, the log level is now
 * already part of the buffer passed to the logging callback. It's not optimal
 * but we need to live with it and parse the buffer manually to determine the
 * level and then truncate the string we actually pass to the logging framework.
 */
static void lvgl_log(const char *buf) {
  /*
   * This is ugly and should be done in a loop or something but as it
   * turned out, Z_LOG()'s first argument (that specifies the log level)
   * cannot be an l-value...
   *
   * We also assume lvgl is sane and always supplies the level string.
   */
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

#ifdef CONFIG_LV_Z_BUFFER_ALLOC_STATIC

static int lvgl_allocate_rendering_buffers(struct display_data *display) {
  lv_disp_drv_t *disp_driver = &display->driver;
  struct lvgl_disp_data *data = (struct lvgl_disp_data *)disp_driver->user_data;
  int err = 0;

  if (data->cap.x_resolution <= display->width) {
    disp_driver->hor_res = data->cap.x_resolution;
  } else {
    LOG_ERR("Horizontal resolution is larger than maximum");
    err = -ENOTSUP;
  }

  if (data->cap.y_resolution <= display->height) {
    disp_driver->ver_res = data->cap.y_resolution;
  } else {
    LOG_ERR("Vertical resolution is larger than maximum");
    err = -ENOTSUP;
  }

  disp_driver->draw_buf = &display->display_buf;
#ifdef CONFIG_LV_Z_DOUBLE_VDB
  lv_disp_draw_buf_init(disp_driver->draw_buf, &display->buf0, &display->buf1,
                        display->nbr_pixels);
#else
  lv_disp_draw_buf_init(disp_driver->draw_buf, &display->buf0, NULL,
                        display->nbr_pixels);
#endif /* CONFIG_LV_Z_DOUBLE_VDB  */

  return err;
}

#else

static int lvgl_allocate_rendering_buffers(struct display_data *display) {
  void *buf0 = NULL;
  void *buf1 = NULL;
  uint16_t buf_nbr_pixels;
  uint32_t buf_size;
  lv_disp_drv_t *disp_driver = &display->driver;
  struct lvgl_disp_data *data = (struct lvgl_disp_data *)disp_driver->user_data;

  disp_driver->hor_res = data->cap.x_resolution;
  disp_driver->ver_res = data->cap.y_resolution;

  buf_nbr_pixels =
      (CONFIG_LV_Z_VDB_SIZE * disp_driver->hor_res * disp_driver->ver_res) /
      100;
  /* one horizontal line is the minimum buffer requirement for lvgl */
  if (buf_nbr_pixels < disp_driver->hor_res) {
    buf_nbr_pixels = disp_driver->hor_res;
  }

  switch (data->cap.current_pixel_format) {
    case PIXEL_FORMAT_ARGB_8888:
      buf_size = 4 * buf_nbr_pixels;
      break;
    case PIXEL_FORMAT_RGB_888:
      buf_size = 3 * buf_nbr_pixels;
      break;
    case PIXEL_FORMAT_RGB_565:
      buf_size = 2 * buf_nbr_pixels;
      break;
    case PIXEL_FORMAT_MONO01:
    case PIXEL_FORMAT_MONO10:
      buf_size = buf_nbr_pixels / 8;
      buf_size += (buf_nbr_pixels % 8) == 0 ? 0 : 1;
      break;
    default:
      return -ENOTSUP;
  }

  buf0 = LVGL_MEM_CUSTOM_ALLOC(buf_size);
  if (buf0 == NULL) {
    LOG_ERR("Failed to allocate memory for rendering buffer");
    return -ENOMEM;
  }

#ifdef CONFIG_LV_Z_DOUBLE_VDB
  buf1 = LVGL_MEM_CUSTOM_ALLOC(buf_size);
  if (buf1 == NULL) {
    LVGL_MEM_CUSTOM_FREE(buf0);
    LOG_ERR("Failed to allocate memory for rendering buffer");
    return -ENOMEM;
  }
#endif

  disp_driver->draw_buf = LVGL_MEM_CUSTOM_ALLOC(sizeof(lv_disp_draw_buf_t));
  if (disp_driver->draw_buf == NULL) {
    LVGL_MEM_CUSTOM_FREE(buf0);
    LVGL_MEM_CUSTOM_FREE(buf1);
    LOG_ERR("Failed to allocate memory to store rendering buffers");
    return -ENOMEM;
  }

  lv_disp_draw_buf_init(disp_driver->draw_buf, display->buf0, display->buf1,
                        buf_nbr_pixels);
  return 0;
}
#endif /* CONFIG_LV_Z_BUFFER_ALLOC_STATIC */

static int lvgl_init(void) {
  int err = 0;

#ifdef CONFIG_LV_Z_MEM_POOL_SYS_HEAP
  lvgl_heap_init();
#endif

#if CONFIG_LV_Z_LOG_LEVEL != 0
  lv_log_register_print_cb(lvgl_log);
#endif

  lv_init();

#ifdef CONFIG_LV_Z_USE_FILESYSTEM
  lvgl_fs_init();
#endif

  struct device *display_dev;
  struct display_data *display;
  lv_disp_t *display_instance;
  for (ssize_t i = 0; i < displays_num; i++) {
    display = &displays[i];
    display_dev = display->dev;

    if (!device_is_ready(display_dev)) {
      LOG_ERR("Display device not ready.");
      return -ENODEV;
    }

    display->data.display_dev = display_dev;
    display_get_capabilities(display_dev, &display->data.cap);

    lv_disp_drv_init(&display->driver);
    display->driver.user_data = (void *)&display->data;

#ifdef CONFIG_LV_Z_FULL_REFRESH
    display->driver.full_refresh = 1;
#endif

    err = lvgl_allocate_rendering_buffers(display);
    if (err != 0) {
      LOG_ERR("Failed to allocate rendering buffers.");
      return err;
    }

    if (set_lvgl_rendering_cb(&display->driver) != 0) {
      LOG_ERR("Display not supported.");
      return -ENOTSUP;
    }

    display_instance = lv_disp_drv_register(&display->driver);
    if (display_instance == NULL) {
      LOG_ERR("Failed to register display device.");
      return -EPERM;
    }

    lv_disp_set_default(display_instance);
  }

  err = lvgl_init_input_devices();
  if (err < 0) {
    LOG_ERR("Failed to initialize input devices.");
    return err;
  }

  return 0;
}

SYS_INIT(lvgl_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
