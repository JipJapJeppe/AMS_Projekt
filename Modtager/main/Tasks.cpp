#include "Tasks.hpp"

void wireless_task(void *args)
{
    QueueHandle_t data_queue = (QueueHandle_t)args;
    QueueHandle_t ip_queue = xQueueCreate(1, sizeof(uint32_t));

    WiFiStation WiFiSta(&ip_queue, "magnet_wifi", "12345678");
    UDPRx UdpRx(&ip_queue);

    int16_t axis_data[3] = {0};

    WiFiSta.init();
    UdpRx.init();

    while (1)
    {
        if (UdpRx.getSocketStatus())
        {
            UdpRx.receiveData(axis_data);
            xQueueSendToBack(data_queue, axis_data, portMAX_DELAY);
        }
        vTaskDelay((TickType_t)10 / portTICK_RATE_MS);
    }
}

void display_task(void *args)
{
    QueueHandle_t data_queue = (QueueHandle_t)args;

    int16_t axis_data[3] = {0};

    while (1)
    {
        xQueueReceive(data_queue, (void *)axis_data, portMAX_DELAY);
        // ESP_LOGI(__func__, "Status read, x: %i, y: %i, z: %i", axis_data[0], axis_data[1], axis_data[2]);
        printf("\033[%d;%dH%c\n", axis_data[0], axis_data[1], 'o');
        vTaskDelay((TickType_t)10 / portTICK_RATE_MS);

        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line
    }
}
