#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace blackblox
{

class BBWSENPADS
{
public:
    explicit BBWSENPADS(
        TwoWire& wire = Wire,
        uint8_t address = 0x5D);

    bool begin();

    bool isConnected();

    bool read(
        float& pressure,
        float& temperature);

private:
    bool writeRegister(
        uint8_t reg,
        uint8_t value);

    bool readRegister(
        uint8_t reg,
        uint8_t* data,
        size_t length);

private:
    TwoWire& _wire;
    uint8_t _address;
};

} // namespace blackblox