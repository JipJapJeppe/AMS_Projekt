#include <stdio.h>
#include <string.h>
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
#define WIFI_CONNECT_MAXIMUM_RETRY 5

class WiFiStation
{
public:
    WiFiStation(uint8_t ssid[32], uint8_t password[64]);
    void init();
    bool getConnectionStatus();

private:
    static void eventHandler(void *arg, esp_event_base_t event_base,
                             int32_t event_id, void *event_data);
    static EventGroupHandle_t _s_wifi_event_group;
    int _s_retry_num = 0;
    uint8_t _ssid[32];
    uint8_t _password[64];
    bool _connected;
};