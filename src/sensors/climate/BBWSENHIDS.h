#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace blackblox
{

class BBWSENHIDS
{
public:
    static constexpr uint8_t DefaultAddress = 0x44;

    explicit BBWSENHIDS(
        TwoWire& wire = Wire,
        uint8_t address = DefaultAddress);

    bool begin();
    bool isConnected();

    bool read(
        float& temperature,
        float& humidity);

private:
    static constexpr uint8_t CommandMeasureHigh = 0xFD;

    TwoWire& _wire;
    uint8_t _address;

    bool sendCommand(uint8_t command);

    static uint8_t calculateCrc(
        uint8_t msb,
        uint8_t lsb);
};

} // namespace blackblox