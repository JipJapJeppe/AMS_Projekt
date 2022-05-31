#include "DisplayTask.hpp"

DisplayTask::DisplayTask()
{
}

void DisplayTask::beginTask(void *args)
{
    DisplayTask *self = (DisplayTask *)args;
    QueueHandle_t data_queue = (QueueHandle_t)args;
    Display display;

    int16_t axis_data[3] = {0};

    xQueueReceive(data_queue, (void *)axis_data, portMAX_DELAY);
    display.init();

    while (1)
    {
        display.plot_point(axis_data);
        vTaskDelay((TickType_t)10 / portTICK_RATE_MS);
        xQueueReceive(data_queue, (void *)axis_data, portMAX_DELAY);
    }
}
