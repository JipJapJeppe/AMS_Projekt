#pragma once
#include <stdio.h>
#include "stdint.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "hal/i2c_types.h"
#include "hal/gpio_types.h"
#include "string.h"

#define ACK_ENABLE true
#define ACK_DISABLE false

typedef enum i2c_speed_mode{
    I2C_NORMAL_MODE = 100000,
    I2C_FAST_MODE = 400000,
}i2c_speed_mode_t;

typedef enum i2c_port_num{
    I2C_PORT_0 = I2C_NUM_0,
    I2C_PORT_1 = I2C_NUM_1,
    I2C_PORT_MAX = I2C_NUM_MAX,
}i2c_port_num_t;

class I2cMaster
{
public:
    I2cMaster(i2c_speed_mode_t i2c_speed_mode, i2c_port_num_t i2c_port_num, gpio_num_t sda_gpio_num, gpio_num_t scl_gpio_num);
    void init();
    void writeToDeviceAddress(uint8_t dev_addr, uint8_t *data, size_t data_len);
    void readFromDeviceAddress(uint8_t dev_addr, uint8_t *read_data, size_t data_len);
    gpio_num_t getSdaGpio() const;
    gpio_num_t getSclGpio() const;
private:
    const i2c_speed_mode_t _i2c_speed_mode;
    const i2c_port_num_t _i2c_port_num;
    const gpio_num_t _sda_gpio_num;
    const gpio_num_t _scl_gpio_num;
};
