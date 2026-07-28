#include "BBWSENHIDS.h"

namespace blackblox
{

BBWSENHIDS::BBWSENHIDS(
    TwoWire& wire,
    uint8_t address)
    : _wire(wire),
      _address(address)
{
}

bool BBWSENHIDS::begin()
{
    return isConnected();
}

bool BBWSENHIDS::isConnected()
{
    _wire.beginTransmission(_address);
    return _wire.endTransmission() == 0;
}

bool BBWSENHIDS::read(
    float& temperature,
    float& humidity)
{
    if (!sendCommand(CommandMeasureHigh))
    {
        return false;
    }

    // Najdaljši čas meritve pri visoki natančnosti je 8,4 ms.
    delay(10);

    constexpr uint8_t DataLength = 6;

    const uint8_t received =
        _wire.requestFrom(_address, DataLength);

    if (received != DataLength)
    {
        while (_wire.available())
        {
            _wire.read();
        }

        return false;
    }

    const uint8_t temperatureMsb = _wire.read();
    const uint8_t temperatureLsb = _wire.read();
    const uint8_t temperatureCrc = _wire.read();

    const uint8_t humidityMsb = _wire.read();
    const uint8_t humidityLsb = _wire.read();
    const uint8_t humidityCrc = _wire.read();

    if (calculateCrc(
            temperatureMsb,
            temperatureLsb) != temperatureCrc)
    {
        return false;
    }

    if (calculateCrc(
            humidityMsb,
            humidityLsb) != humidityCrc)
    {
        return false;
    }

    const uint16_t rawTemperature =
        (static_cast<uint16_t>(temperatureMsb) << 8) |
        temperatureLsb;

    const uint16_t rawHumidity =
        (static_cast<uint16_t>(humidityMsb) << 8) |
        humidityLsb;

    temperature =
        -45.0f +
        175.0f *
        static_cast<float>(rawTemperature) /
        65535.0f;

    humidity =
        -6.0f +
        125.0f *
        static_cast<float>(rawHumidity) /
        65535.0f;

    if (humidity < 0.0f)
    {
        humidity = 0.0f;
    }
    else if (humidity > 100.0f)
    {
        humidity = 100.0f;
    }

    return true;
}

bool BBWSENHIDS::sendCommand(uint8_t command)
{
    _wire.beginTransmission(_address);
    _wire.write(command);

    return _wire.endTransmission() == 0;
}

uint8_t BBWSENHIDS::calculateCrc(
    uint8_t msb,
    uint8_t lsb)
{
    uint8_t crc = 0xFF;

    const uint8_t data[2] =
    {
        msb,
        lsb
    };

    for (uint8_t byteIndex = 0;
         byteIndex < 2;
         ++byteIndex)
    {
        crc ^= data[byteIndex];

        for (uint8_t bit = 0; bit < 8; ++bit)
        {
            if ((crc & 0x80) != 0)
            {
                crc =
                    static_cast<uint8_t>(
                        (crc << 1) ^ 0x31);
            }
            else
            {
                crc =
                    static_cast<uint8_t>(
                        crc << 1);
            }
        }
    }

    return crc;
}

} // namespace blackblox