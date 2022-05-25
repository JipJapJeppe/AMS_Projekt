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
    int16_t new_rx_data[4] = {0};

    if (!_socket_bound)
    {
        ESP_LOGE(__func__, "Socket not bound Error");
        return;
    }

    socklen_t socklen = sizeof(_client_addr);

    int length_of_data = recvfrom(_socket, new_rx_data, 20, 0, (struct sockaddr *)&_client_addr, &socklen);

    if (length_of_data < 0)
    {
        ESP_LOGE(__func__, "Error occurred during receiving - reception error: %s", strerror(errno));
        return;
    }
    ESP_LOGD(__func__, "len: %i", length_of_data);

    int16_t checksum_diff = validateChecksum(new_rx_data);
    if (checksum_diff != 0)
    {
        ESP_LOGE(__func__, "Error occurred during receiving - checksum error, difference of: %i", checksum_diff);
        return;
    }
    rx_data[0] = new_rx_data[0];
    rx_data[1] = new_rx_data[1];
    rx_data[2] = new_rx_data[2];
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

int16_t UDPRx::validateChecksum(const int16_t *rx_data)
{
    uint16_t sum = 0;
    int16_t local_checksum = 0;
    int16_t received_checksum = rx_data[3];

    for (int i = 0; i < 3; i++)
    {
        sum += rx_data[i];
    }
    local_checksum = ~sum + 1;

    return local_checksum - received_checksum;
}
