#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace blackblox
{

class BBPCA9633
{
public:
    explicit BBPCA9633(
        TwoWire& wire = Wire,
        uint8_t address = 0x01);

    bool begin();
    bool isConnected();

    bool setChannel(uint8_t channel, uint8_t brightness);

    bool setChannels(
        uint8_t channel0,
        uint8_t channel1,
        uint8_t channel2,
        uint8_t channel3);

    bool setColor(uint8_t red, uint8_t green);

    bool off();

private:
    bool writeRegister(uint8_t reg, uint8_t value);

private:
    TwoWire& _wire;
    uint8_t _address;
};

}