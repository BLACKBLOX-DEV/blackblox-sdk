#pragma once

#include <stdint.h>

class BBI2C
{
public:
    static bool begin(int sda, int scl);

    static bool write(
        uint8_t address,
        const uint8_t* data,
        uint16_t length
    );

    static uint8_t scan();
};