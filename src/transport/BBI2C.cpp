#include "BBI2C.h"

#if defined(ARDUINO)
#include <Arduino.h>
#include <Wire.h>
#endif

bool BBI2C::begin(int sda, int scl)
{
#if defined(ARDUINO)
    Wire.setBufferSize(512);

    if (!Wire.begin(sda, scl))
    {
        return false;
    }

    Wire.setClock(400000);
#else
    (void)sda;
    (void)scl;
#endif

    return true;
}

bool BBI2C::write(
    uint8_t address,
    const uint8_t* data,
    uint16_t length)
{
#if defined(ARDUINO)
    if (data == nullptr || length == 0)
    {
        return false;
    }

    Wire.beginTransmission(address);

    for (uint16_t i = 0; i < length; i++)
    {
        Wire.write(data[i]);
    }

    return Wire.endTransmission() == 0;
#else
    (void)address;
    (void)data;
    (void)length;

    return false;
#endif
}

uint8_t BBI2C::scan()
{
#if defined(ARDUINO)
    uint8_t count = 0;

    for (uint8_t address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        const uint8_t result = Wire.endTransmission();

        if (result == 0)
        {
            Serial.print("0x");

            if (address < 0x10)
            {
                Serial.print("0");
            }

            Serial.println(address, HEX);
            count++;
        }
    }

    return count;
#else
    return 0;
#endif
}