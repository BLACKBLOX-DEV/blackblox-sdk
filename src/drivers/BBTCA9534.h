#pragma once

#include <Arduino.h>
#include <Wire.h>

namespace blackblox
{

// Generic TCA9534 driver. The caller starts the shared I2C bus before begin().
// This driver keeps a shadow of the output and direction registers so changing
// one pin does not change any of the other seven pins.
class BBTCA9534
{
public:
    explicit BBTCA9534(TwoWire& wire = Wire, uint8_t address = 0x20);

    // Reads the actual chip registers; does not change its pin states.
    bool begin();
    bool isConnected();
    bool isInitialized() const;

    // INPUT / OUTPUT and LOW / HIGH are accepted as the boolean arguments.
    // Returns false for an invalid pin, failed transaction, or unsynced cache.
    bool pinMode(uint8_t pin, bool output);
    bool digitalWrite(uint8_t pin, bool high);
    bool readInputs(uint8_t& value);

private:
    bool readRegister(uint8_t reg, uint8_t& value);
    bool writeRegister(uint8_t reg, uint8_t value);

    TwoWire& _wire;
    uint8_t _address;
    uint8_t _configReg;
    uint8_t _outputReg;
    bool _initialized;
};

} // namespace blackblox
