/**
 * @file tiles.h
 * @brief Chessboard Tiles driver public header file
 */

#ifndef APP_DRIVERS_SENSOR_TILES_H_
#define APP_DRIVERS_SENSOR_TILES_H_

#include <zephyr/drivers/sensor.h>

#if __cplusplus
extern "C" {
#endif

enum sensor_channel_tiles {
  /** Tiles management **/
  SENSOR_CHAN_TILES_MANAGEMENT = SENSOR_CHAN_PRIV_START,
  /** Tiles HAL config **/
  SENSOR_CHAN_TILES_HAL_CONFIG,
  /** Tiles LED color **/
  SENSOR_CHAN_TILES_LED_COLOR,
  /** Tiles position **/
  SENSOR_CHAN_TILES_POS,
  /** Tiles state **/
  SENSOR_CHAN_TILES_STATE,
  /** Tiles previous state **/
  SENSOR_CHAN_TILES_STATE_PREV,
};

enum sensor_attribute_tiles {
  /** Reset device **/
  SENSOR_ATTR_TILES_RESET = SENSOR_ATTR_PRIV_START,
  /** Enable device **/
  SENSOR_ATTR_TILES_ENABLE,
  /** Enable HAL **/
  SENSOR_ATTR_TILES_ENABLE_HAL,
  /** Enable LED **/
  SENSOR_ATTR_TILES_ENABLE_LED,
  /** Set HAL interval **/
  SENSOR_ATTR_TILES_HAL_INTERVAL,
  /** Set HAL threshold **/
  SENSOR_ATTR_TILES_HAL_THRESHOLD,
  /** Set CH1 LED color **/
  SENSOR_ATTR_TILES_LED_CH1_COLOR,
  /** Set CH2 LED color **/
  SENSOR_ATTR_TILES_LED_CH2_COLOR,
  /** Set CH3 LED color **/
  SENSOR_ATTR_TILES_LED_CH3_COLOR,
  /** Set CH4 LED color **/
  SENSOR_ATTR_TILES_LED_CH4_COLOR,
  /** Set CH1 tile position **/
  SENSOR_ATTR_TILES_CH1_POS,
  /** Set CH2 tile position **/
  SENSOR_ATTR_TILES_CH2_POS,
  /** Set CH3 tile position **/
  SENSOR_ATTR_TILES_CH3_POS,
  /** Set CH4 tile position **/
  SENSOR_ATTR_TILES_CH4_POS,
};

#if __cplusplus
}
#endif

#endif  // APP_DRIVERS_SENSOR_TILES_H_
