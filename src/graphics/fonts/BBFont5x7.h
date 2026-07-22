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

    static const BBGlyph* getGlyph(char character)
    {
        static const uint8_t glyphBitmap_65[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b11111000,
            0b10001000,
            0b10001000
        };

        static const BBGlyph glyph_65 =
        {
            5,
            glyphBitmap_65
        };

        static const uint8_t glyphBitmap_66[7] =
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000
        };

        static const BBGlyph glyph_66 =
        {
            5,
            glyphBitmap_66
        };

        static const uint8_t glyphBitmap_67[7] =
        {
            0b01110000,
            0b10001000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10001000,
            0b01110000
        };

        static const BBGlyph glyph_67 =
        {
            5,
            glyphBitmap_67
        };

        switch (character)
        {
            case 'A':
                return &glyph_65;

            case 'B':
                return &glyph_66;

            case 'C':
                return &glyph_67;

            default:
                return nullptr;
        }
    }
};

}