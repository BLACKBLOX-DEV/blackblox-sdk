#pragma once

#include <stdint.h>
#include "../core/BBColor.h"

namespace blackblox
{

class BBRGBMatrix8x16
{
public:
    static constexpr uint8_t Width = 16;
    static constexpr uint8_t Height = 8;
    static constexpr uint16_t PixelCount = Width * Height;
    static constexpr uint16_t BufferSize = PixelCount * 3;

    explicit BBRGBMatrix8x16(uint8_t address);

    bool begin();

    void clear();
    void fill(BBColor color);
    void setPixel(uint8_t x, uint8_t y, BBColor color);

    bool show();

private:
    uint8_t _address;
    uint8_t _buffer[BufferSize];

    bool writeCommand(
        uint8_t command,
        const uint8_t* payload,
        uint16_t length
    );
};

}