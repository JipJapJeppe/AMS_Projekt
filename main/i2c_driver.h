#include <stdio.h>
#include "stdint.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "driver/i2c.h"
#include "hal/i2c_types.h"
#include "hal/gpio_types.h"

#define SCL_GPIO_NUM 16
#define SDA_GPIO_NUM 17

#define I2C_NORMAL_MODE 100000
#define I2C_FAST_MODE 400000

#define I2C_MASTER_PORT I2C_NUM_0

#define ZMOD4410_ADDR 0x32

#define thigh 1000  // us
#define tlow 1200 // min SCL clock low
#define tsusta 1200
#define thdsta 1000
#define tsusto 1000
#define tsudat 50
#define thddat 50
#define tbus 1200

void i2c_master_init();
void i2c_write_to_address(uint8_t address, uint8_t *data_to_write);
uint8_t *i2c_read_from_address(uint8_t address);
