#include "JoystickTask.hpp"

JoystickTask::JoystickTask()
{
}

void JoystickTask::beginTask(void *args)
{
    I2cMaster I2c(I2C_FAST_MODE, I2C_PORT_0, SDA_GPIO_NUM, SCL_GPIO_NUM);
    Tlv493d tlv493d(&I2c, PWR_GPIO, TLV493D_ADDR0);
    int16_t new_axis_data[3] = {0x00};
    int16_t saved_axis_data[3] = {0xFF};
    bool big_axis_change = false;

    tlv493d.init();

    QueueHandle_t data_queue = (QueueHandle_t)args;

    while (1)
    {
        vTaskDelay((TickType_t)1 / portTICK_RATE_MS);
        tlv493d.readPositionData(new_axis_data);

        for (int i = 0; i < 3; i++)
        {
            if (abs(saved_axis_data[i] - new_axis_data[i]) > 4)
            {
                saved_axis_data[i] = new_axis_data[i];
                big_axis_change = true;
            }
        }
        if (big_axis_change == false)
        {
            xQueueSendToBack(data_queue, saved_axis_data, portMAX_DELAY);
        }
        else // big_axis_change == true
        {
            big_axis_change = false;
            ESP_LOGI(__func__, "Read position data, x: %i, y: %i, z: %i", new_axis_data[0], new_axis_data[1], new_axis_data[2]);
            xQueueSendToBack(data_queue, new_axis_data, portMAX_DELAY);
        }
    }
}
