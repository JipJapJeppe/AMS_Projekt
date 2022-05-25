#include "udp.hpp"

UDP::UDP()
{
}

void UDP::init()
{
    int error_check = 0;

    // Create socket for IPv4 UDP communication
    _socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    if (_socket < 0)
    {
        ESP_LOGE(__func__, "Unable to create socket - error: %s", strerror(errno));
        return;
    }
    else
    {
        ESP_LOGI(__func__, "UDP socket created");
    }

    // Create a 0,5 second timeout type
    struct timeval socket_timeout = {};
    socket_timeout.tv_sec = 0;
    socket_timeout.tv_usec = 500000;

    // Set 1 second timeout on send message, to prevent delays from occuring
    error_check = setsockopt(_socket, SOL_SOCKET, SO_SNDTIMEO,
                             (const void *)&socket_timeout, sizeof(socket_timeout));

    if (error_check < 0)
    {
        ESP_LOGE(__func__, "Unable to set socket send timout option - error: %s", strerror(errno));
        return;
    }

    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_AP_STAIPASSIGNED,
                                                        udpEventHandler,
                                                        this,
                                                        NULL));
}

void UDP::sendData(const int16_t *tx_data, const size_t data_len)
{
    int16_t new_tx_data[4] = {0};
    for (int i = 0; i < 3; i++)
    {
        new_tx_data[i] = tx_data[i];
    }
    new_tx_data[3] = calculateChecksum(tx_data);

    ESP_LOGD(__func__, "Sending data, x: %i, y: %i, z: %i, checksum: %i", new_tx_data[0], new_tx_data[1], new_tx_data[2], new_tx_data[3]);
    int error_check = sendto(_socket, new_tx_data, data_len + sizeof(int16_t), 0, (struct sockaddr *)&_dest_addr, sizeof(_dest_addr));

    if (error_check < 0)
    {
        ESP_LOGE(__func__, "Error occurred during sending - error: %s", strerror(errno));
        return;
    }

    ESP_LOGD(__func__, "Message sent");
}

void UDP::receiveData(int16_t *rx_data)
{
    socklen_t socklen = sizeof(_dest_addr);

    ESP_LOGW(__func__, "Waiting for response");

    int length_of_data = recvfrom(_socket, rx_data, 3,
                                  0, (struct sockaddr *)&_dest_addr, &socklen);

    if (length_of_data < 0)
    {
        ESP_LOGE(__func__, "Error occurred during receiving - error: %s", strerror(errno));
        return;
    }
}

void UDP::setupDestinationIP(uint32_t ip_address)
{
    _dest_addr.sin_addr.s_addr = ip_address;
    _dest_addr.sin_family = AF_INET;
    _dest_addr.sin_port = htons(PORT);
    ESP_LOGI(__func__, "IP:PORT - %x:%x", _dest_addr.sin_addr.s_addr, _dest_addr.sin_port);
}

void UDP::udpEventHandler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
    UDP *self = (UDP *)arg;

    if (event_id == IP_EVENT_AP_STAIPASSIGNED)
    {
        ip_event_ap_staipassigned_t *data = (ip_event_ap_staipassigned_t *)event_data;
        self->setupDestinationIP(data->ip.addr);
    }
}

int16_t UDP::calculateChecksum(const int16_t *tx_data)
{
    uint16_t sum = 0;
    int16_t checksum = 0;

    for (int i = 0; i < 3; i++)
    {
        sum += tx_data[i];
    }
    checksum = ~sum + 1;

    return checksum;
}