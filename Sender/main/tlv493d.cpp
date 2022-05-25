#include "tlv493d.hpp"

Tlv493d::Tlv493d(I2cMaster *I2c, gpio_num_t power_gpio, tlv493d_addr_t tlv493d_addr)
    : _I2c(I2c), _power_gpio(power_gpio), _tlv493d_addr(tlv493d_addr)
{
}

void Tlv493d::startup()
{
    gpio_set_direction(_power_gpio, GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)_I2c->getSdaGpio(), GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)_I2c->getSdaGpio(), 0);
    gpio_set_level(_power_gpio, 0);

    vTaskDelay((TickType_t)500 / portTICK_RATE_MS);

    // Restart
    gpio_set_level(_power_gpio, 1);
    vTaskDelay((TickType_t)500 / portTICK_RATE_MS);

    ESP_LOGI(__func__, "TLV493D startup complete");
}

void Tlv493d::init()
{
    uint8_t register_data[10] = {0};
    uint8_t write_data[3] = {0};
    uint8_t power_mode[4] = POWER_MODE;

    startup();
    _I2c->init();

    _I2c->readFromDeviceAddress(_tlv493d_addr, register_data, sizeof(register_data));

    // Write registers require specific bits from the read_registers defined in the datasheet
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("regdata: %u \n", register_data[i]);
    // }
    write_data[0] = 0b00000000;
    write_data[1] = register_data[7] & MODE_1_REG;
    write_data[2] = register_data[8];
    write_data[3] = register_data[9] & MODE_2_REG;

    for (int i = 0; i < sizeof(write_data); i++)
    {
        write_data[i] |= power_mode[i];
    }

    _I2c->writeToDeviceAddress(_tlv493d_addr, write_data, sizeof(write_data));

    ESP_LOGI(__func__, "TLV493D init complete");
}

void Tlv493d::readPositionData(int16_t *read_data)
{
    int16_t Bx = 0, By = 0, Bz = 0;
    uint8_t register_data[10] = {0};

    _I2c->readFromDeviceAddress(_tlv493d_addr, register_data, sizeof(register_data));

    Bx |= (register_data[0] << 4);
    Bx |= (register_data[4] >> 4);
    By |= (register_data[1] << 4);
    By |= (register_data[4] & 0b00001111);
    Bz |= (register_data[2] << 4);
    Bz |= (register_data[5] & 0b00001111);

    if (Bx > 2047)
    {
        Bx -= 4096;
    }
    if (By > 2047)
    {
        By -= 4096;
    }
    if (Bz > 2047)
    {
        Bz -= 4096;
    }

    read_data[0] = Bx;
    read_data[1] = By;
    read_data[2] = Bz;
}
