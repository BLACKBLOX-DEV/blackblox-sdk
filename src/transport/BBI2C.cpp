#include "BBI2C.h"

#if defined(ARDUINO)
#include <Wire.h>
#endif

bool BBI2C::begin(int sda, int scl)
{
#if defined(ARDUINO)
    Wire.begin(sda, scl);
#else
    (void)sda;
    (void)scl;
#endif

    return true;
}

bool BBI2C::write(uint8_t address, const uint8_t* data, uint16_t length)
{
#if defined(ARDUINO)
    Wire.beginTransmission(address);

    for (uint16_t i = 0; i < length; i++) {
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