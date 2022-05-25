#pragma once
#include "esp_system.h"
#include "esp_log.h"
#include "esp_event.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "sys/_timeval.h"
#include "sys/errno.h"
#include <sys/param.h>
#include <string.h>
#include "freertos/queue.h"

#define PORT 4321

class UDPRx
{
public:
    UDPRx(QueueHandle_t *ip_queue);
    void init();
    void receiveData(int16_t *rx_data);
    bool getSocketStatus() const;

protected:
    void setupSourceIP(uint32_t ip_address);
    static void udpEventHandler(void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data);

private:
    int16_t validateChecksum(const int16_t *rx_data);
    const QueueHandle_t *_ip_queue;
    struct sockaddr_in _server_addr = {};
    struct sockaddr_in _client_addr = {};
    int _socket = 0;
    bool _socket_bound = false;
};
