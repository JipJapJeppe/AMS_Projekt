#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"

#include "tlv493d.hpp"
#include "i2c_master.hpp"
#include "wifi_ap.hpp"
#include "udp.hpp"
#include "gpio_num.h"
#include "Tasks.hpp"

extern "C" void app_main(void)
{
    QueueHandle_t shared_queue = xQueueCreate(5, sizeof(int16_t[3]));

    xTaskCreatePinnedToCore(joystick_task, "JOYSTICK_TASK", 5000, shared_queue, 2, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(wireless_task, "WIRELESS_TASK", 5000, shared_queue, 2, NULL, APP_CPU_NUM);
}
