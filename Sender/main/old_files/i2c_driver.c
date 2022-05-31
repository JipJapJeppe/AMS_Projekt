#include "i2c_driver.h"

// void i2c_master_init(i2c_speed_mode_t i2c_speed_mode, i2c_port_num_t i2c_port_num, uint8_t sda_gpio_num, uint8_t scl_gpio_num)
// {
//     i2c_config_t i2c_conf =
//         {
//             .mode = I2C_MODE_MASTER,
//             .sda_io_num = sda_gpio_num,
//             .sda_pullup_en = GPIO_PULLUP_ENABLE,
//             .scl_io_num = scl_gpio_num,
//             .scl_pullup_en = GPIO_PULLUP_ENABLE,
//             .master.clk_speed = i2c_speed_mode,
//         };

//     ESP_ERROR_CHECK(i2c_param_config(i2c_port_num, &i2c_conf));
// }

// void i2c_write_to_device_address(uint8_t dev_addr, uint8_t *data, size_t data_len)
// {
//     i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
//     // Send start
//     ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
//     // Write device address
//     ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_WRITE, ACK_ENABLE));
//     // Write data
//     ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[0], ACK_ENABLE));
//     ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[1], ACK_ENABLE));
//     ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[2], ACK_ENABLE));
//     ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, data[3], ACK_ENABLE));
//     // Send stop
//     ESP_ERROR_CHECK(i2c_master_stop(i2c_cmd));
//     // Sends queued commands
//     esp_err_t err = i2c_master_cmd_begin(I2C_MASTER_PORT, i2c_cmd, portMAX_DELAY);
//     if(err != ESP_OK)
//     {
//         ESP_LOGE(__func__, "I2C device error: %s", esp_err_to_name(err));
//     }
//     i2c_cmd_link_delete(i2c_cmd);
// }

// void i2c_read_from_device_address(uint8_t dev_addr, uint8_t *read_data, size_t data_len)
// {
//     i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
//     // Send start
//     ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
//     // Write device address
//     ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, (dev_addr << 1) | I2C_MASTER_READ, ACK_ENABLE));
//     // Read data
//     ESP_ERROR_CHECK(i2c_master_read(i2c_cmd, read_data, data_len, I2C_MASTER_ACK));
//     // Send stop
//     ESP_ERROR_CHECK(i2c_master_stop(i2c_cmd));
//     // Sends queued commands
//     esp_err_t err = i2c_master_cmd_begin(I2C_MASTER_PORT, i2c_cmd, portMAX_DELAY);
//     if(err != ESP_OK)
//     {
//         ESP_LOGE(__func__, "I2C device error: %s", esp_err_to_name(err));
//     }
//     i2c_cmd_link_delete(i2c_cmd);
// }
