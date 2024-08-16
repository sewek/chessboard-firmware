// #include <chess_position.h>
#include <chess_position.h>
#include <lvgl.h>
#include <lvgl_display.h>
#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define CONFIG_BOARD "nRF52840"

int main() {
  printk("Hello World! %s\n", CONFIG_BOARD);

  ChessPosition position("a1");
  position.isValid();

  // lv_disp_set_default(registered_displays[0]);

  static lv_obj_t *meter;
  meter = lv_meter_create(lv_scr_act());
  lv_obj_center(meter);
  lv_obj_set_size(meter, 200, 200);

  lv_obj_remove_style(meter, nullptr, LV_PART_INDICATOR);
  lv_task_handler();
  // display_blanking_off(display_dev);

  while (true) {
    lv_task_handler();
    k_msleep(1000);
  }

  return 0;
}
