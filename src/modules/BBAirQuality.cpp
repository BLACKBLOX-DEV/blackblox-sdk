#include "BBAirQuality.h"

namespace blackblox
{

BBAirQualityBlock::BBAirQualityBlock(TwoWire& wire, uint8_t sensorAddress)
    : _sensor(wire, sensorAddress),
      _lastResult(BBENS160ReadResult::NotInitialized)
{
}

bool BBAirQualityBlock::begin()
{
    _data = BBAirQualityData();
    _lastResult = BBENS160ReadResult::NotInitialized;
    return _sensor.begin();
}

BBENS160ReadResult BBAirQualityBlock::read()
{
    BBENS160Reading reading;
    _lastResult = _sensor.read(reading);

    if (_lastResult == BBENS160ReadResult::NewData)
    {
        _data.aqi = reading.aqi;
        _data.tvocPpb = reading.tvocPpb;
        _data.eco2Ppm = reading.eco2Ppm;
        _data.validity = reading.validity;
        _data.timestampMs = reading.timestampMs;
        _data.hasSample = true;
    }

    return _lastResult;
}

bool BBAirQualityBlock::isFresh(uint32_t maxAgeMs) const
{
    return _data.hasSample &&
           static_cast<uint32_t>(millis() - _data.timestampMs) <= maxAgeMs;
}

bool BBAirQualityBlock::hasUsableData(uint32_t maxAgeMs) const
{
    return _data.isValid() && isFresh(maxAgeMs);
}

bool BBAirQualityBlock::setAmbient(
    float temperatureC,
    float humidityPercent)
{
    return _sensor.setAmbient(temperatureC, humidityPercent);
}

} // namespace blackblox
