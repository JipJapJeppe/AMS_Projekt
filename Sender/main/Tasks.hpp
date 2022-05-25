#pragma once
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "math.h"

#include "wifi_ap.hpp"
#include "tlv493d.hpp"
#include "i2c_master.hpp"
#include "udp.hpp"
#include "gpio_num.h"

void joystick_task(void *args);
void wireless_task(void *args);
