/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "tlv493d_driver.h"

void app_main(void)
{
    int16_t read_data[3] = {0};

    tlv493d_init();

    while (1)
    {
        vTaskDelay((TickType_t) 200/portTICK_RATE_MS);
        tlv493d_read_axis_data(read_data, 0);
        ESP_LOGI(__func__, "Status read, x: %i, y: %i, z: %i", read_data[0], read_data[1], read_data[2]);
    }
}
