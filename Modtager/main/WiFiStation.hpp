#pragma once
#include <stdio.h>
#include <string.h>
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
#define WIFI_CONNECT_MAXIMUM_RETRY 20

class WiFiStation
{
public:
    WiFiStation(QueueHandle_t *ip_queue, const char *ssid, const char* password);
    void init();
    bool getConnectionStatus();

private:
    static void eventHandler(void *arg, esp_event_base_t event_base,
                             int32_t event_id, void *event_data);
    const QueueHandle_t *_ip_queue;
    EventGroupHandle_t _s_wifi_event_group;
    int _s_retry_num = 0;
    const char *_ssid;
    const char *_password;
    bool _connected;
};
