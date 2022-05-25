#pragma once
#include "stdint.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "WiFiStation.hpp"
#include "udp_rx.hpp"
#include "esp_log.h"
#include "esp_console.h"

#include "Display.hpp"

void wireless_task(void *args);
void display_task(void *args);
