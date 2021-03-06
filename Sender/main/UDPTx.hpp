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
#include <stdint.h>

#define PORT 4321

typedef enum udp_status
{
    UDP_ERROR = 0,
    UDP_SUCCESS = 1,
} udp_status_t;

class UDPTx
{
public:
    UDPTx();
    void init();
    udp_status_t sendData(const int16_t *tx_data, const size_t data_len);

protected:
    void setupDestinationIP(uint32_t ip_address);
    static void udpEventHandler(void *arg, esp_event_base_t event_base,
                                int32_t event_id, void *event_data);

private:
    int16_t calculateChecksum(const int16_t *tx_data);
    struct sockaddr_in _dest_addr = {};
    int _socket = 0;
};
