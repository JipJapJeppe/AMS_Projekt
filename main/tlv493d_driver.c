#include "tlv493d_driver.h"

void tlv493d_startup()
{
    gpio_set_direction(PWR_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(PWR_GPIO, 0);

    vTaskDelay((TickType_t) 500/portTICK_RATE_MS);

    gpio_set_level(PWR_GPIO, 1);  // address = 0x1F
    gpio_set_level(SDA_GPIO_NUM, 0);

    vTaskDelay((TickType_t) 500/portTICK_RATE_MS);

    ESP_LOGI(__func__, "Startup complete");
}

void tlv493d_init()
{
    uint8_t register_data[10];
    uint8_t write_data[3];

    i2c_master_init(I2C_FAST_MODE);
    tlv493d_startup();

    i2c_read_from_device_address(TLV493D_ADDR0, &register_data, sizeof(register_data));

    // Write registers require specific bits from the read_registers defined in the datasheet
    write_data[0] = 0b00000000;
    write_data[1] = register_data[7] & 0b01111000;
    write_data[2] = register_data[8];
    write_data[3] = register_data[9] & 0b00011111;

    i2c_write_to_device_address(TLV493D_ADDR0, &write_data, sizeof(write_data));

    ESP_LOGI(__func__, "Init complete");
}

void tlv493d_read_axis_data(uint8_t *axis_data, size_t data_len)
{
    uint8_t Bx = 0, By = 0, Bz = 0;
    uint8_t register_data[7];

    i2c_read_from_device_address(TLV493D_ADDR0, &register_data, sizeof(register_data));

    Bx = register_data[0];
    By = register_data[1];
    Bz = register_data[2];

    axis_data[0] = Bx;
    axis_data[1] = By;
    axis_data[2] = Bz;
}

void tlv493d_read_temp_data(uint8_t *read_data, size_t data_len)
{

}

void tlv493d_full_reset()
{
    // Send address 0x00 to all slaves
    i2c_master_write_to_device(I2C_MASTER_PORT, 0x00, NULL, 0, 0);
}
