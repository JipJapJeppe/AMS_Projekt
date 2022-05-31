#include "WirelessTransmitterTask.hpp"

WirelessTransmitterTask::WirelessTransmitterTask()
{
}

void WirelessTransmitterTask::beginTask(void *args)
{
    WiFiAP wifiAP(SYSTEM_SSID, SYSTEM_PASS);
    UDPTx UDPtx;

    int16_t axis_data[3] = {0};
    udp_status_t udp_status;

    QueueHandle_t data_queue = (QueueHandle_t)args;

    wifiAP.init();
    UDPtx.init();

    while (1)
    {
        vTaskDelay((TickType_t)1 / portTICK_RATE_MS);
        xQueueReceive(data_queue, (void *)axis_data, portMAX_DELAY);
        udp_status = UDPtx.sendData(axis_data, sizeof(axis_data));
        if (udp_status == UDP_ERROR)
        {
            continue;
        }
    }
}
