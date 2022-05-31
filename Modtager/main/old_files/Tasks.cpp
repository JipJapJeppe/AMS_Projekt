// #include "Tasks.hpp"

// void wireless_task(void *args)
// {
//     QueueHandle_t data_queue = (QueueHandle_t)args;
//     QueueHandle_t ip_queue = xQueueCreate(1, sizeof(uint32_t));

//     WiFiStation WiFiSta(&ip_queue, "magnet_wifi", "12345678");
//     UDPRx UdpRx(&ip_queue);

//     int16_t axis_data[3] = {0};

//     WiFiSta.init();
//     UdpRx.init();

//     while (1)
//     {
//         if (UdpRx.getSocketStatus())
//         {
//             UdpRx.receiveData(axis_data);
//             xQueueSendToBack(data_queue, axis_data, portMAX_DELAY);
//         }
//         vTaskDelay((TickType_t)10 / portTICK_RATE_MS);
//     }
// }

// void display_task(void *args)
// {
//     QueueHandle_t data_queue = (QueueHandle_t)args;
//     Display display;

//     int16_t axis_data[3] = {0};

//     xQueueReceive(data_queue, (void *)axis_data, portMAX_DELAY);
//     display.init();

//     while (1)
//     {
//         display.plot_point(axis_data);
//         vTaskDelay((TickType_t)10 / portTICK_RATE_MS);
//         xQueueReceive(data_queue, (void *)axis_data, portMAX_DELAY);
//     }
// }
