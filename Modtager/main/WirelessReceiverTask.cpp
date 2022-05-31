#include "WirelessReceiverTask.hpp"

WirelessReceiverTask::WirelessReceiverTask()
{
}

void WirelessReceiverTask::beginTask(void *args)
{
    WirelessReceiverTask *self = (WirelessReceiverTask *)args;
    QueueHandle_t data_queue = (QueueHandle_t)args;
    QueueHandle_t ip_queue = xQueueCreate(1, sizeof(uint32_t));

    WiFiStation WiFiSta(&ip_queue, "magnet_wifi", "12345678");
    UDPRx UdpRx(&ip_queue);

    int16_t axis_data[3] = {0};
    udp_status_t udp_status;

    WiFiSta.init();
    UdpRx.init();

    while (1)
    {
        vTaskDelay((TickType_t)1 / portTICK_RATE_MS);

        udp_status = UdpRx.receiveData(axis_data);
        if (udp_status == UDP_ERROR)
        {
            continue;
        }
        xQueueSendToBack(data_queue, axis_data, portMAX_DELAY);
    }
}
