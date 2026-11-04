#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "../drivers/BBTCA9534.h"

namespace blackblox
{

// Schematic: TCA9534 P0 -> R2 (100 ohm) -> Q1 gate; Q1 switches the
// common cathode path of 28 LEDs. All LEDs switch as one bank.
class BBLight
{
public:
    // A2/A1/A0 are each pulled high on the schematic. Grounding address
    // pins through the connector selects another address from 0x20..0x27.
    static constexpr uint8_t DefaultAddress = 0x27;

    explicit BBLight(TwoWire& wire = Wire,
                          uint8_t address = DefaultAddress);

    // Requires a previously started I2C bus. Initializes P0 LOW (off)
    // before configuring P0 as an output; other P pins retain their state.
    // A failed call may leave the physical lamp state unknown.
    bool begin();

    bool set(bool enabled);
    bool on();
    bool off();
    bool toggle();

    bool isOn() const;          // last successfully commanded state
    bool isInitialized() const;
    bool isConnected();        // I2C ACK, not a measurement of LED current

private:
    static constexpr uint8_t SwitchPin = 0;

    BBTCA9534 _expander;
    bool _initialized;
    bool _on;
};

} // namespace blackblox
