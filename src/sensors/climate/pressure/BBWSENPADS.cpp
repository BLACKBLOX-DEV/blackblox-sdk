#include "BBWSENPADS.h"

namespace blackblox
{

namespace
{

constexpr uint8_t RegisterDeviceId = 0x0F;
constexpr uint8_t RegisterCtrl2 = 0x11;
constexpr uint8_t RegisterDataPressureXl = 0x28;

constexpr uint8_t ExpectedDeviceId = 0xB3;

constexpr uint8_t Ctrl2OneShotMask = 0x01;

constexpr uint8_t MeasurementDataLength = 5;

constexpr uint32_t MeasurementTimeoutMs = 20;

} // namespace

BBWSENPADS::BBWSENPADS(
    TwoWire& wire,
    uint8_t address)
    : _wire(wire),
      _address(address)
{
}

bool BBWSENPADS::begin()
{
    // Boot proces lahko traja do 4,5 ms.
    delay(5);

    uint8_t deviceId = 0;

    if (!readRegister(
            RegisterDeviceId,
            &deviceId,
            1))
    {
        return false;
    }

    return deviceId == ExpectedDeviceId;
}

bool BBWSENPADS::isConnected()
{
    _wire.beginTransmission(_address);
    return _wire.endTransmission() == 0;
}

bool BBWSENPADS::read(
    float& pressure,
    float& temperature)
{
    uint8_t ctrl2 = 0;

    if (!readRegister(
            RegisterCtrl2,
            &ctrl2,
            1))
    {
        return false;
    }

    // Ohrani obstoječe nastavitve registra CTRL_2
    // in nastavi samo bit ONE_SHOT.
    ctrl2 |= Ctrl2OneShotMask;

    if (!writeRegister(
            RegisterCtrl2,
            ctrl2))
    {
        return false;
    }

    const uint32_t startTime = millis();

    while (true)
    {
        if (!readRegister(
                RegisterCtrl2,
                &ctrl2,
                1))
        {
            return false;
        }

        if ((ctrl2 & Ctrl2OneShotMask) == 0)
        {
            break;
        }

        if (millis() - startTime >=
            MeasurementTimeoutMs)
        {
            return false;
        }

        delay(1);
    }

    uint8_t data[MeasurementDataLength];

    if (!readRegister(
            RegisterDataPressureXl,
            data,
            MeasurementDataLength))
    {
        return false;
    }

    int32_t rawPressure =
        static_cast<int32_t>(
            static_cast<uint32_t>(data[0]) |
            (static_cast<uint32_t>(data[1]) << 8) |
            (static_cast<uint32_t>(data[2]) << 16));

    // Razširitev predznaka iz 24-bitnega
    // two's-complement zapisa na int32_t.
    if ((rawPressure & 0x00800000L) != 0)
    {
        rawPressure |=
            static_cast<int32_t>(0xFF000000UL);
    }

    const int16_t rawTemperature =
        static_cast<int16_t>(
            static_cast<uint16_t>(data[3]) |
            (static_cast<uint16_t>(data[4]) << 8));

    // Rezultat tlaka je v kPa.
    pressure =
        static_cast<float>(rawPressure) /
        40960.0f;

    // Rezultat temperature je v °C.
    temperature =
        static_cast<float>(rawTemperature) *
        0.01f;

    return true;
}

bool BBWSENPADS::writeRegister(
    uint8_t reg,
    uint8_t value)
{
    _wire.beginTransmission(_address);
    _wire.write(reg);
    _wire.write(value);

    return _wire.endTransmission() == 0;
}

bool BBWSENPADS::readRegister(
    uint8_t reg,
    uint8_t* data,
    size_t length)
{
    _wire.beginTransmission(_address);
    _wire.write(reg);

    if (_wire.endTransmission(false) != 0)
    {
        return false;
    }

    const uint8_t received =
        _wire.requestFrom(
            _address,
            static_cast<uint8_t>(length));

    if (received != length)
    {
        while (_wire.available())
        {
            _wire.read();
        }

        return false;
    }

    for (size_t i = 0; i < length; ++i)
    {
        data[i] = _wire.read();
    }

    return true;
}

} // namespace blackblox