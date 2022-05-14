#pragma once
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

#include "i2c_master.hpp"

#define MODE_1_REG 0b01111000
#define MODE_2_REG 0b00011111

#define LOW_POWER_MODE {0b0000000, 0b0000001, 0b0000000, 0b11000000}

#define POWER_MODE LOW_POWER_MODE

typedef enum tlv493d_addr{
    TLV493D_ADDR0 = 0x1F,
    TLV493D_ADDR1 = 0x5E,
}tlv493d_addr_t;

class Tlv493d
{
public:
    Tlv493d(I2cMaster* I2c, gpio_num_t power_gpio, tlv493d_addr_t tlv493d_addr);
    void init();
    void readPositionData(int16_t *read_data);
protected:
    void startup();
private:
    I2cMaster* _I2c;
    const gpio_num_t _power_gpio;
    const tlv493d_addr_t _tlv493d_addr;
};
