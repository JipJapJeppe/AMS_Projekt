#include "I2cMaster.hpp"

I2cMaster::I2cMaster(i2c_speed_mode_t i2c_speed_mode, i2c_port_num_t i2c_port_num, gpio_num_t sda_gpio_num, gpio_num_t scl_gpio_num)
: _i2c_speed_mode(i2c_speed_mode), _i2c_port_num(i2c_port_num), _sda_gpio_num(sda_gpio_num), _scl_gpio_num(scl_gpio_num)
{}

void I2cMaster::init()
{
    i2c_config_t i2c_config = {};
    i2c_config.mode = I2C_MODE_MASTER;
    i2c_config.sda_io_num = _sda_gpio_num;
    i2c_config.sda_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_config.scl_io_num = _scl_gpio_num;
    i2c_config.scl_pullup_en = GPIO_PULLUP_ENABLE;
    i2c_config.master.clk_speed = _i2c_speed_mode;

    ESP_ERROR_CHECK(i2c_param_config(_i2c_port_num, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(_i2c_port_num, I2C_MODE_MASTER, 0, 0, 0));
}

void I2cMaster::writeToDeviceAddress(uint8_t dev_addr, uint8_t *data, size_t data_len)
{
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    // Send start
    ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
    // Write device address
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_WRITE, ACK_ENABLE));
    // Write data
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[0], ACK_ENABLE));
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[1], ACK_ENABLE));
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[2], ACK_ENABLE));
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[3], ACK_ENABLE));
    // Send stop
    ESP_ERROR_CHECK(i2c_master_stop(i2c_cmd));
    // Sends queued commands
    esp_err_t err = i2c_master_cmd_begin(_i2c_port_num, i2c_cmd, portMAX_DELAY);
    if(err != ESP_OK)
    {
        ESP_LOGE(__func__, "I2C device error: %s", esp_err_to_name(err));
    }
    i2c_cmd_link_delete(i2c_cmd);
}

void I2cMaster::readFromDeviceAddress(uint8_t dev_addr, uint8_t *read_data, size_t data_len)
{
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    // Send start
    ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
    // Write device address
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_READ, ACK_ENABLE));
    // Read data
    ESP_ERROR_CHECK(i2c_master_read(i2c_cmd, read_data, data_len, I2C_MASTER_ACK));
    // Send stop
    ESP_ERROR_CHECK(i2c_master_stop(i2c_cmd));
    // Sends queued commands
    esp_err_t err = i2c_master_cmd_begin(_i2c_port_num, i2c_cmd, portMAX_DELAY);
    if(err != ESP_OK)
    {
        ESP_LOGE(__func__, "I2C device error: %s", esp_err_to_name(err));
    }
    i2c_cmd_link_delete(i2c_cmd);
}

gpio_num_t I2cMaster::getSdaGpio() const
{
    return _sda_gpio_num;
}

gpio_num_t I2cMaster::getSclGpio() const
{
    return _scl_gpio_num;
}
