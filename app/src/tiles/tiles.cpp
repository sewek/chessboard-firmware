/**
 * @file tiles.cpp
 * @brief Chessboard Tiles driver abstraction
 */

#include <app/drivers/sensor/tiles.h>
#include <chess_types.h>
#include <tiles.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(tiles, LOG_LEVEL_DBG);

Tiles::Tiles() {}
Tiles::~Tiles() {}

int Tiles::init() {
  struct sensor_value buff_pos;
  struct sensor_value buff_state;
  struct sensor_value buff_color;
  const struct device *dev;
  for (int i = 0; i < this->tiles_count; i++) {
    dev = this->tiles_dev[i];

    // Check if device is ready
    if (!device_is_ready(dev)) {
      LOG_ERR("Device %s is not ready", dev->name);
      return -ENODEV;
    }

    // Fetch sample
    if (sensor_sample_fetch(dev) < 0) {
      LOG_ERR("Failed to fetch sample for device %s", dev->name);
      return -ENOTSUP;
    }

    // Channel 1
    sensor_attr_get(
        dev, static_cast<enum sensor_channel>(SENSOR_CHAN_TILES_POS),
        static_cast<enum sensor_attribute>(SENSOR_ATTR_TILES_CH1_POS),
        &buff_pos);
    sensor_channel_get(
        dev, static_cast<enum sensor_channel>(SENSOR_CHAN_TILES_STATE),
        &buff_state);
    sensor_attr_get(
        dev, static_cast<enum sensor_channel>(SENSOR_CHAN_TILES_LED_COLOR),
        static_cast<enum sensor_attribute>(SENSOR_ATTR_TILES_LED_CH1_COLOR),
        &buff_color);

    ChessPosition ch1_position = ChessPosition((uint8_t)(buff_pos.val1));
    this->tiles[Tiles::positionToIndex(&ch1_position)] =
        Tile(&ch1_position, buff_color.val1, buff_state.val1 & 0x01,
             (device *)dev, 1);

    // Channel 2
    sensor_attr_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_POS,
                    (enum sensor_attribute)SENSOR_ATTR_TILES_CH2_POS,
                    &buff_pos);
    sensor_channel_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_STATE,
                       &buff_state);
    sensor_attr_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_LED_COLOR,
                    (enum sensor_attribute)SENSOR_ATTR_TILES_LED_CH2_COLOR,
                    &buff_color);

    ChessPosition ch2_position = ChessPosition((uint8_t)buff_pos.val1);
    this->tiles[Tiles::positionToIndex(&ch2_position)] =
        Tile(&ch2_position, buff_color.val1, buff_state.val1 & 0x02,
             (device *)dev, 2);

    // Channel 3
    sensor_attr_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_POS,
                    (enum sensor_attribute)SENSOR_ATTR_TILES_CH3_POS,
                    &buff_pos);
    sensor_channel_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_STATE,
                       &buff_state);
    sensor_attr_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_LED_COLOR,
                    (enum sensor_attribute)SENSOR_ATTR_TILES_LED_CH3_COLOR,
                    &buff_color);

    ChessPosition ch3_position = ChessPosition((uint8_t)buff_pos.val1);
    this->tiles[Tiles::positionToIndex(&ch3_position)] =
        Tile(&ch3_position, buff_color.val1, buff_state.val1 & 0x04,
             (device *)dev, 3);

    // Channel 4
    sensor_attr_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_POS,
                    (enum sensor_attribute)SENSOR_ATTR_TILES_CH4_POS,
                    &buff_pos);
    sensor_channel_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_STATE,
                       &buff_state);
    sensor_attr_get(dev, (enum sensor_channel)SENSOR_CHAN_TILES_LED_COLOR,
                    (enum sensor_attribute)SENSOR_ATTR_TILES_LED_CH4_COLOR,
                    &buff_color);

    ChessPosition ch4_position = ChessPosition((uint8_t)buff_pos.val1);
    this->tiles[Tiles::positionToIndex(&ch4_position)] =
        Tile(&ch4_position, buff_color.val1, buff_state.val1 & 0x08,
             (device *)dev, 4);

