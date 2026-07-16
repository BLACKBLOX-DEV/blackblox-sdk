#pragma once

#include <stdint.h>

#include "../graphics/BBGraphics.h"

namespace blackblox
{

class BBRGBMatrix8x16 : public BBGraphics
{
public:
    static constexpr uint8_t Width = 16;
    static constexpr uint8_t Height = 8;

    static constexpr uint16_t PixelCount =
        static_cast<uint16_t>(Width) * Height;

    static constexpr uint16_t FrameByteCount =
        PixelCount * 3;

    explicit BBRGBMatrix8x16(uint8_t address);

    bool begin();

    void drawMonoBitmap(
        uint8_t x,
        uint8_t y,
        const uint8_t* bitmap,
        uint8_t width,
        uint8_t height,
        BBColor color);

    bool show() override;

private:
    uint8_t _address;

    bool writeCommand(
        uint8_t command,
        const uint8_t* payload,
        uint16_t length);
};

}