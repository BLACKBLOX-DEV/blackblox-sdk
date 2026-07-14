#ifndef BB_GRAPHICS_H
#define BB_GRAPHICS_H

#include <stdint.h>
#include "BBColor.h"

class BBGraphics
{
public:

    BBGraphics(uint16_t width, uint16_t height);

    virtual ~BBGraphics() {}

    uint16_t width() const;
    uint16_t height() const;

    virtual void drawPixel(
        int16_t x,
        int16_t y,
        BBColor color) = 0;

    void drawLine(
        int16_t x0,
        int16_t y0,
        int16_t x1,
        int16_t y1,
        BBColor color);

    void drawRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        BBColor color);

    void fillRect(
        int16_t x,
        int16_t y,
        int16_t w,
        int16_t h,
        BBColor color);

protected:

    uint16_t _width;
    uint16_t _height;
};

#endif