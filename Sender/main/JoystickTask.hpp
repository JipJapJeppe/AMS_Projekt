#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "Tlv493d.hpp"
#include "I2cMaster.hpp"

class JoystickTask
{
public:
    JoystickTask();
    static void beginTask(void *args);
};
