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
#include "driver/gpio.h"

#include "i2c_driver.h"

#define PWR_GPIO 18

#define TLV493D_ADDR0 0x1F

void tlv493d_init();
void tlv493d_write_data(uint8_t *write_data, size_t data_len);
void tlv493d_read_axis_data(uint8_t *read_data, size_t data_len);
void tlv493d_read_temp_data(uint8_t *read_data, size_t data_len);
void tlv493d_full_reset();
