#pragma once

#include <stdint.h>

namespace blackblox
{

enum class BBFontFormat : uint8_t
{
    Columns,
    Rows
};

using BBGetGlyphFunction =
    const uint8_t* (*)(char character);

struct BBFont
{
    uint8_t width;
    uint8_t height;
    uint8_t spacing;

    BBFontFormat format;

    BBGetGlyphFunction getGlyph;
};

}