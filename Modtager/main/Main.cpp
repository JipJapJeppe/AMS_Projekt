#include "WirelessReceiverTask.hpp"
#include "DisplayTask.hpp"

extern "C" void app_main()
{
    QueueHandle_t shared_queue = xQueueCreate(5, sizeof(int16_t[3]));

    DisplayTask displayTask;
    WirelessReceiverTask wirelessRxTask;

    xTaskCreatePinnedToCore(displayTask.beginTask, "DISPLAY_TASK", 10000, (void*)shared_queue, 2, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(wirelessRxTask.beginTask, "WIRELESS_TASK", 10000, (void*)shared_queue, 2, NULL, APP_CPU_NUM);
}
