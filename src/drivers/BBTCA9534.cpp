#include "BBTCA9534.h"

namespace blackblox
{

namespace
{
constexpr uint8_t RegInput  = 0x00;
constexpr uint8_t RegOutput = 0x01;
constexpr uint8_t RegConfig = 0x03;
}

BBTCA9534::BBTCA9534(TwoWire& wire, uint8_t address)
    : _wire(wire),
      _address(address),
      _configReg(0xFF),
      _outputReg(0xFF), // chip power-on default, NOT 0x00
      _initialized(false)
{
}

bool BBTCA9534::isConnected()
{
    if (_address < 0x20 || _address > 0x27)
        return false;

    _wire.beginTransmission(_address);
    return _wire.endTransmission() == 0;
}

bool BBTCA9534::begin()
{
    _initialized = false;
    if (!isConnected())
        return false;

    uint8_t output;
    uint8_t config;
    if (!readRegister(RegOutput, output) || !readRegister(RegConfig, config))
        return false;

    _outputReg = output;
    _configReg = config;
    _initialized = true;
    return true;
}

bool BBTCA9534::isInitialized() const
{
    return _initialized;
}

bool BBTCA9534::pinMode(uint8_t pin, bool output)
{
    if (!_initialized || pin >= 8)
        return false;

    const uint8_t bit = static_cast<uint8_t>(1u << pin);
    const uint8_t next = output
        ? static_cast<uint8_t>(_configReg & ~bit)
        : static_cast<uint8_t>(_configReg | bit);

    if (!writeRegister(RegConfig, next))
    {
        _initialized = false; // re-read registers with begin() before retry
        return false;
    }

    _configReg = next;
    return true;
}

bool BBTCA9534::digitalWrite(uint8_t pin, bool high)
{
    if (!_initialized || pin >= 8)
        return false;

    const uint8_t bit = static_cast<uint8_t>(1u << pin);
    const uint8_t next = high
        ? static_cast<uint8_t>(_outputReg | bit)
        : static_cast<uint8_t>(_outputReg & ~bit);

    if (!writeRegister(RegOutput, next))
    {
        _initialized = false;
        return false;
    }

    _outputReg = next;
    return true;
}

bool BBTCA9534::readInputs(uint8_t& value)
{
    if (!_initialized)
        return false;

    if (!readRegister(RegInput, value))
    {
        _initialized = false;
        return false;
    }

    return true;
}

bool BBTCA9534::writeRegister(uint8_t reg, uint8_t value)
{
    _wire.beginTransmission(_address);
    if (_wire.write(reg) != 1 || _wire.write(value) != 1)
    {
        _wire.endTransmission();
        return false;
    }
    return _wire.endTransmission() == 0;
}

bool BBTCA9534::readRegister(uint8_t reg, uint8_t& value)
{
    _wire.beginTransmission(_address);
    if (_wire.write(reg) != 1)
    {
        _wire.endTransmission();
        return false;
    }
    if (_wire.endTransmission(false) != 0)
        return false;
    if (_wire.requestFrom(_address, static_cast<uint8_t>(1)) != 1)
        return false;
    value = static_cast<uint8_t>(_wire.read());
    return true;
}

} // namespace blackblox
