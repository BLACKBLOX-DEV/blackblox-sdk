#include "BBClimateWSENHIDS.h"

namespace blackblox
{

BBClimateWSENHIDS::BBClimateWSENHIDS(
    TwoWire& wire,
    uint8_t sensorAddress,
    uint8_t ledDriverAddress)
    : _wire(wire),
      _sensor(wire, sensorAddress),
      _ledDriver(wire, ledDriverAddress)
{
}

bool BBClimateWSENHIDS::begin(uint8_t ledCurrent)
{
    const bool sensorOk = _sensor.begin();
    const bool ledDriverOk = _ledDriver.begin(ledCurrent);

    return sensorOk && ledDriverOk;
}

BBClimateData BBClimateWSENHIDS::read()
{
    BBClimateData data;

    data.timestamp = millis();

    data.valid =
        _sensor.read(
            data.temperature,
            data.humidity);

    return data;
}

bool BBClimateWSENHIDS::setLed(
    uint8_t led,
    BBColor color)
{
    return setLed(
        led,
        color.r,
        color.g,
        color.b);
}

bool BBClimateWSENHIDS::setLed(
    uint8_t led,
    uint8_t red,
    uint8_t green,
    uint8_t blue)
{
    if (!validLed(led))
    {
        return false;
    }

    const uint8_t firstChannel = led * 3;

    return _ledDriver.setRgb(
        firstChannel,
        firstChannel + 1,
        firstChannel + 2,
        red,
        green,
        blue);
}

bool BBClimateWSENHIDS::ledOff(uint8_t led)
{
    return setLed(
        led,
        BBColor::Off());
}

bool BBClimateWSENHIDS::ledsOff()
{
    return _ledDriver.allOff();
}

bool BBClimateWSENHIDS::setStatus(
    BBClimateStatus status)
{
    switch (status)
    {
        case BBClimateStatus::Off:
            return ledsOff();

        case BBClimateStatus::Ok:
            return
                setLed(0, BBColor::Green()) &&
                setLed(1, BBColor::Green());

        case BBClimateStatus::Warning:
            return
                setLed(0, BBColor::Yellow()) &&
                setLed(1, BBColor::Yellow());

        case BBClimateStatus::Error:
            return
                setLed(0, BBColor::Red()) &&
                setLed(1, BBColor::Red());

        case BBClimateStatus::Measuring:
            return
                setLed(0, BBColor::Blue()) &&
                setLed(1, BBColor::Blue());
    }

    return false;
}

bool BBClimateWSENHIDS::validLed(uint8_t led) const
{
    return led < LedCount;
}

} // namespace blackblox