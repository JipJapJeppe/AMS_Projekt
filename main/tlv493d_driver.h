#include <stdio.h>
#include "stdint.h"
#include "unistd.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "hal/i2c_types.h"
#include "hal/gpio_types.h"
#include "string.h"
#include "driver/gpio.h"

#include "i2c_driver.h"

#define PWR_GPIO 18

#define TLV493D_ADDR0 0x1F
#define TLV493D_ADDR1 0x5E

#define TLV493D_ADDR TLV493D_ADDR0

#define TLV493D_I2C_MODE I2C_FAST_MODE

#define MODE_1_REG 0b01111000
#define MODE_2_REG 0b00011111

void tlv493d_init();
void tlv493d_write_data(uint8_t *write_data, size_t data_len);
void tlv493d_read_axis_data(int16_t *read_data, size_t data_len);
void tlv493d_read_temp_data(uint8_t *read_data, size_t data_len);
void tlv493d_full_reset();
