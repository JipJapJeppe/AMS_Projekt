#include "i2c_driver.h"

void i2c_master_init()
{
    i2c_config_t i2c_conf =
        {
            .mode = I2C_MODE_MASTER,
            .sda_io_num = SDA_GPIO_NUM,
            .sda_pullup_en = GPIO_PULLUP_ENABLE,
            .scl_io_num = SCL_GPIO_NUM,
            .scl_pullup_en = GPIO_PULLUP_ENABLE,
            .master.clk_speed = I2C_NORMAL_MODE,
        };

    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_PORT, &i2c_conf));

    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_PORT, I2C_MODE_MASTER, 0, 0, 0));
}

void i2c_write_to_register_address(uint8_t register_address, uint8_t *data_to_write, size_t data_length)
{
    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    // Send start
    ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
    // Write device address
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, (ZMOD4410_ADDR << 1), ACK_ENABLE));
    // Write register address
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, register_address, ACK_ENABLE));
    // Write data
    ESP_ERROR_CHECK(i2c_master_write(i2c_cmd, data_to_write, data_length, ACK_ENABLE));
    // Send stop
    ESP_ERROR_CHECK(i2c_master_stop(i2c_cmd));
    // Sends queued commands
    ESP_ERROR_CHECK(i2c_master_cmd_begin(I2C_MASTER_PORT, i2c_cmd, portMAX_DELAY));
    i2c_cmd_link_delete(i2c_cmd);
}

void i2c_read_from_register_address(uint8_t register_address, uint8_t *read_data)
{
    size_t buffer_size = 128;

    i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
    // Send start
    ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
    // Write device address
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, (ZMOD4410_ADDR << 1), ACK_ENABLE));
    // Write register address
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, register_address, ACK_ENABLE));
    // Extra start to read
    ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
    // Write device address
    ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, (ZMOD4410_ADDR << 1), ACK_ENABLE));
    // Read data
    ESP_ERROR_CHECK(i2c_master_read(i2c_cmd, read_data, buffer_size, ACK_ENABLE));

    // NACK skal sendes her ?? hvad er værdi for NACK?

    // Send stop
    ESP_ERROR_CHECK(i2c_master_stop(i2c_cmd));
    // Sends queued commands
    ESP_ERROR_CHECK(i2c_master_cmd_begin(I2C_MASTER_PORT, i2c_cmd, portMAX_DELAY));
    i2c_cmd_link_delete(i2c_cmd);
}
