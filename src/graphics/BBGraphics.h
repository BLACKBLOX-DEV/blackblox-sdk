#pragma once

#include <stdint.h>

#include "../core/BBColor.h"
#include "fonts/BBFont.h"

namespace blackblox
{

class BBGraphics
{
public:
    BBGraphics(
        uint16_t width,
        uint16_t height);

    virtual ~BBGraphics();

    BBGraphics(const BBGraphics&) = delete;
    BBGraphics& operator=(const BBGraphics&) = delete;

    uint16_t getWidth() const;
    uint16_t getHeight() const;

    bool isValid() const;

    void clear();
    void fill(BBColor color);

    void drawPixel(
        int16_t x,
        int16_t y,
        BBColor color);

    BBColor getPixel(
        int16_t x,
        int16_t y) const;

    void drawLine(
        int16_t x0,
        int16_t y0,
        int16_t x1,
        int16_t y1,
        BBColor color);

    void drawRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height,
        BBColor color);

    void fillRect(
        int16_t x,
        int16_t y,
        int16_t width,
        int16_t height,
        BBColor color);

    // ========================================================
    // Privzeti font 5 x 7
    // ========================================================

    void drawChar(
        int16_t x,
        int16_t y,
        char character,
        BBColor color);

    void drawText(
        int16_t x,
        int16_t y,
        const char* text,
        BBColor color);

    // ========================================================
    // Poljubni font
    // ========================================================

    void drawChar(
        int16_t x,
        int16_t y,
        char character,
        const BBFont& font,
        BBColor color);

    void drawText(
        int16_t x,
        int16_t y,
        const char* text,
        const BBFont& font,
        BBColor color);

    // ========================================================
    // Merjenje besedila
    // ========================================================

    uint8_t getCharacterWidth(
        char character,
        const BBFont& font) const;

    int16_t getTextWidth(
        const char* text,
        const BBFont& font) const;

    virtual bool show() = 0;

protected:
    const BBColor* framebuffer() const;
    BBColor* framebuffer();

    uint32_t pixelIndex(
        uint16_t x,
        uint16_t y) const;

private:
    uint16_t _width;
    uint16_t _height;
    BBColor* _framebuffer;
};

}