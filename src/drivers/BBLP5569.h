#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace blackblox
{

class BBLP5569
{
public:
    static constexpr uint8_t DefaultAddress = 0x32;
    static constexpr uint8_t ChannelCount = 9;

    explicit BBLP5569(
        TwoWire& wire = Wire,
        uint8_t address = DefaultAddress);

    bool begin(uint8_t current = 50);
    bool isConnected();

    bool setChannel(uint8_t channel, uint8_t brightness);

    bool setRgb(
        uint8_t redChannel,
        uint8_t greenChannel,
        uint8_t blueChannel,
        uint8_t red,
        uint8_t green,
        uint8_t blue);

    bool channelOff(uint8_t channel);
    bool allOff();

private:
    static constexpr uint8_t RegisterControl = 0x00;
    static constexpr uint8_t RegisterLedControlBase = 0x07;
    static constexpr uint8_t RegisterPwmBase = 0x16;
    static constexpr uint8_t RegisterCurrentBase = 0x22;
    static constexpr uint8_t RegisterMisc = 0x2F;

    TwoWire& _wire;
    uint8_t _address;
    bool _initialized;

    bool writeRegister(uint8_t reg, uint8_t value);
};

} // namespace blackblox