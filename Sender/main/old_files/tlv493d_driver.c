// #include "tlv493d_driver.h"

// // void tlv493d_send_recovery()
// // {
// //     i2c_cmd_handle_t i2c_cmd = i2c_cmd_link_create();
// //     ESP_ERROR_CHECK(i2c_master_start(i2c_cmd));
// //     ESP_ERROR_CHECK(i2c_master_write_byte(i2c_cmd, 0xFF, ACK_DISABLE));
// //     ESP_ERROR_CHECK(i2c_master_stop(i2c_cmd));
// //     esp_err_t err = i2c_master_cmd_begin(I2C_MASTER_PORT, i2c_cmd, portMAX_DELAY);
// //     if (err != ESP_OK)
// //     {
// //         ESP_LOGE(__func__, "I2C device error: %s", esp_err_to_name(err));
// //     }
// //     i2c_cmd_link_delete(i2c_cmd);
// // }

// // void tlv493d_startup()
// // {
// //     gpio_set_direction(PWR_GPIO, GPIO_MODE_OUTPUT);
// //     gpio_set_direction(SDA_GPIO_NUM, GPIO_MODE_OUTPUT);
// //     gpio_set_level(SDA_GPIO_NUM, 0);
// //     gpio_set_level(PWR_GPIO, 0);

// //     vTaskDelay((TickType_t)500 / portTICK_RATE_MS);

// //     // Restart
// //     gpio_set_level(PWR_GPIO, 1);
// //     gpio_set_level(SDA_GPIO_NUM, 0); //Address 0 (h1F)
// //     vTaskDelay((TickType_t)500 / portTICK_RATE_MS);

// //     ESP_LOGI(__func__, "Startup complete");
// // }

// // void tlv493d_init()
// // {
// //     uint8_t register_data[10] = {0};
// //     uint8_t write_data[3] = {0};

// //     tlv493d_startup();
// //     i2c_master_init(TLV493D_I2C_MODE);

// //     i2c_read_from_device_address(TLV493D_ADDR, register_data, sizeof(register_data));

// //     // Write registers require specific bits from the read_registers defined in the datasheet
// //     for(int i = 0 ; i < 10 ; i++)
// //     {
// //         printf("regdata: %u \n", register_data[i]);
// //     }
// //     write_data[0] = 0b00000000;
// //     write_data[1] = register_data[7] & MODE_1_REG;
// //     write_data[2] = register_data[8];
// //     write_data[3] = register_data[9] & MODE_2_REG;

// //     for (int i = 0; i < sizeof(write_data); i++)
// //     {
// //         write_data[i] |= mode_lowpower[i];
// //     }

// //     i2c_write_to_device_address(TLV493D_ADDR, write_data, sizeof(write_data));

// //     ESP_LOGI(__func__, "Init complete");
// // }

// void tlv493d_read_axis_data(int16_t *axis_data, size_t data_len)
// {
//     int16_t Bx = 0, By = 0, Bz = 0;
//     uint8_t register_data[10] = {0};

//     i2c_read_from_device_address(TLV493D_ADDR, register_data, sizeof(register_data));

//     Bx |= (register_data[0] << 4);
//     Bx |= (register_data[4] >> 4);
//     By |= (register_data[1] << 4);
//     By |= (register_data[4] & 0b00001111);
//     Bz |= (register_data[2] << 4);
//     Bz |= (register_data[5] & 0b00001111);

//     if(Bx >= 2048)
//     {
//         Bx -= 4096;
//     }
//     if(By >= 2048)
//     {
//         By -= 4096;
//     }
//     if(Bz >= 2048)
//     {
//         Bz -= 4096;
//     }

//     axis_data[0] = Bx;
//     axis_data[1] = By;
//     axis_data[2] = Bz;
// }
