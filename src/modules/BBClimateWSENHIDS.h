#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "../core/BBColor.h"
#include "../drivers/BBLP5569.h"
#include "../sensors/climate/BBWSENHIDS.h"

namespace blackblox
{

struct BBClimateData
{
    bool valid = false;
    float temperature = 0.0f;
    float humidity = 0.0f;
    uint32_t timestamp = 0;
};

enum class BBClimateStatus
{
    Off,
    Ok,
    Warning,
    Error,
    Measuring
};

class BBClimateWSENHIDS
{
public:
    static constexpr uint8_t LedCount = 2;

    BBClimateWSENHIDS(
        TwoWire& wire = Wire,
        uint8_t sensorAddress = 0x44,
        uint8_t ledDriverAddress = 0x40);

    bool begin(uint8_t ledCurrent = 50);

    BBClimateData read();

    bool setLed(
        uint8_t led,
        BBColor color);

    bool setLed(
        uint8_t led,
        uint8_t red,
        uint8_t green,
        uint8_t blue);

    bool ledOff(uint8_t led);
    bool ledsOff();

    bool setStatus(BBClimateStatus status);

private:
    bool validLed(uint8_t led) const;

    TwoWire& _wire;
    BBWSENHIDS _sensor;
    BBLP5569 _ledDriver;
};

} // namespace blackblox