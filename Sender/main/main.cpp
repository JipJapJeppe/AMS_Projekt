#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"

#include "Tlv493d.hpp"
#include "I2cMaster.hpp"
#include "WiFiAP.hpp"
#include "UDPTx.hpp"
#include "system_parameters.h"
#include "JoystickTask.hpp"
#include "WirelessTransmitterTask.hpp"

extern "C" void app_main(void)
{
    QueueHandle_t shared_queue = xQueueCreate(5, sizeof(int16_t[3]));

    JoystickTask joystickTask;
    WirelessTransmitterTask wirelessTxTask;

    xTaskCreatePinnedToCore(&joystickTask.beginTask, "JOYSTICK_TASK", 10000, (void*)shared_queue, 2, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(&wirelessTxTask.beginTask, "WIRELESS_TASK", 10000, (void*)shared_queue, 2, NULL, APP_CPU_NUM);
}
