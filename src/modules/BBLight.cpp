#include "BBLight.h"

namespace blackblox
{

BBLight::BBLight(TwoWire& wire, uint8_t address)
    : _expander(wire, address),
      _initialized(false),
      _on(false)
{
}

bool BBLight::begin()
{
    _initialized = false;
    _on = false;

    if (!_expander.begin())
        return false;

    // The TCA9534 output latch powers up HIGH. Load LOW before making P0
    // an output. A hardware gate pull-down is still needed for a guaranteed
    // off state while P0 is high impedance before begin() completes.
    if (!_expander.digitalWrite(SwitchPin, false))
        return false;
    if (!_expander.pinMode(SwitchPin, true))
        return false;

    _initialized = true;
    return true;
}

bool BBLight::set(bool enabled)
{
    if (!_initialized)
        return false;
    if (!_expander.digitalWrite(SwitchPin, enabled))
    {
        _initialized = false; // call begin() to resync after an I2C error
        return false;
    }

    _on = enabled;
    return true;
}

bool BBLight::on()
{
    return set(true);
}

bool BBLight::off()
{
    return set(false);
}

bool BBLight::toggle()
{
    return set(!_on);
}

bool BBLight::isOn() const
{
    return _on;
}

bool BBLight::isInitialized() const
{
    return _initialized && _expander.isInitialized();
}

bool BBLight::isConnected()
{
    return _expander.isConnected();
}

} // namespace blackblox
