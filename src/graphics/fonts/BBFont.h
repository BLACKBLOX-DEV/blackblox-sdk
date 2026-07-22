#pragma once

#include <stdint.h>

namespace blackblox
{

enum class BBFontFormat : uint8_t
{
    Columns,
    Rows
};

struct BBGlyph
{
    uint8_t width;
    const uint8_t* bitmap;
};

using BBGetGlyphFunction =
    const BBGlyph* (*)(char character);

struct BBFont
{
    uint8_t width;
    uint8_t height;
    uint8_t spacing;
    BBFontFormat format;
    BBGetGlyphFunction getGlyph;
};

}