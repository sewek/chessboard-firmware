
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>

#include <zephyr/logging/log.h>

#include "chessboard_tiles.h"

#define DT_DRV_COMPAT zephyr_chessboard_tiles

LOG_MODULE_REGISTER(chessboard_tiles, CONFIG_SENSOR_LOG_LEVEL);

static int chessboard_tiles_channel_get(const struct device *dev,
			       enum sensor_channel chan,
			       struct sensor_value *val)
{
	struct chessboard_tiles_data *drv_data = dev->data;

	switch (chan) {
	case SENSOR_CHAN_ALL:
      val[0].val1 = drv_data->tiles_state;
      val[0].val2 = 0;
      val[1].val1 = drv_data->tiles_state_prev;
      val[1].val2 = 0;
      break;
	default:
		return -ENOTSUP;
	}

	return 0;
}

static int chessboard_tiles_sample_fetch(const struct device *dev,
				enum sensor_channel chan)
{
	struct chessboard_tiles_data *drv_data = dev->data;
	const struct chessboard_tiles_config *cfg = dev->config;
	uint8_t buf[2];

	if (i2c_burst_read_dt(&cfg->i2c, CHESSBOARD_TILES_REG_HAL_STATE, (uint8_t *)buf,
			      2) < 0) {
		LOG_ERR("Failed to read data sample.");
		return -EIO;
	}

	drv_data->tiles_state = buf[0];
   drv_data->tiles_state_prev = buf[1];

	return 0;
}

static const struct sensor_driver_api chessboard_tiles_driver_api = {
	.sample_fetch = chessboard_tiles_sample_fetch,
	.channel_get = chessboard_tiles_channel_get,
};

int chessboard_sensor_init(const struct device *dev) {
   struct chessboard_tiles_data *drv_data = dev->data;
	const struct chessboard_tiles_config *cfg = dev->config;
	uint8_t id;

	if (!device_is_ready(cfg->i2c.bus)) {
		LOG_ERR("Bus device is not ready");
		return -ENODEV;
	}

	/* check chip ID */
	if (i2c_reg_read_byte_dt(&cfg->i2c, CHESSBOARD_TILES_REG_CHIP_ID, &id) < 0) {
		LOG_ERR("Failed to read chip ID.");
		return -EIO;
	}

	if (id != CHESSBOARD_TILES_CHIP_ID) {
		LOG_ERR("Invalid chip ID.");
		return -EINVAL;
	}

	/* enable chip */
	if (i2c_reg_update_byte_dt(&cfg->i2c, CHESSBOARD_TILES_REG_MANAGEMENT, CHESSBOARD_TILES_ENABLE | CHESSBOARD_TILES_ENABLE_HAL | CHESSBOARD_TILES_ENABLE_LED, 1) < 0) {
		LOG_ERR("Failed to enable chip.");
		return -EIO;
	}

   /* set HAL interval to 50ms */
   if (i2c_reg_write_byte_dt(&cfg->i2c, CHESSBOARD_TILES_REG_HAL_INTERVAL, 0x32) < 0) {
      LOG_ERR("Failed to set HAL interval.");
      return -EIO;
   }

   /* set HAL threshold to 192 */
   if (i2c_reg_write_byte_dt(&cfg->i2c, CHESSBOARD_TILES_REG_HAL_THRESHOLD, 0xC0) < 0) {
      LOG_ERR("Failed to set HAL threshold.");
      return -EIO;
   }

   return 0;
}

#define CHESSBOARD_TILES_DEFINE(inst)									                           \
	static struct chessboard_tiles_data chessboard_tiles_data_##inst;						      \
												                                                      \
	static const struct chessboard_tiles_config chessboard_tiles_config_##inst = {			\
		.i2c = I2C_DT_SPEC_INST_GET(inst),						                                 \
	};											                                                      \
												                                                      \
	SENSOR_DEVICE_DT_INST_DEFINE(inst, chessboard_sensor_init, NULL,					         \
			      &chessboard_tiles_data_##inst, &chessboard_tiles_config_##inst,			   \
			      POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,				                        \
			      &chessboard_tiles_driver_api);						                           \

DT_INST_FOREACH_STATUS_OKAY(CHESSBOARD_TILES_DEFINE)
