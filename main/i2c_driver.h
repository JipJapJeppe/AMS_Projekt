#include <stdio.h>
#include "stdint.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "driver/i2c.h"
#include "hal/i2c_types.h"
#include "hal/gpio_types.h"
#include "string.h"

#define I2C_NORMAL_MODE 100000
#define I2C_FAST_MODE 400000

#define I2C_MASTER_PORT I2C_NUM_0
#define ACK_ENABLE true
#define ACK_DISABLE false

#define SCL_GPIO_NUM 16
#define SDA_GPIO_NUM 17

void i2c_master_init(uint32_t i2c_mode);
void i2c_write_to_device_address(uint8_t dev_addr, uint8_t *data, size_t data_len);
void i2c_read_from_device_address(uint8_t dev_addr, uint8_t *read_data, size_t data_len);
