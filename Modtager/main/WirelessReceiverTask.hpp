#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "WiFiStation.hpp"
#include "UDPRx.hpp"

class WirelessReceiverTask
{
public:
    WirelessReceiverTask();
    static void beginTask(void *args);
};
