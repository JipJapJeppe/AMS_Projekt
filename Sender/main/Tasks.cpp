#include "Tasks.hpp"

void joystick_task(void *args)
{
    I2cMaster I2c(I2C_FAST_MODE, I2C_PORT_0, SDA_GPIO_NUM, SCL_GPIO_NUM);
    Tlv493d tlv493d(&I2c, PWR_GPIO, TLV493D_ADDR0);
    int16_t axis_data[3] = {0};

    tlv493d.init();

    QueueHandle_t data_queue = (QueueHandle_t)args;

    while(1)
    {
        vTaskDelay((TickType_t) 20/portTICK_RATE_MS);
        tlv493d.readPositionData(axis_data);

        xQueueSendToBack(data_queue, axis_data, portMAX_DELAY);
    }
}

void wireless_task(void *args)
{
    WiFiAP wifiAP;
    UDP UDPtx;

    int16_t axis_data[3] = {0};

    wifiAP.init();
    UDPtx.init();

    QueueHandle_t data_queue = (QueueHandle_t)args;

    while(1)
    {
        vTaskDelay((TickType_t) 10/portTICK_RATE_MS);
        xQueueReceive(data_queue, (void *)axis_data, portMAX_DELAY);
        UDPtx.sendData(axis_data, sizeof(axis_data));
    }
}
