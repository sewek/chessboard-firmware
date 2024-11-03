/**
 * @file tiles.c
 * @brief Chessboard Tiles driver implementation
 */

#include <app/drivers/sensor/tiles.h>
#include <inttypes.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/types.h>

#define DT_DRV_COMPAT chess_tiles

#define TILES_REG_CHIP_ID 0x01
#define TILES_CHIP_ID 0x69

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

LOG_MODULE_REGISTER(tiles_sensor, CONFIG_SENSOR_LOG_LEVEL);

struct tiles_data {
#ifdef CONFIG_TILES_SENSOR_TRIGGER
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
};

#ifdef CONFIG_TILES_SENSOR_TRIGGER
// Thread instance
static struct k_thread tiles_thread;
static struct k_sem tiles_sem;
#endif

#ifdef CONFIG_TILES_SENSOR_TRIGGER
static K_THREAD_STACK_DEFINE(thread_stack,
                             CONFIG_TILES_SENSOR_TRIGGER_THREAD_STACK_SIZE);
static K_TIMER_DEFINE(fetch_state_timer, NULL, NULL);
#endif

static int tiles_channel_get(const struct device *dev, enum sensor_channel chan,
                             struct sensor_value *val) {
  struct tiles_data *data = dev->data;

  switch (chan) {
    case SENSOR_CHAN_TILES_STATE:
      val->val1 = data->tiles_state;
      val->val2 = 0;
      break;
    case SENSOR_CHAN_TILES_STATE_PREV:
      val->val1 = data->tiles_state_prev;
      val->val2 = 0;
      break;
    default:
      return -ENOTSUP;
  }

  return 0;
}

static int tiles_sample_fetch(const struct device *dev,
                              enum sensor_channel chan) {
  struct tiles_data *data = dev->data;
  const struct tiles_config *cfg = dev->config;
  int ret = 0;
  uint8_t buff[2];

  if (k_sem_take(&tiles_sem, K_FOREVER) < 0) {
    LOG_ERR("Failed to take semaphore.");
    return -EBUSY;
  }

  ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_HAL_STATE, &buff[0]);
  if (ret < 0) {
    LOG_ERR("Failed to read HAL state, error: %d", ret);
    k_sem_give(&tiles_sem);
    return ret;
  } else {
    data->tiles_state = buff[0];
  }

  ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_HAL_STATE_PREV, &buff[1]);
  if (ret < 0) {
    LOG_ERR("Failed to read HAL prev state, error: %d", ret);
    k_sem_give(&tiles_sem);
    return ret;
  } else {
    data->tiles_state_prev = buff[1];
  }

  k_sem_give(&tiles_sem);

  return 0;
}

