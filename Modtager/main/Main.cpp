#include "WiFiStation.hpp"
#include "udp_rx.hpp"
#include "Tasks.hpp"

extern "C" void app_main()
{
    QueueHandle_t shared_queue = xQueueCreate(5, sizeof(int16_t[3]));

    xTaskCreatePinnedToCore(display_task, "DISPLAY_TASK", 5000, shared_queue, 2, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(wireless_task, "WIRELESS_TASK", 5000, shared_queue, 2, NULL, APP_CPU_NUM);
}
