#pragma once

#include <stdint.h>
#include "BBFont.h"

namespace blackblox
{

class BBFont8x16
{
public:

    static const BBFont& font()
    {
        static const BBFont descriptor =
        {
            8,
            16,
            1,
            BBFontFormat::Rows,
            &BBFont8x16::getGlyph
        };

        return descriptor;
    }

    static const uint8_t* getGlyph(char character)
    {
        static const uint8_t glyph_50[16] =
        {
            0b00111100,
            0b01111110,
            0b11100111,
            0b11000011,
            0b00000011,
            0b00000011,
            0b00000010,
            0b00000110,
            0b00001100,
            0b00011000,
            0b00110000,
            0b01100000,
            0b11000000,
            0b11000000,
            0b11111111,
            0b11111111
        };

        static const uint8_t glyph_51[16] =
        {
            0b00111100,
            0b01111110,
            0b11100111,
            0b11000011,
            0b00000011,
            0b00000011,
            0b00000111,
            0b00111110,
            0b00111110,
            0b00000111,
            0b00000011,
            0b00000011,
            0b11000011,
            0b11100111,
            0b01111110,
            0b00111100
        };

        static const uint8_t glyph_52[16] =
        {
            0b00000011,
            0b00000110,
            0b00001100,
            0b00011000,
            0b00110000,
            0b01100000,
            0b11000000,
            0b11001100,
            0b11111111,
            0b01111111,
            0b00001100,
            0b00001100,
            0b00001100,
            0b00001100,
            0b00001100,
            0b00001100
        };

        static const uint8_t glyph_65[16] =
        {
            0b00111100,
            0b01111110,
            0b11100111,
            0b11000011,
            0b00000011,
            0b00000011,
            0b00000111,
            0b00001110,
            0b00011100,
            0b00111000,
            0b01110000,
            0b11100000,
            0b11000000,
            0b11000000,
            0b11111111,
            0b11111111
        };

        static const uint8_t glyph_66[16] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_67[16] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_97[16] =
        {
            0b11111111,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b10000001,
            0b11111111
        };

        switch (character)
        {
            case '2': return glyph_50;
            case '3': return glyph_51;
            case '4': return glyph_52;
            case 'A': return glyph_65;
            case 'B': return glyph_66;
            case 'C': return glyph_67;
            case 'a': return glyph_97;

            default: return nullptr;
        }
    }
};

}
