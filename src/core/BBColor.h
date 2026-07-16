#pragma once

#include <stdint.h>

namespace blackblox
{

struct BBColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    constexpr BBColor()
    : r(0), g(0), b(0)
{
}

    constexpr BBColor(
        uint8_t red,
        uint8_t green,
        uint8_t blue)
        : r(red), g(green), b(blue)
    {
    }

    static constexpr BBColor Off()
    {
        return BBColor(0x00, 0x00, 0x00);
    }

    static constexpr BBColor Red()
    {
        return BBColor(0xFF, 0x00, 0x00);
    }

    static constexpr BBColor Green()
    {
        return BBColor(0x00, 0xFF, 0x00);
    }

    static constexpr BBColor Blue()
    {
        return BBColor(0x00, 0x00, 0xFF);
    }

    static constexpr BBColor White()
    {
        return BBColor(0xFF, 0xFF, 0xFF);
    }

    static constexpr BBColor Yellow()
    {
        return BBColor(0xFF, 0xFF, 0x00);
    }

    static constexpr BBColor Cyan()
    {
        return BBColor(0x00, 0xFF, 0xFF);
    }

    static constexpr BBColor Magenta()
    {
        return BBColor(0xFF, 0x00, 0xFF);
    }
};

}