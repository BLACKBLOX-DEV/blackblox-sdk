#include "BBENS160.h"

namespace blackblox
{

namespace
{
constexpr uint8_t RegisterPartId = 0x00;
constexpr uint8_t RegisterOpMode = 0x10;
constexpr uint8_t RegisterTemperatureIn = 0x13;
constexpr uint8_t RegisterHumidityIn = 0x15;
constexpr uint8_t RegisterStatus = 0x20;
constexpr uint8_t RegisterAqi = 0x21;

constexpr uint8_t StandardMode = 0x02;
constexpr uint8_t NewDataMask = 0x02;
constexpr uint8_t SensorErrorMask = 0x40;
}

BBENS160::BBENS160(TwoWire& wire, uint8_t address)
    : _wire(wire),
      _requestedAddress(address),
      _address(address),
      _initialized(false)
{
}

bool BBENS160::begin()
{
    _initialized = false;
    if (_requestedAddress != AutoAddress &&
        _requestedAddress != AddressLow &&
        _requestedAddress != AddressHigh)
    {
        return false;
    }

    const uint8_t first = _requestedAddress == AutoAddress
        ? AddressLow : _requestedAddress;
    const uint8_t last = _requestedAddress == AutoAddress
        ? AddressHigh : _requestedAddress;

    // Do not mistake another peripheral's ACK for an ENS160.
    for (uint8_t candidate = first; candidate <= last; ++candidate)
    {
        _address = candidate;
        uint8_t id[2];
        if (!readRegister(RegisterPartId, id, sizeof(id)) ||
            id[0] != 0x60 || id[1] != 0x01)
        {
            continue;
        }

        uint8_t mode = 0;
        if (!readRegister(RegisterOpMode, &mode, 1))
        {
            break;
        }
        // Rewriting STANDARD terminates and restarts the operating mode.
        // Leave it running if the MCU rebooted without cycling sensor power.
        if (mode != StandardMode &&
            !writeRegister(RegisterOpMode, &StandardMode, 1))
        {
            break;
        }

        // A new measurement takes about a second; begin() does not wait for it.
        _initialized = true;
        return true;
    }

    _address = _requestedAddress;
    return false;
}

BBENS160ReadResult BBENS160::read(BBENS160Reading& out)
{
    if (!_initialized)
    {
        return BBENS160ReadResult::NotInitialized;
    }

    uint8_t status;
    if (!readRegister(RegisterStatus, &status, 1))
    {
        return BBENS160ReadResult::BusError;
    }
    if ((status & SensorErrorMask) != 0)
    {
        return BBENS160ReadResult::SensorError;
    }
    if ((status & NewDataMask) == 0)
    {
        return BBENS160ReadResult::NoNewData;
    }

    // Auto-increment reads AQI, TVOC (little endian), eCO2 (little endian)
    // together. The NEWDAT flag clears at the first DATA register read.
    uint8_t bytes[5];
    if (!readRegister(RegisterAqi, bytes, sizeof(bytes)))
    {
        return BBENS160ReadResult::BusError;
    }

    BBENS160Reading next;
    next.aqi = bytes[0] & 0x07;
    next.tvocPpb = static_cast<uint16_t>(bytes[1]) |
        (static_cast<uint16_t>(bytes[2]) << 8);
    next.eco2Ppm = static_cast<uint16_t>(bytes[3]) |
        (static_cast<uint16_t>(bytes[4]) << 8);
    next.validity = static_cast<BBENS160Validity>((status >> 2) & 0x03);
    next.timestampMs = millis();

    // The quality flag may be Invalid during sensor conditioning; still
    // report that complete sample so the caller can show the actual state.
    if (next.validity == BBENS160Validity::Normal &&
        (next.aqi < 1 || next.aqi > 5))
    {
        return BBENS160ReadResult::SensorError;
    }
    out = next;
    return BBENS160ReadResult::NewData;
}

bool BBENS160::setAmbient(float temperatureC, float humidityPercent)
{
    if (!_initialized ||
        !(temperatureC >= -40.0f && temperatureC <= 125.0f) ||
        !(humidityPercent >= 0.0f && humidityPercent <= 100.0f))
    {
        return false;
    }

    const uint16_t rawTemperature = static_cast<uint16_t>(
        (temperatureC + 273.15f) * 64.0f + 0.5f);
    const uint16_t rawHumidity = static_cast<uint16_t>(
        humidityPercent * 512.0f + 0.5f);

    const uint8_t temperature[2] = {
        static_cast<uint8_t>(rawTemperature),
        static_cast<uint8_t>(rawTemperature >> 8)
    };
    const uint8_t humidity[2] = {
        static_cast<uint8_t>(rawHumidity),
        static_cast<uint8_t>(rawHumidity >> 8)
    };

    return writeRegister(RegisterTemperatureIn, temperature, sizeof(temperature)) &&
           writeRegister(RegisterHumidityIn, humidity, sizeof(humidity));
}

bool BBENS160::writeRegister(uint8_t reg, const uint8_t* data, uint8_t length)
{
    _wire.beginTransmission(_address);
    if (_wire.write(reg) != 1 || _wire.write(data, length) != length)
    {
        _wire.endTransmission();
        return false;
    }
    return _wire.endTransmission() == 0;
}

bool BBENS160::readRegister(uint8_t reg, uint8_t* data, uint8_t length)
{
    _wire.beginTransmission(_address);
    if (_wire.write(reg) != 1 || _wire.endTransmission(false) != 0)
    {
        return false;
    }

    if (_wire.requestFrom(_address, length) != length)
    {
        while (_wire.available()) { _wire.read(); }
        return false;
    }
    for (uint8_t i = 0; i < length; ++i)
    {
        data[i] = static_cast<uint8_t>(_wire.read());
    }
    return true;
}

} // namespace blackblox
