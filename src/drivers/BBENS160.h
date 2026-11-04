#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace blackblox
{

// DEVICE_STATUS bits 3:2; these states describe the sensor's own confidence.
enum class BBENS160Validity : uint8_t
{
    Normal = 0,
    WarmUp = 1,
    InitialStartUp = 2,
    Invalid = 3
};

enum class BBENS160ReadResult : uint8_t
{
    NewData,
    NoNewData,
    BusError,
    SensorError,
    NotInitialized
};

struct BBENS160Reading
{
    uint8_t aqi = 0;             // UBA AQI, 1..5 (not the US EPA AQI)
    uint16_t tvocPpb = 0;
    uint16_t eco2Ppm = 0;        // Estimated CO2, not a direct CO2 measurement
    BBENS160Validity validity = BBENS160Validity::Invalid;
    uint32_t timestampMs = 0;   // millis() when this complete sample was read

    bool isValid() const { return validity == BBENS160Validity::Normal; }
};

class BBENS160
{
public:
    static constexpr uint8_t AddressLow = 0x52;
    static constexpr uint8_t AddressHigh = 0x53;
    static constexpr uint8_t AutoAddress = 0;

    // Application initializes the shared I2C bus (e.g. BB.begin(sda, scl)).
    // AutoAddress probes both addresses AND checks the ENS160 part ID.
    explicit BBENS160(TwoWire& wire = Wire, uint8_t address = AutoAddress);

    // Starts STANDARD sensing. Does not reset the chip, preserving its
    // conditioning when the MCU alone restarts. Returns false on any I2C error.
    bool begin();

    // Poll roughly once a second. Only NewData modifies 'out'; in particular,
    // a partial/failed I2C transfer cannot publish a partially updated sample.
    BBENS160ReadResult read(BBENS160Reading& out);

    // Optional compensation from an external temperature/humidity sensor.
    // Pass Celsius and relative humidity percent; call when ambient changes.
    bool setAmbient(float temperatureC, float humidityPercent);

    bool isInitialized() const { return _initialized; }
    uint8_t address() const { return _address; } // 0 until auto-detection succeeds

private:
    bool writeRegister(uint8_t reg, const uint8_t* data, uint8_t length);
    bool readRegister(uint8_t reg, uint8_t* data, uint8_t length);

    TwoWire& _wire;
    uint8_t _requestedAddress;
    uint8_t _address;
    bool _initialized;
};

} // namespace blackblox
