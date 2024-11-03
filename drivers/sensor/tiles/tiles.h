/**
 * @file tiles.h
 * @brief Chessboard Tiles driver private header file
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_TILES_H_
#define ZEPHYR_DRIVERS_SENSOR_TILES_H_

#include <inttypes.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/types.h>

#define TILES_REG_CHIP_ID 0x01
#define TILES_CHIP_ID 0x68

#define TILES_REG_MANAGEMENT 0x02
#define TILES_RESET BIT(0)
#define TILES_ENABLE BIT(1)
#define TILES_ENABLE_HAL BIT(2)
#define TILES_ENABLE_LED BIT(3)

#define TILES_REG_HAL_INTERVAL 0x03
#define TILES_REG_HAL_THRESHOLD 0x04

#define TILES_REG_LED_CH1_COLOR 0x10
#define TILES_REG_LED_CH2_COLOR 0x13
#define TILES_REG_LED_CH3_COLOR 0x16
#define TILES_REG_LED_CH4_COLOR 0x19
#define TILES_REG_LED_BRIGHTNESS 0x1F
#define TILES_REG_LED_COLOR_RED BIT(0)
#define TILES_REG_LED_COLOR_GREEN BIT(7)
#define TILES_REG_LED_COLOR_BLUE BIT(15)

#define TILES_REG_CH1_POS 0x20
#define TILES_REG_CH2_POS 0x21
#define TILES_REG_CH3_POS 0x22
#define TILES_REG_CH4_POS 0x23

#define TILES_REG_HAL_STATE 0x30
#define TILES_REG_HAL_STATE_PREV 0x31

#ifdef __cplusplus
extern "C" {
#endif

struct tiles_data {
#ifdef TILES_SENSOR_TRIGGER
  // Trigger and corresponding handler
  sensor_trigger_handler_t trg_handler;
  const struct sensor_trigger *trigger;
#endif

  // Management configuration
  uint8_t config;

  // Hal configuration
  uint8_t hal_interval;
  uint16_t hal_threshold;

  // LED colors
  uint32_t led_ch1_color;
  uint32_t led_ch2_color;
  uint32_t led_ch3_color;
  uint32_t led_ch4_color;

  // Tile positions
  uint8_t ch1_pos;
  uint8_t ch2_pos;
  uint8_t ch3_pos;
  uint8_t ch4_pos;

  // Each bit represents a tile, 1 when piece is present, 0 when empty
  uint8_t tiles_state;

  // Previous state of the tiles
  uint8_t tiles_state_prev;
};

struct tiles_config {
  struct i2c_dt_spec i2c;
  struct k_sem sem;

#ifdef TILES_SENSOR_TRIGGER
  // Thread instance
  struct k_thread thread;
#endif
};

#ifdef __cplusplus
}
#endif

#endif  // ZEPHYR_DRIVERS_SENSOR_TILES_H_