#ifdef CONFIG_TILES_SENSOR_TRIGGER
    // Trigger
    if (this->trigger_handler != nullptr) {
      if (sensor_trigger_set(dev, &this->trigger, this->trigger_handler) < 0) {
        LOG_ERR("Failed to set trigger for device %s", dev->name);
        return -ENOTSUP;
      }
      LOG_DBG("Trigger set for device %s", dev->name);
    } else {
      LOG_WRN("No trigger handler set");
    }
#endif
  }

  return 0;
}

Tile *Tiles::getTiles() { return this->tiles; }

Tile *Tiles::getTile(ChessPosition *position) {
  if (Tiles::positionToIndex(position) >= 64) {
    return nullptr;
  }

  return &this->tiles[Tiles::positionToIndex(position)];
}

void Tiles::setTriggerHandler(sensor_trigger_handler_t handler) {
  trigger_handler = handler;
}

int Tiles::setTileColor(ChessPosition *position, uint32_t color) {
  Tile *tile = this->getTile(position);
  if (tile == nullptr) {
    LOG_ERR("Tile not found");
    return -ENOEXEC;
  }

  if (tile->dev == nullptr) {
    LOG_ERR("Device not found");
    return -ENOEXEC;
  }

  tile->color = color;

  struct sensor_value buff = {
      .val1 = color,
      .val2 = 0,
  };

  LOG_INF("Setting tile color to %x", color);

  if (sensor_attr_set(tile->dev,
                      (enum sensor_channel)SENSOR_CHAN_TILES_LED_COLOR,
                      (enum sensor_attribute)(SENSOR_ATTR_TILES_LED_CH1_COLOR +
                                              tile->channel - 1),
                      &buff) < 0) {
    LOG_ERR("Failed to set tile color");
    return -ENOTSUP;
  }

  return 0;
}

int Tiles::setTilePosition(ChessPosition *position,
                           ChessPosition *new_position) {
  Tile *tile = getTile(position);
  if (tile == nullptr) {
    return -ENOEXEC;
  }

  tile->position = *new_position;

  struct sensor_value buff = {
      .val1 = new_position->toData(),
      .val2 = 0,
  };

  if (sensor_attr_set(tile->dev, (enum sensor_channel)SENSOR_CHAN_TILES_POS,
                      (enum sensor_attribute)(SENSOR_ATTR_TILES_CH1_POS +
                                              tile->channel - 1),
                      &buff) < 0) {
    return -ENOTSUP;
  }

  return 0;
}

int Tiles::setTileThreshold(ChessPosition *position, uint16_t threshold) {
  Tile *tile = getTile(position);
  if (tile == nullptr) {
    return -ENOEXEC;
  }

  struct sensor_value buff = {
      .val1 = threshold,
      .val2 = 0,
  };

  if (sensor_attr_set(tile->dev,
                      (enum sensor_channel)SENSOR_CHAN_TILES_HAL_CONFIG,
                      (enum sensor_attribute)(SENSOR_ATTR_TILES_HAL_THRESHOLD +
                                              tile->channel - 1),
                      &buff) < 0) {
    return -ENOTSUP;
  }

  return 0;
}

int Tiles::setTileInterval(ChessPosition *position, uint8_t interval) {
  Tile *tile = getTile(position);
  if (tile == nullptr) {
    return -ENOEXEC;
  }

  struct sensor_value buff = {
      .val1 = interval,
      .val2 = 0,
  };

  if (sensor_attr_set(tile->dev,
                      (enum sensor_channel)SENSOR_CHAN_TILES_HAL_CONFIG,
                      (enum sensor_attribute)(SENSOR_ATTR_TILES_HAL_INTERVAL +
                                              tile->channel - 1),
                      &buff) < 0) {
    return -ENOTSUP;
  }

  return 0;
}

uint8_t Tiles::positionToIndex(ChessPosition *position) {
  if (!position->isValid()) {
    LOG_ERR("Invalid position");
    return 0;
  }

  return (position->getFile() - 1) * 8 + (position->getRank() - 1);
}

ChessPosition Tiles::indexToPosition(uint8_t index) {
  return ChessPosition((index / 8) + 1, (index % 8) + 1);
}
