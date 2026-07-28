#include "BBPCA9633.h"

namespace blackblox
{

namespace
{
constexpr uint8_t REG_MODE1  = 0x00;
constexpr uint8_t REG_MODE2  = 0x01;
constexpr uint8_t REG_PWM0   = 0x02;
constexpr uint8_t REG_LEDOUT = 0x08;
}

BBPCA9633::BBPCA9633(
    TwoWire& wire,
    uint8_t address)
    : _wire(wire),
      _address(address)
{
}

bool BBPCA9633::isConnected()
{
    _wire.beginTransmission(_address);
    return _wire.endTransmission() == 0;
}

bool BBPCA9633::begin()
{
    if (!isConnected())
        return false;

    // Normal operating mode.
    if (!writeRegister(REG_MODE1, 0x00))
        return false;

    // Outputs change after STOP; totem-pole output mode.
    if (!writeRegister(REG_MODE2, 0x04))
        return false;

    // All four outputs controlled by their individual PWM registers.
    if (!writeRegister(REG_LEDOUT, 0xAA))
        return false;

    return off();
}

bool BBPCA9633::setColor(
    uint8_t red,
    uint8_t green)
{
    return setChannels(
        green,
        red,
        0,
        0);
}

bool BBPCA9633::setChannel(
    uint8_t channel,
    uint8_t brightness)
{
    if (channel > 3)
        return false;

    return writeRegister(
        static_cast<uint8_t>(REG_PWM0 + channel),
        brightness);
}

bool BBPCA9633::setChannels(
    uint8_t channel0,
    uint8_t channel1,
    uint8_t channel2,
    uint8_t channel3)
{
    return
        setChannel(0, channel0) &&
        setChannel(1, channel1) &&
        setChannel(2, channel2) &&
        setChannel(3, channel3);
}

bool BBPCA9633::off()
{
    return setChannels(0, 0, 0, 0);
}

bool BBPCA9633::writeRegister(
    uint8_t reg,
    uint8_t value)
{
    _wire.beginTransmission(_address);
    _wire.write(reg);
    _wire.write(value);

    return _wire.endTransmission() == 0;
}

}