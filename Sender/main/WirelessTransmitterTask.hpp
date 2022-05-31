#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "WiFiAP.hpp"
#include "UDPTx.hpp"
#include "system_parameters.h"

class WirelessTransmitterTask
{
public:
    WirelessTransmitterTask();
    static void beginTask(void *args);
};
