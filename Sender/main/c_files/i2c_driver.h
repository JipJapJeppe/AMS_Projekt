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

// void i2c_master_init(i2c_speed_mode_t i2c_speed_mode, i2c_port_num_t i2c_port_num, uint8_t sda_gpio_num, uint8_t scl_gpio_num);
