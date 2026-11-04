#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "../../drivers/BBENS160.h"

namespace blackblox
{

struct BBAirQualityData
{
    uint8_t aqi = 0;             // UBA AQI: 1 (best) through 5 (worst)
    uint16_t tvocPpb = 0;
    uint16_t eco2Ppm = 0;        // Estimated CO2, not true measured CO2
    BBENS160Validity validity = BBENS160Validity::Invalid;
    uint32_t timestampMs = 0;
    bool hasSample = false;

    // This tests the sensor quality flag; also use isFresh() for live data.
    bool isValid() const
    {
        return hasSample && validity == BBENS160Validity::Normal;
    }
};

// High-level interface for a block containing an ENS160. The block makes no
// assumptions about indicator LEDs, buzzer pins, or other unconfirmed hardware.
class BBAirQualityBlock
{
public:
    explicit BBAirQualityBlock(
        TwoWire& wire = Wire,
        uint8_t sensorAddress = BBENS160::AutoAddress);

    // Start the shared bus first: BB.begin(sda, scl), then block.begin().
    bool begin();

    // Call about once per second. NewData updates the cached complete sample;
    // all other results leave it untouched. Read lastResult() for error detail.
    BBENS160ReadResult read();

    const BBAirQualityData& data() const { return _data; }
    BBENS160ReadResult lastResult() const { return _lastResult; }
    bool isInitialized() const { return _sensor.isInitialized(); }
    uint8_t sensorAddress() const { return _sensor.address(); }

    // Uses subtraction to work correctly even when millis() wraps.
    bool isFresh(uint32_t maxAgeMs = 4000) const;
    bool hasUsableData(uint32_t maxAgeMs = 4000) const;

    // Optional: supply external ambient data to compensate ENS160 readings.
    bool setAmbient(float temperatureC, float humidityPercent);

private:
    BBENS160 _sensor;
    BBAirQualityData _data;
    BBENS160ReadResult _lastResult;
};

} // namespace blackblox
