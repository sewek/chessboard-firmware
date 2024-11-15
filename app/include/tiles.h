/**
 * @file tiles.h
 * @brief Chessboard Tiles driver abstraction
 */

#ifndef TILES_H
#define TILES_H

#include <app/drivers/sensor/tiles.h>
#include <chess_position.h>
#include <chess_types.h>
#include <tile.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

#define DT_DRV_COMPAT chess_tiles
#define TILES_REF(node_id) DEVICE_DT_GET(node_id),

using TileChangeCallback = void (*)(Tile *tile, ChessTileActionType action);

/**
 * @brief Chessboard Tiles driver abstraction
 */
class Tiles {
 public:
  Tiles();
  ~Tiles();

  /**
   * @brief Initialize the tiles driver
   * @return 0 on success, negative error code on failure
   */
  int init();

  /**
   * @brief Get list of tiles on the chessboard
   * @return List of tiles
   */
  Tile *getTiles();

  /**
   * @brief Get the tile at the given position
   * @param position The position of the tile
   * @return The tile at the given position
   */
  Tile *getTile(ChessPosition *position);

  /**
   * @brief Get the tiles count
   * @return The tiles count
   */
  int getTilesCount() { return tiles_count; }

  /**
   * @brief Set tile color
   * @param position The position of the tile
   * @param color The color to set
   * @return 0 on success, negative error code on failure
   */
  int setTileColor(ChessPosition *position, uint32_t color);

  /**
   * @brief Set tile position
   * @param position The position of the tile
   * @param new_position The new position to set
   * @return 0 on success, negative error code on failure
   */
  int setTilePosition(ChessPosition *position, ChessPosition *new_position);

  /**
   * @brief Set tile threshold
   * @param position The position of the tile
   * @param threshold The threshold to set
   * @return 0 on success, negative error code on failure
   */
  int setTileThreshold(ChessPosition *position, uint16_t threshold);

  /**
   * @brief Set tile interval
   * @param position The position of the tile
   * @param interval The interval to set
   * @return 0 on success, negative error code on failure
   */
  int setTileInterval(ChessPosition *position, uint8_t interval);

  /**
   * @brief Set trigger handler
   * @param handler The trigger handler to set
   */
  void setTriggerHandler(sensor_trigger_handler_t handler);

  const struct device *tiles_dev[DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT)] = {
      DT_FOREACH_STATUS_OKAY(DT_DRV_COMPAT, TILES_REF)};
  int tiles_count = ARRAY_SIZE(tiles_dev);
  const struct sensor_trigger trigger = {
      .type = SENSOR_TRIG_DATA_READY,
      .chan = static_cast<enum sensor_channel>(SENSOR_CHAN_TILES_STATE),
  };
  Tile tiles[64];

  static uint8_t positionToIndex(ChessPosition *position);
  static ChessPosition indexToPosition(uint8_t index);

 private:
  sensor_trigger_handler_t trigger_handler = nullptr;
};

#endif  // TILES_H
