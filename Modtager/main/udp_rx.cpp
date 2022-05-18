#include "udp_rx.hpp"

UDPRx::UDPRx(QueueHandle_t *ip_queue) : _ip_queue(ip_queue)
{
}

void UDPRx::init()
{
    uint32_t ip_address = 0;

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
    xQueueReceive(*_ip_queue, &ip_address, portMAX_DELAY);
    setupSourceIP(ip_address);
}

void UDPRx::receiveData(int16_t *rx_data)
{
    if (!_socket_bound)
    {
        ESP_LOGE(__func__, "Socket not bound Error");
        return;
    }

    socklen_t socklen = sizeof(_client_addr);

    int length_of_data = recvfrom(_socket, rx_data, 15,
                                  0, (struct sockaddr *)&_client_addr, &socklen);

    if (length_of_data < 0)
    {
        ESP_LOGE(__func__, "Error occurred during receiving - error: %s", strerror(errno));
        return;
    }
    ESP_LOGV(__func__, "len: %i", length_of_data);
}

bool UDPRx::getSocketStatus() const
{
    return _socket_bound;
}

void UDPRx::setupSourceIP(uint32_t ip_address)
{
    _server_addr.sin_addr.s_addr = ip_address;
    _server_addr.sin_family = AF_INET;
    _server_addr.sin_port = htons(PORT);
    ESP_LOGI(__func__, "IP:PORT - %u:%u", _server_addr.sin_addr.s_addr, _server_addr.sin_port);

    int err = bind(_socket, (struct sockaddr *)&_server_addr, sizeof(_server_addr));
    if (err < 0)
    {
        ESP_LOGE(__func__, "Socket unable to bind: errno %d", errno);
    }
    else
    {
        ESP_LOGI(__func__, "Socket bound, port %u", _server_addr.sin_port);
    }
    _socket_bound = true;
}
