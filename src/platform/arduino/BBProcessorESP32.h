#pragma once

/// Initializes the BLACKBLOX ESP32 processor module.
/// Configures board peripherals such as I2C.


namespace blackblox
{

class BBProcessorESP32
{
public:
    bool begin();
};

}