static int tiles_attr_set(const struct device *dev, enum sensor_channel chan,
                          enum sensor_attribute attr,
                          const struct sensor_value *val) {
  int ret = 0;
  uint8_t buff[4];
  struct tiles_data *data = dev->data;
  struct tiles_config *cfg = dev->config;

  if ((enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_MANAGEMENT &&
      (enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_HAL_CONFIG &&
      (enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_LED_COLOR &&
      (enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_POS) {
    LOG_ERR("Channel not supported");
    return -ENOTSUP;
  }

  if (k_sem_take(&tiles_sem, K_FOREVER) < 0) {
    LOG_ERR("Failed to take semaphore.");
    return -EBUSY;
  }

  switch ((enum sensor_attribute_tiles)attr) {
    case SENSOR_ATTR_TILES_RESET:
      if (val->val1) {
        data->config |= TILES_RESET;
      } else {
        data->config &= ~TILES_RESET;
      }

      ret = i2c_reg_update_byte_dt(&cfg->i2c, TILES_REG_MANAGEMENT, TILES_RESET,
                                   data->config & TILES_RESET);
      break;
    case SENSOR_ATTR_TILES_ENABLE:
      if (val->val1) {
        data->config |= TILES_ENABLE;
      } else {
        data->config &= ~TILES_ENABLE;
      }

      ret = i2c_reg_update_byte_dt(&cfg->i2c, TILES_REG_MANAGEMENT,
                                   TILES_ENABLE, data->config & TILES_ENABLE);
      break;
    case SENSOR_ATTR_TILES_ENABLE_HAL:
      if (val->val1) {
        data->config |= TILES_ENABLE_HAL;
      } else {
        data->config &= ~TILES_ENABLE_HAL;
      }

      ret = i2c_reg_update_byte_dt(&cfg->i2c, TILES_REG_MANAGEMENT,
                                   TILES_ENABLE_HAL,
                                   data->config & TILES_ENABLE_HAL);
      break;
    case SENSOR_ATTR_TILES_ENABLE_LED:
      if (val->val1) {
        data->config |= TILES_ENABLE_LED;
      } else {
        data->config &= ~TILES_ENABLE_LED;
      }

      ret = i2c_reg_update_byte_dt(&cfg->i2c, TILES_REG_MANAGEMENT,
                                   TILES_ENABLE_LED,
                                   data->config & TILES_ENABLE_LED);
      break;
    case SENSOR_ATTR_TILES_HAL_INTERVAL:
      data->hal_interval = val->val1 & 0xFF;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_HAL_INTERVAL,
                                  data->hal_interval);
      break;
    case SENSOR_ATTR_TILES_HAL_THRESHOLD:
      data->hal_threshold = val->val1 & 0xFFFF;
      buff[0] = data->hal_threshold & 0xFF;
      buff[1] = (data->hal_threshold >> 8) & 0xFF;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_HAL_THRESHOLD, buff[0]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_HAL_THRESHOLD + 1,
                                  buff[1]);
      break;
    case SENSOR_ATTR_TILES_LED_CH1_COLOR:
      data->led_ch1_color = val->val1;
      buff[0] = data->led_ch1_color & 0xFF;
      buff[1] = (data->led_ch1_color >> 8) & 0xFF;
      buff[2] = (data->led_ch1_color >> 16) & 0xFF;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH1_COLOR, buff[0]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH1_COLOR + 1,
                                  buff[1]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH1_COLOR + 2,
                                  buff[2]);
      break;
    case SENSOR_ATTR_TILES_LED_CH2_COLOR:
      data->led_ch2_color = val->val1;
      buff[0] = data->led_ch2_color & 0xFF;
      buff[1] = (data->led_ch2_color >> 8) & 0xFF;
      buff[2] = (data->led_ch2_color >> 16) & 0xFF;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH2_COLOR, buff[0]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH2_COLOR + 1,
                                  buff[1]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH2_COLOR + 2,
                                  buff[2]);
      break;
    case SENSOR_ATTR_TILES_LED_CH3_COLOR:
      data->led_ch3_color = val->val1;
      buff[0] = data->led_ch3_color & 0xFF;
      buff[1] = (data->led_ch3_color >> 8) & 0xFF;
      buff[2] = (data->led_ch3_color >> 16) & 0xFF;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH3_COLOR, buff[0]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH3_COLOR + 1,
                                  buff[1]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH3_COLOR + 2,
                                  buff[2]);
      break;
    case SENSOR_ATTR_TILES_LED_CH4_COLOR:
      data->led_ch4_color = val->val1;
      buff[0] = data->led_ch4_color & 0xFF;
      buff[1] = (data->led_ch4_color >> 8) & 0xFF;
      buff[2] = (data->led_ch4_color >> 16) & 0xFF;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH4_COLOR, buff[0]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH4_COLOR + 1,
                                  buff[1]);
      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_LED_CH4_COLOR + 2,
                                  buff[2]);
      break;
    case SENSOR_ATTR_TILES_CH1_POS:
      data->ch1_pos = val->val1 & 0x0F;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_CH1_POS, data->ch1_pos);
      break;
    case SENSOR_ATTR_TILES_CH2_POS:
      data->ch2_pos = val->val1 & 0x0F;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_CH2_POS, data->ch2_pos);
      break;
    case SENSOR_ATTR_TILES_CH3_POS:
      data->ch3_pos = val->val1 & 0x0F;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_CH3_POS, data->ch3_pos);
      break;
    case SENSOR_ATTR_TILES_CH4_POS:
      data->ch4_pos = val->val1 & 0x0F;

      ret = i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_CH4_POS, data->ch4_pos);
      break;
    default:
      LOG_ERR("Sensor attribute not supported");
      ret = -ENOTSUP;
  }

  k_sem_give(&tiles_sem);

  return ret;
}

