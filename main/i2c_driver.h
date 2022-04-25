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

#define SCL_GPIO_NUM 16
#define SDA_GPIO_NUM 17

#define ZMOD4410_ADDR 0x32

#define thigh 1000  // minimum SCL clock high
#define tlow 1200   // minimum SCL clock low
#define tsusta 1200 // minimum setup cycles start
#define thdsta 1000 // minimum hold cycles start
#define tsusto 1000 // minimum setup cycles stop
#define tsudat 50   // minimum setup cycles data
#define thddat 50   // minimum hold cycles data
#define tbus 1200   // minimum bus cycles

void i2c_master_init();
void i2c_write_to_register_address(uint8_t register_address, uint8_t *data_to_write, size_t data_length);
void i2c_read_from_register_address(uint8_t register_address, uint8_t *read_data);
