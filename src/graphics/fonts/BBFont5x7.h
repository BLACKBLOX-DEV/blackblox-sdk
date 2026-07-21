#pragma once

#include <stdint.h>
#include "BBFont.h"

namespace blackblox
{

class BBFont5x7
{
public:

    static const BBFont& font()
    {
        static const BBFont descriptor =
        {
            5,
            7,
            1,
            BBFontFormat::Rows,
            &BBFont5x7::getGlyph
        };

        return descriptor;
    }

    static const uint8_t* getGlyph(char character)
    {
        static const uint8_t glyph_65[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b11111000,
            0b10001000,
            0b10001000
        };

        static const uint8_t glyph_66[7] =
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000
        };

        static const uint8_t glyph_67[7] =
        {
            0b01110000,
            0b10001000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10001000,
            0b01110000
        };

        switch (character)
        {
            case 'A': return glyph_65;
            case 'B': return glyph_66;
            case 'C': return glyph_67;

            default: return nullptr;
        }
    }
};

}