// NOLINTNEXTLINE
static int tiles_attr_get(const struct device *dev, enum sensor_channel chan,
                          enum sensor_attribute attr,
                          struct sensor_value *val) {
  int ret = 0;
  struct tiles_data *data = dev->data;
  struct tiles_config *cfg = dev->config;

  if ((enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_MANAGEMENT &&
      (enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_HAL_CONFIG &&
      (enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_LED_COLOR &&
      (enum sensor_channel_tiles)chan != SENSOR_CHAN_TILES_POS) {
    LOG_ERR("Channel not supported");
    return -ENOTSUP;
  }

  if (k_sem_take(&tiles_sem, K_FOREVER) < 0) {
    LOG_ERR("Failed to take semaphore.");
    return -EBUSY;
  }

  switch ((enum sensor_attribute_tiles)attr) {
    case SENSOR_ATTR_TILES_ENABLE:
    case SENSOR_ATTR_TILES_ENABLE_HAL:
    case SENSOR_ATTR_TILES_ENABLE_LED:
      ret =
          i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_MANAGEMENT, &data->config);
      break;
    case SENSOR_ATTR_TILES_HAL_INTERVAL:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_HAL_INTERVAL,
                                 &data->hal_interval);
      break;
    case SENSOR_ATTR_TILES_HAL_THRESHOLD:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_HAL_THRESHOLD,
                                 (uint8_t *)&data->hal_threshold);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_HAL_THRESHOLD + 1,
                                 (uint8_t *)&data->hal_threshold + 1);
      break;
    case SENSOR_ATTR_TILES_LED_CH1_COLOR:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH1_COLOR,
                                 (uint8_t *)&data->led_ch1_color);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH1_COLOR + 1,
                                 (uint8_t *)&data->led_ch1_color + 1);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH1_COLOR + 2,
                                 (uint8_t *)&data->led_ch1_color + 2);
      break;
    case SENSOR_ATTR_TILES_LED_CH2_COLOR:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH2_COLOR,
                                 (uint8_t *)&data->led_ch2_color);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH2_COLOR + 1,
                                 (uint8_t *)&data->led_ch2_color + 1);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH2_COLOR + 2,
                                 (uint8_t *)&data->led_ch2_color + 2);
      break;
    case SENSOR_ATTR_TILES_LED_CH3_COLOR:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH3_COLOR,
                                 (uint8_t *)&data->led_ch3_color);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH3_COLOR + 1,
                                 (uint8_t *)&data->led_ch3_color + 1);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH3_COLOR + 2,
                                 (uint8_t *)&data->led_ch3_color + 2);
      break;
    case SENSOR_ATTR_TILES_LED_CH4_COLOR:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH4_COLOR,
                                 (uint8_t *)&data->led_ch4_color);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH4_COLOR + 1,
                                 (uint8_t *)&data->led_ch4_color + 1);
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_LED_CH4_COLOR + 2,
                                 (uint8_t *)&data->led_ch4_color + 2);
      break;
    case SENSOR_ATTR_TILES_CH1_POS:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_CH1_POS, &data->ch1_pos);
      break;
    case SENSOR_ATTR_TILES_CH2_POS:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_CH2_POS, &data->ch2_pos);
      break;
    case SENSOR_ATTR_TILES_CH3_POS:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_CH3_POS, &data->ch3_pos);
      break;
    case SENSOR_ATTR_TILES_CH4_POS:
      ret = i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_CH4_POS, &data->ch4_pos);
      break;
    default:
      LOG_ERR("Sensor attribute not supported");
      ret = -ENOTSUP;
      break;
  }

  k_sem_give(&tiles_sem);

  switch ((enum sensor_attribute_tiles)attr) {
    case SENSOR_ATTR_TILES_ENABLE:
      val->val1 = data->config & TILES_ENABLE;
      break;
    case SENSOR_ATTR_TILES_ENABLE_HAL:
      val->val1 = data->config & TILES_ENABLE_HAL;
      break;
    case SENSOR_ATTR_TILES_ENABLE_LED:
      val->val1 = data->config & TILES_ENABLE_LED;
      break;
    case SENSOR_ATTR_TILES_HAL_INTERVAL:
      val->val1 = data->hal_interval;
      break;
    case SENSOR_ATTR_TILES_HAL_THRESHOLD:
      val->val1 = data->hal_threshold;
      break;
    case SENSOR_ATTR_TILES_LED_CH1_COLOR:
      val->val1 = data->led_ch1_color;
      break;
    case SENSOR_ATTR_TILES_LED_CH2_COLOR:
      val->val1 = data->led_ch2_color;
      break;
    case SENSOR_ATTR_TILES_LED_CH3_COLOR:
      val->val1 = data->led_ch3_color;
      break;
    case SENSOR_ATTR_TILES_LED_CH4_COLOR:
      val->val1 = data->led_ch4_color;
      break;
    case SENSOR_ATTR_TILES_CH1_POS:
      val->val1 = data->ch1_pos;
      break;
    case SENSOR_ATTR_TILES_CH2_POS:
      val->val1 = data->ch2_pos;
      break;
    case SENSOR_ATTR_TILES_CH3_POS:
      val->val1 = data->ch3_pos;
      break;
    case SENSOR_ATTR_TILES_CH4_POS:
      val->val1 = data->ch4_pos;
      break;
    default:
      LOG_ERR("Sensor attribute not supported");
      ret = -ENOTSUP;
      break;
  }

  return ret;
}

