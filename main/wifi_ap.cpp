#include "wifi_ap.hpp"

WiFiAP::WiFiAP()
{
}

void WiFiAP::init()
{
    // Create default WiFi AP (Access Point). Registers default WiFi AP handlers.
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    // Set and init Wi-Fi to default config.
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    // Setup event handlers for WiFi and IP events.
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        wifiEventHandler,
                                                        NULL,
                                                        NULL));
    // WiFi config settings.
    wifi_config_t wifi_config = {};
    strcpy((char *)wifi_config.ap.ssid, MY_SSID);
    strcpy((char *)wifi_config.ap.password, MY_PASS);
    wifi_config.ap.max_connection = 1;
    wifi_config.ap.ssid_hidden = true;

    // Configure AP with WiFi config settings
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));

    // Start WiFi
    ESP_ERROR_CHECK(esp_wifi_start());

    printf("\n");
    ESP_LOGI(__func__, "Init Wi-Fi finished. SSID: %s password: %s\n",
             MY_SSID, MY_PASS);
}

void WiFiAP::wifiEventHandler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED)
    {
        ESP_LOGI(__func__, "Station connected to AP");
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED)
    {
        ESP_LOGW(__func__, "Station disconnected from AP");
    }
}
