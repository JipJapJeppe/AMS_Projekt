#pragma once
#include <stdio.h>
#include "stdint.h"
#include "sdkconfig.h"
#include "string.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "nvs_flash.h"

class WiFiAP
{
public:
    WiFiAP(const char *ssid, const char *password);
    void init();

protected:
    static void wifiEventHandler(void *arg, esp_event_base_t event_base,
                             int32_t event_id, void *event_data);

private:
    const char *_ssid;
    const char *_password;
};
