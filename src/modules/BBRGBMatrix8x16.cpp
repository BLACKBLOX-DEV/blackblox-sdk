#include "BBRGBMatrix8x16.h"
#include "../transport/BBI2C.h"

namespace blackblox
{

static constexpr uint8_t CommandSetFrameRow = 0x02;
static constexpr uint8_t CommandClear = 0x20;
static constexpr uint8_t CommandFill = 0x21;

BBRGBMatrix8x16::BBRGBMatrix8x16(uint8_t address)
    : _address(address)
{
    for (uint16_t i = 0; i < BufferSize; i++)
    {
        _buffer[i] = 0;
    }
}

bool BBRGBMatrix8x16::begin()
{
    return true;
}

void BBRGBMatrix8x16::clear()
{
    for (uint16_t i = 0; i < BufferSize; i++)
    {
        _buffer[i] = 0;
    }

    writeCommand(CommandClear, nullptr, 0);
}

void BBRGBMatrix8x16::fill(BBColor color)
{
    for (uint16_t i = 0; i < PixelCount; i++)
    {
        const uint16_t index = i * 3;

        _buffer[index + 0] = color.g;
        _buffer[index + 1] = color.b;
        _buffer[index + 2] = color.r;
    }

    const uint8_t payload[3] =
    {
        color.g,
        color.b,
        color.r
    };

    writeCommand(CommandFill, payload, sizeof(payload));
}

void BBRGBMatrix8x16::setPixel(
    uint8_t x,
    uint8_t y,
    BBColor color)
{
    if (x >= Width || y >= Height)
    {
        return;
    }

    const uint16_t index =
        (static_cast<uint16_t>(y) * Width + x) * 3;

    _buffer[index + 0] = color.g;
    _buffer[index + 1] = color.b;
    _buffer[index + 2] = color.r;
}

void BBRGBMatrix8x16::drawMonoBitmap(
    uint8_t x0,
    uint8_t y0,
    const uint8_t* bitmap,
    uint8_t width,
    uint8_t height,
    BBColor color)
{
    const uint8_t bytesPerRow = (width + 7) / 8;

    for (uint8_t y = 0; y < height; y++)
    {
        for (uint8_t x = 0; x < width; x++)
        {
            const uint8_t value =
                bitmap[y * bytesPerRow + (x / 8)];

            if (value & (0x80 >> (x & 7)))
            {
                setPixel(x0 + x, y0 + y, color);
            }
        }
    }
}

bool BBRGBMatrix8x16::show()
{
    return writeCommand(
        CommandSetFrameRow,
        _buffer,
        BufferSize
    );
}

bool BBRGBMatrix8x16::writeCommand(
    uint8_t command,
    const uint8_t* payload,
    uint16_t length)
{
    uint8_t packet[3 + BufferSize];

    packet[0] = command;
    packet[1] = 0x00;
    packet[2] = 0x00;

    for (uint16_t i = 0; i < length; i++)
    {
        packet[3 + i] = payload[i];
    }

    return BBI2C::write(
        _address,
        packet,
        length + 3
    );
}

}