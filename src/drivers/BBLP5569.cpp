#include "BBLP5569.h"

namespace blackblox
{

BBLP5569::BBLP5569(TwoWire& wire, uint8_t address)
    : _wire(wire),
      _address(address),
      _initialized(false)
{
}

bool BBLP5569::isConnected()
{
    _wire.beginTransmission(_address);
    return _wire.endTransmission() == 0;
}

bool BBLP5569::begin(uint8_t current)
{
    _initialized = false;

    if (!isConnected())
    {
        return false;
    }

    // CHIP_EN = 1
    if (!writeRegister(RegisterControl, 0x40))
    {
        return false;
    }

    delay(1);

    // Charge pump AUTO
    if (!writeRegister(RegisterMisc, 0x18))
    {
        return false;
    }

    delay(10);

    for (uint8_t channel = 0; channel < ChannelCount; ++channel)
    {
        if (!writeRegister(
                RegisterLedControlBase + channel,
                0x00))
        {
            return false;
        }

        if (!writeRegister(
                RegisterCurrentBase + channel,
                current))
        {
            return false;
        }

        if (!writeRegister(
                RegisterPwmBase + channel,
                0x00))
        {
            return false;
        }
    }

    _initialized = true;
    return true;
}

bool BBLP5569::setChannel(
    uint8_t channel,
    uint8_t brightness)
{
    if (!_initialized || channel >= ChannelCount)
    {
        return false;
    }

    return writeRegister(
        RegisterPwmBase + channel,
        brightness);
}

bool BBLP5569::setRgb(
    uint8_t redChannel,
    uint8_t greenChannel,
    uint8_t blueChannel,
    uint8_t red,
    uint8_t green,
    uint8_t blue)
{
    if (!_initialized)
    {
        return false;
    }

    if (redChannel >= ChannelCount ||
        greenChannel >= ChannelCount ||
        blueChannel >= ChannelCount)
    {
        return false;
    }

    bool result = true;

    result &= setChannel(redChannel, red);
    result &= setChannel(greenChannel, green);
    result &= setChannel(blueChannel, blue);

    return result;
}

bool BBLP5569::channelOff(uint8_t channel)
{
    return setChannel(channel, 0);
}

bool BBLP5569::allOff()
{
    if (!_initialized)
    {
        return false;
    }

    bool result = true;

    for (uint8_t channel = 0;
         channel < ChannelCount;
         ++channel)
    {
        result &= setChannel(channel, 0);
    }

    return result;
}

bool BBLP5569::writeRegister(
    uint8_t reg,
    uint8_t value)
{
    _wire.beginTransmission(_address);
    _wire.write(reg);
    _wire.write(value);

    return _wire.endTransmission() == 0;
}

} // namespace blackblox