#ifdef CONFIG_TILES_SENSOR_TRIGGER
static int tiles_trigger_set(const struct device *dev,
                             const struct sensor_trigger *trig,
                             sensor_trigger_handler_t handler) {
  struct tiles_data *data = dev->data;
  struct tiles_config *cfg = dev->config;

  if (trig->type != SENSOR_TRIG_TIMER && trig->type != SENSOR_TRIG_DATA_READY) {
    LOG_ERR("Unsupported sensor trigger");
    return -ENOTSUP;
  }

  if ((trig->chan == SENSOR_CHAN_ALL) ||
      (trig->chan == SENSOR_CHAN_TILES_STATE) ||
      (trig->chan == SENSOR_CHAN_TILES_STATE_PREV)) {
    data->trigger = trig;
    data->trg_handler = handler;
  } else {
    LOG_ERR("Unsupported sensor channel");
    return -ENOTSUP;
  }

  return 0;
}

static void tiles_thread_fn(void *arg1, void *arg2, void *arg3) {
  ARG_UNUSED(arg2);
  ARG_UNUSED(arg3);
  const struct device *dev = (const struct device *)arg1;
  struct tiles_config *cfg = dev->config;
  struct tiles_data *data = dev->data;
  uint8_t prev_state = 0;

  while (1) {
    if (!(data->config & (TILES_ENABLE | TILES_ENABLE_HAL))) {
      k_sleep(K_MSEC(CONFIG_TILES_SENSOR_TRIGGER_THREAD_PERIOD_MS));
      continue;
    }

    if (k_timer_remaining_get(&fetch_state_timer) == 0) {
      if (tiles_sample_fetch(
              dev, (enum sensor_channel)SENSOR_CHAN_TILES_STATE) < 0) {
        LOG_ERR("Failed to fetch data sample in thread");
        continue;
      }

      if (data->trigger->type == SENSOR_TRIG_TIMER && data->trg_handler) {
        data->trg_handler(dev, data->trigger);
      }

      if (data->trigger->type == SENSOR_TRIG_DATA_READY && data->trg_handler &&
          prev_state != data->tiles_state) {
        prev_state = data->tiles_state;
        data->trg_handler(dev, data->trigger);
      }

      k_timer_start(&fetch_state_timer,
                    K_MSEC(CONFIG_TILES_SENSOR_TRIGGER_INTERVAL_MS), K_NO_WAIT);
    }
    k_sleep(K_MSEC(CONFIG_TILES_SENSOR_TRIGGER_THREAD_PERIOD_MS));
  }
}
#endif

