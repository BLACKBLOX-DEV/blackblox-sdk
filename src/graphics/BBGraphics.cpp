#include "BBGraphics.h"
#include "fonts/BBFont5x7.h"
#include "fonts/BBFont8x16.h"

#include <new>

namespace blackblox
{

BBGraphics::BBGraphics(uint16_t width, uint16_t height)
    : _width(width),
      _height(height),
      _framebuffer(nullptr)
{
    const uint32_t pixelCount =
        static_cast<uint32_t>(_width) * _height;

    if (pixelCount > 0)
    {
        _framebuffer =
            new (std::nothrow) BBColor[pixelCount];
    }

    clear();
}

BBGraphics::~BBGraphics()
{
    delete[] _framebuffer;
}

uint16_t BBGraphics::getWidth() const
{
    return _width;
}

uint16_t BBGraphics::getHeight() const
{
    return _height;
}

bool BBGraphics::isValid() const
{
    return _framebuffer != nullptr;
}

void BBGraphics::clear()
{
    fill(BBColor::Off());
}

void BBGraphics::fill(BBColor color)
{
    if (_framebuffer == nullptr)
    {
        return;
    }

    const uint32_t pixelCount =
        static_cast<uint32_t>(_width) * _height;

    for (uint32_t i = 0; i < pixelCount; ++i)
    {
        _framebuffer[i] = color;
    }
}

void BBGraphics::drawPixel(
    int16_t x,
    int16_t y,
    BBColor color)
{
    if (_framebuffer == nullptr)
    {
        return;
    }

    if (x < 0 || y < 0)
    {
        return;
    }

    if (x >= static_cast<int16_t>(_width) ||
        y >= static_cast<int16_t>(_height))
    {
        return;
    }

    _framebuffer[pixelIndex(
        static_cast<uint16_t>(x),
        static_cast<uint16_t>(y))] = color;
}

BBColor BBGraphics::getPixel(
    int16_t x,
    int16_t y) const
{
    if (_framebuffer == nullptr ||
        x < 0 ||
        y < 0 ||
        x >= static_cast<int16_t>(_width) ||
        y >= static_cast<int16_t>(_height))
    {
        return BBColor::Off();
    }

    return _framebuffer[pixelIndex(
        static_cast<uint16_t>(x),
        static_cast<uint16_t>(y))];
}

void BBGraphics::drawLine(
    int16_t x0,
    int16_t y0,
    int16_t x1,
    int16_t y1,
    BBColor color)
{
    const int16_t dx =
        (x1 >= x0) ? (x1 - x0) : (x0 - x1);

    const int16_t sx =
        (x0 < x1) ? 1 : -1;

    const int16_t dy =
        (y1 >= y0) ? (y0 - y1) : (y1 - y0);

    const int16_t sy =
        (y0 < y1) ? 1 : -1;

    int16_t error = dx + dy;

    while (true)
    {
        drawPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        const int16_t error2 = 2 * error;

        if (error2 >= dy)
        {
            error += dy;
            x0 += sx;
        }

        if (error2 <= dx)
        {
            error += dx;
            y0 += sy;
        }
    }
}

void BBGraphics::drawRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    BBColor color)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    drawLine(
        x,
        y,
        x + width - 1,
        y,
        color);

    drawLine(
        x,
        y,
        x,
        y + height - 1,
        color);

    drawLine(
        x + width - 1,
        y,
        x + width - 1,
        y + height - 1,
        color);

    drawLine(
        x,
        y + height - 1,
        x + width - 1,
        y + height - 1,
        color);
}

void BBGraphics::fillRect(
    int16_t x,
    int16_t y,
    int16_t width,
    int16_t height,
    BBColor color)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    for (int16_t yy = 0; yy < height; ++yy)
    {
        drawLine(
            x,
            y + yy,
            x + width - 1,
            y + yy,
            color);
    }
}

void BBGraphics::drawChar(
    int16_t x,
    int16_t y,
    char character,
    const BBFont& font,
    BBColor color)
{
    if (font.getGlyph == nullptr)
    {
        return;
    }

    const BBGlyph* glyph =
        font.getGlyph(character);

    if (glyph == nullptr ||
        glyph->bitmap == nullptr)
    {
        return;
    }

    const uint8_t* bitmap =
        glyph->bitmap;

    const uint8_t glyphWidth =
        glyph->width;

    if (font.format == BBFontFormat::Columns)
    {
        for (uint8_t column = 0;
             column < glyphWidth;
             ++column)
        {
            const uint8_t columnData =
                bitmap[column];

            for (uint8_t row = 0;
                 row < font.height;
                 ++row)
            {
                if ((columnData & (1U << row)) != 0)
                {
                    drawPixel(
                        x + column,
                        y + row,
                        color);
                }
            }
        }
    }
    else
    {
        for (uint8_t row = 0;
             row < font.height;
             ++row)
        {
            const uint8_t rowData =
                bitmap[row];

            for (uint8_t column = 0;
                 column < glyphWidth;
                 ++column)
            {
                if ((rowData &
                    (0x80U >> column)) != 0)
                {
                    drawPixel(
                        x + column,
                        y + row,
                        color);
                }
            }
        }
    }
}

void BBGraphics::drawText(
    int16_t x,
    int16_t y,
    const char* text,
    const BBFont& font,
    BBColor color)
{
    if (text == nullptr)
    {
        return;
    }

    const int16_t startX = x;
    int16_t cursorX = x;
    int16_t cursorY = y;

    while (*text != '\0')
    {
        if (*text == '\n')
        {
            cursorX = startX;
            cursorY += font.height + 1;
            ++text;
            continue;
        }

        if (*text == '\r')
        {
            cursorX = startX;
            ++text;
            continue;
        }

        const BBGlyph* glyph = nullptr;

        if (font.getGlyph != nullptr)
        {
            glyph =
                font.getGlyph(*text);
        }

        drawChar(
            cursorX,
            cursorY,
            *text,
            font,
            color);

        if (glyph != nullptr)
        {
            cursorX +=
                glyph->width + font.spacing;
        }
        else
        {
            cursorX +=
                font.width + font.spacing;
        }

        ++text;
    }
}

void BBGraphics::drawChar(
    int16_t x,
    int16_t y,
    char character,
    BBColor color)
{
    drawChar(
        x,
        y,
        character,
        BBFont5x7::font(),
        color);
}

void BBGraphics::drawText(
    int16_t x,
    int16_t y,
    const char* text,
    BBColor color)
{
    drawText(
        x,
        y,
        text,
        BBFont5x7::font(),
        color);
}

const BBColor* BBGraphics::framebuffer() const
{
    return _framebuffer;
}

BBColor* BBGraphics::framebuffer()
{
    return _framebuffer;
}

uint32_t BBGraphics::pixelIndex(
    uint16_t x,
    uint16_t y) const
{
    return static_cast<uint32_t>(y) * _width + x;
}

}