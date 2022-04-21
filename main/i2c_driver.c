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

    // ESP_ERROR_CHECK(i2c_set_period(I2C_MASTER_PORT, thigh, tlow));
    // ESP_ERROR_CHECK(i2c_set_start_timing(I2C_MASTER_PORT, tsusta, thdsta));
    // ESP_ERROR_CHECK(i2c_set_stop_timing(I2C_MASTER_PORT, tsusto, tbus));
    // ESP_ERROR_CHECK(i2c_set_data_timing(I2C_MASTER_PORT, tsudat, thddat));

    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_PORT, I2C_MODE_MASTER, 0, 0, 0));
}

void i2c_write_to_address(uint8_t address, uint8_t *data_to_write)
{
    i2c_cmd_handle_t i2c_handle = NULL;

    i2c_master_start(i2c_handle);
    i2c_master_write_byte(i2c_handle, ZMOD4410_ADDR, true);
    i2c_master_write_byte(i2c_handle, address, true);

    for(int i = 0; i<sizeof(data_to_write); i++)
    {
        i2c_master_write_byte(i2c_handle, data_to_write[i], true);
    }

    i2c_master_cmd_begin(I2C_MASTER_PORT, i2c_handle, portMAX_DELAY);
}

uint8_t *i2c_read_from_address(uint8_t address)
{
    // uint8_t *data_array = malloc(128);
    // memset(data_array, 0, sizeof(data_array));

    // i2c_master_write_read_device(I2C_MASTER_PORT,
    //                              ZMOD4410_ADDR,
    //                              &address,
    //                              sizeof(address),
    //                              data_array,
    //                              sizeof(data_array),
    //                              portMAX_DELAY);

    // return data_array;
    return NULL;
}
