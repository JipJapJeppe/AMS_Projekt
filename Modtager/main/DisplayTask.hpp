#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "Display.hpp"

class DisplayTask
{
public:
    DisplayTask();
    static void beginTask(void *args);
};
