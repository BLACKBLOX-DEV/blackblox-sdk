#include "BBRGBMatrix8x16.h"

#include "../transport/BBI2C.h"

namespace blackblox
{

static constexpr uint8_t CommandSetFrameRow = 0x02;

BBRGBMatrix8x16::BBRGBMatrix8x16(uint8_t address)
    : BBGraphics(Width, Height),
      _address(address)
{
}

bool BBRGBMatrix8x16::begin()
{
    return isValid();
}

void BBRGBMatrix8x16::drawMonoBitmap(
    uint8_t x0,
    uint8_t y0,
    const uint8_t* bitmap,
    uint8_t width,
    uint8_t height,
    BBColor color)
{
    if (bitmap == nullptr)
    {
        return;
    }

    const uint8_t bytesPerRow =
        static_cast<uint8_t>((width + 7) / 8);

    for (uint8_t y = 0; y < height; ++y)
    {
        for (uint8_t x = 0; x < width; ++x)
        {
            const uint8_t value =
                bitmap[
                    static_cast<uint16_t>(y) * bytesPerRow +
                    (x / 8)
                ];

            if ((value & (0x80 >> (x & 7))) != 0)
            {
                drawPixel(
                    static_cast<int16_t>(x0 + x),
                    static_cast<int16_t>(y0 + y),
                    color);
            }
        }
    }
}

bool BBRGBMatrix8x16::show()
{
    if (!isValid())
    {
        return false;
    }

    uint8_t payload[FrameByteCount];

    const BBColor* pixels = framebuffer();

    for (uint16_t i = 0; i < PixelCount; ++i)
    {
        const uint16_t byteIndex = i * 3;

        // Firmware matrike pričakuje vrstni red G, B, R.
        payload[byteIndex + 0] = pixels[i].g;
        payload[byteIndex + 1] = pixels[i].b;
        payload[byteIndex + 2] = pixels[i].r;
    }

    return writeCommand(
        CommandSetFrameRow,
        payload,
        FrameByteCount);
}

bool BBRGBMatrix8x16::writeCommand(
    uint8_t command,
    const uint8_t* payload,
    uint16_t length)
{
    if (length > FrameByteCount)
    {
        return false;
    }

    if (length > 0 && payload == nullptr)
    {
        return false;
    }

    uint8_t packet[3 + FrameByteCount];

    packet[0] = command;
    packet[1] = 0x00;
    packet[2] = 0x00;

    for (uint16_t i = 0; i < length; ++i)
    {
        packet[3 + i] = payload[i];
    }

    return BBI2C::write(
        _address,
        packet,
        length + 3);
}

}