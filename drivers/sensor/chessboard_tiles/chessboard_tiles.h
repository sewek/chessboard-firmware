
#ifndef ZEPHYR_DRIVERS_SENSOR_CHESSBOARD_TILES_H_
#define ZEPHYR_DRIVERS_SENSOR_CHESSBOARD_TILES_H_

#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>
#include <zephyr/types.h>

#define CHESSBOARD_TILES_REG_CHIP_ID 0x01
#define CHESSBOARD_TILES_CHIP_ID 0x68

#define CHESSBOARD_TILES_REG_MANAGEMENT 0x02
#define CHESSBOARD_TILES_RESET BIT(0)
#define CHESSBOARD_TILES_ENABLE BIT(1)
#define CHESSBOARD_TILES_ENABLE_HAL BIT(2)
#define CHESSBOARD_TILES_ENABLE_LED BIT(3)

#define CHESSBOARD_TILES_REG_HAL_INTERVAL 0x03
#define CHESSBOARD_TILES_REG_HAL_THRESHOLD 0x04

#define CHESSBOARD_TILES_REG_LED_UPPER_LEFT_COLOR 0x11
#define CHESSBOARD_TILES_REG_LED_UPPER_RIGHT_COLOR 0x12
#define CHESSBOARD_TILES_REG_LED_LOWER_LEFT_COLOR 0x13
#define CHESSBOARD_TILES_REG_LED_LOWER_RIGHT_COLOR 0x14
#define CHESSBOARD_TILES_REG_LED_COLOR_RED BIT(0)
#define CHESSBOARD_TILES_REG_LED_COLOR_GREEN BIT(7)
#define CHESSBOARD_TILES_REG_LED_COLOR_BLUE BIT(15)
#define CHESSBOARD_TILES_REG_LED_COLOR_WHITE BIT(23)

#define CHESSBOARD_TILES_REG_HAL_STATE 0x21
#define CHESSBOARD_TILES_REG_HAL_STATE_PREV 0x22

struct chessboard_tiles_data {
   // Tiles names, first 4 bits are the row, last 4 bits are the column
   uint8_t upper_left_tile;
   uint8_t upper_right_tile;
   uint8_t lower_left_tile;
   uint8_t lower_right_tile;

   // Each bit represents a tile, 1 when piece is present, 0 when empty
   uint8_t tiles_state;

   // Previous state of the tiles
   uint8_t tiles_state_prev;


};

struct chessboard_tiles_config {
	struct i2c_dt_spec i2c;
};

#endif  // ZEPHYR_DRIVERS_SENSOR_CHESSBOARD_TILES_H_
