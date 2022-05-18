#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

#include "tlv493d.hpp"
#include "i2c_master.hpp"
#include "wifi_ap.hpp"
#include "udp.hpp"
#include "gpio_num.h"

extern "C" void app_main(void)
{
    I2cMaster I2c(I2C_FAST_MODE, I2C_PORT_0, SDA_GPIO_NUM, SCL_GPIO_NUM);
    Tlv493d tlv493d(&I2c, PWR_GPIO, TLV493D_ADDR0);
    WiFiAP wifiAP;
    UDP UDPtx;

    int16_t axis_data[3] = {0};

    tlv493d.init();
    wifiAP.init();
    UDPtx.init();

    while (1)
    {
        vTaskDelay((TickType_t) 200/portTICK_RATE_MS);
        tlv493d.readPositionData(axis_data);
        ESP_LOGI(__func__, "Status read, x: %i, y: %i, z: %i", axis_data[0], axis_data[1], axis_data[2]);
    }
}