static const struct sensor_driver_api kTilesDriverApi = {
    .attr_set = tiles_attr_set,
    .attr_get = tiles_attr_get,
    .sample_fetch = tiles_sample_fetch,
    .channel_get = tiles_channel_get,
#ifdef CONFIG_TILES_SENSOR_TRIGGER
    .trigger_set = tiles_trigger_set,
#endif
};

// NOLINTNEXTLINE
int chessboard_sensor_init(const struct device *dev) {
  struct tiles_data *data = dev->data;
  const struct tiles_config *cfg = dev->config;
  uint8_t id;

  if (k_sem_init(&tiles_sem, 1, 1) < 0) {
    LOG_ERR("Failed to initialize semaphore.");
    return -EBUSY;
  }

  if (k_sem_take(&tiles_sem, K_FOREVER) < 0) {
    LOG_ERR("Failed to take semaphore.");
    return -EBUSY;
  }

  if (!device_is_ready(cfg->i2c.bus)) {
    LOG_ERR("Bus device is not ready");
    return -ENODEV;
  }

  /* check chip ID */
  if (i2c_reg_read_byte_dt(&cfg->i2c, TILES_REG_CHIP_ID, &id) < 0) {
    LOG_ERR("Failed to read chip ID.");
    return -EIO;
  }

  if (id != TILES_CHIP_ID) {
    LOG_ERR("Invalid chip ID.");
    return -EINVAL;
  }

  data->config = 0;
  data->config |= TILES_ENABLE | TILES_ENABLE_HAL | TILES_ENABLE_LED;
  data->hal_interval = 0x32;   // 50ms
  data->hal_threshold = 0x0a;  // 10G * 1.4mV/G = 14mV

  /* set HAL interval */
  if (i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_HAL_INTERVAL,
                            data->hal_interval) < 0) {
    LOG_ERR("Failed to set HAL interval.");
    return -EIO;
  }

  /* set HAL threshold */
  char buff[2] = {data->hal_threshold & 0xFF,
                  (data->hal_threshold >> 8) & 0xFF};

  if (i2c_burst_write_dt(&cfg->i2c, TILES_REG_HAL_THRESHOLD, buff, 2) < 0) {
    LOG_ERR("Failed to set HAL threshold.");
    return -EIO;
  }

  /* enable chip */
  if (i2c_reg_write_byte_dt(&cfg->i2c, TILES_REG_MANAGEMENT, data->config) <
      0) {
    LOG_ERR("Failed to enable chip.");
    return -EIO;
  }

  k_sem_give(&tiles_sem);

#ifdef CONFIG_TILES_SENSOR_TRIGGER
  k_thread_create(&tiles_thread, thread_stack,
                  CONFIG_TILES_SENSOR_TRIGGER_THREAD_STACK_SIZE,
                  tiles_thread_fn, (void *)dev, NULL, NULL,
                  K_PRIO_COOP(CONFIG_TILES_SENSOR_TRIGGER_THREAD_PRIORITY), 0,
                  K_NO_WAIT);
  k_thread_name_set(&tiles_thread, "tiles_thread");

  k_timer_start(&fetch_state_timer,
                K_MSEC(CONFIG_TILES_SENSOR_TRIGGER_INTERVAL_MS), K_NO_WAIT);

  k_thread_start(&tiles_thread);
#endif

  return 0;
}

#define TILES_DEFINE(inst)                                               \
  static struct tiles_data tiles_data_##inst;                            \
                                                                         \
  static const struct tiles_config tiles_config_##inst = {               \
      .i2c = I2C_DT_SPEC_INST_GET(inst),                                 \
  };                                                                     \
                                                                         \
  SENSOR_DEVICE_DT_INST_DEFINE(inst, chessboard_sensor_init, NULL,       \
                               &tiles_data_##inst, &tiles_config_##inst, \
                               POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY, \
                               &kTilesDriverApi);

DT_INST_FOREACH_STATUS_OKAY(TILES_DEFINE)
