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

    static const BBGlyph* getGlyph(char character)
    {
        static const uint8_t glyphBitmap_32[16] =
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

        static const BBGlyph glyph_32 =
        {
            8,
            glyphBitmap_32
        };

        static const uint8_t glyphBitmap_33[16] =
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

        static const BBGlyph glyph_33 =
        {
            8,
            glyphBitmap_33
        };

        static const uint8_t glyphBitmap_34[16] =
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

        static const BBGlyph glyph_34 =
        {
            8,
            glyphBitmap_34
        };

        static const uint8_t glyphBitmap_35[16] =
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

        static const BBGlyph glyph_35 =
        {
            8,
            glyphBitmap_35
        };

        static const uint8_t glyphBitmap_36[16] =
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

        static const BBGlyph glyph_36 =
        {
            8,
            glyphBitmap_36
        };

        static const uint8_t glyphBitmap_37[16] =
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

        static const BBGlyph glyph_37 =
        {
            8,
            glyphBitmap_37
        };

        static const uint8_t glyphBitmap_38[16] =
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

        static const BBGlyph glyph_38 =
        {
            8,
            glyphBitmap_38
        };

        static const uint8_t glyphBitmap_39[16] =
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

        static const BBGlyph glyph_39 =
        {
            8,
            glyphBitmap_39
        };

        static const uint8_t glyphBitmap_40[16] =
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

        static const BBGlyph glyph_40 =
        {
            8,
            glyphBitmap_40
        };

        static const uint8_t glyphBitmap_41[16] =
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

        static const BBGlyph glyph_41 =
        {
            8,
            glyphBitmap_41
        };

        static const uint8_t glyphBitmap_42[16] =
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

        static const BBGlyph glyph_42 =
        {
            8,
            glyphBitmap_42
        };

        static const uint8_t glyphBitmap_43[16] =
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

        static const BBGlyph glyph_43 =
        {
            8,
            glyphBitmap_43
        };

        static const uint8_t glyphBitmap_44[16] =
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

        static const BBGlyph glyph_44 =
        {
            8,
            glyphBitmap_44
        };

        static const uint8_t glyphBitmap_45[16] =
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

        static const BBGlyph glyph_45 =
        {
            8,
            glyphBitmap_45
        };

        static const uint8_t glyphBitmap_46[16] =
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

        static const BBGlyph glyph_46 =
        {
            8,
            glyphBitmap_46
        };

        static const uint8_t glyphBitmap_47[16] =
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

        static const BBGlyph glyph_47 =
        {
            8,
            glyphBitmap_47
        };

        static const uint8_t glyphBitmap_48[16] =
        {
            0b00111100,
            0b01111110,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000111,
            0b11001111,
            0b11011011,
            0b11110011,
            0b11100011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b01111110,
            0b00111100
        };

        static const BBGlyph glyph_48 =
        {
            8,
            glyphBitmap_48
        };

        static const uint8_t glyphBitmap_49[16] =
        {
            0b00110000,
            0b01110000,
            0b11110000,
            0b10110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b00110000,
            0b11111100,
            0b11111100
        };

        static const BBGlyph glyph_49 =
        {
            8,
            glyphBitmap_49
        };

        static const uint8_t glyphBitmap_50[16] =
        {
            0b00111100,
            0b01111110,
            0b11000011,
            0b11000011,
            0b00000011,
            0b00000011,
            0b00000110,
            0b00001100,
            0b00011000,
            0b00110000,
            0b01100000,
            0b11000000,
            0b11000000,
            0b11000000,
            0b11111111,
            0b11111111
        };

        static const BBGlyph glyph_50 =
        {
            8,
            glyphBitmap_50
        };

        static const uint8_t glyphBitmap_51[16] =
        {
            0b00111100,
            0b01111110,
            0b11000011,
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
            0b11000011,
            0b00111110,
            0b00111100
        };

        static const BBGlyph glyph_51 =
        {
            8,
            glyphBitmap_51
        };

        static const uint8_t glyphBitmap_52[16] =
        {
            0b00000011,
            0b00000110,
            0b00001100,
            0b00011000,
            0b00110000,
            0b01100000,
            0b11000000,
            0b11000000,
            0b11000110,
            0b11111111,
            0b11111111,
            0b00000110,
            0b00000110,
            0b00000110,
            0b00000110,
            0b00000110
        };

        static const BBGlyph glyph_52 =
        {
            8,
            glyphBitmap_52
        };

        static const uint8_t glyphBitmap_53[16] =
        {
            0b11111111,
            0b11111111,
            0b11000000,
            0b11000000,
            0b11000000,
            0b11000000,
            0b11111100,
            0b11111110,
            0b00000111,
            0b00000011,
            0b00000011,
            0b00000011,
            0b11000011,
            0b11000011,
            0b01111110,
            0b00111100
        };

        static const BBGlyph glyph_53 =
        {
            8,
            glyphBitmap_53
        };

        static const uint8_t glyphBitmap_54[16] =
        {
            0b00111100,
            0b01111110,
            0b11000011,
            0b11000000,
            0b11000000,
            0b11000000,
            0b11000000,
            0b11111100,
            0b11111110,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b01111110,
            0b00111100
        };

        static const BBGlyph glyph_54 =
        {
            8,
            glyphBitmap_54
        };

        static const uint8_t glyphBitmap_55[16] =
        {
            0b11111111,
            0b11111111,
            0b00000011,
            0b00000011,
            0b00000011,
            0b00000011,
            0b00000110,
            0b00001100,
            0b00011000,
            0b00110000,
            0b01100000,
            0b11000000,
            0b11000000,
            0b11000000,
            0b11000000,
            0b11000000
        };

        static const BBGlyph glyph_55 =
        {
            8,
            glyphBitmap_55
        };

        static const uint8_t glyphBitmap_56[16] =
        {
            0b00111100,
            0b01111110,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b01111110,
            0b01111110,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b01111110,
            0b00111100
        };

        static const BBGlyph glyph_56 =
        {
            8,
            glyphBitmap_56
        };

        static const uint8_t glyphBitmap_57[16] =
        {
            0b00111100,
            0b01111110,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b11000011,
            0b01111111,
            0b00111111,
            0b00000011,
            0b00000011,
            0b00000011,
            0b00000011,
            0b11000011,
            0b01111110,
            0b00111100
        };

        static const BBGlyph glyph_57 =
        {
            8,
            glyphBitmap_57
        };

        static const uint8_t glyphBitmap_58[16] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00111000,
            0b00111000,
            0b00111000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00111000,
            0b00111000,
            0b00111000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_58 =
        {
            8,
            glyphBitmap_58
        };

        static const uint8_t glyphBitmap_59[16] =
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

        static const BBGlyph glyph_59 =
        {
            8,
            glyphBitmap_59
        };

        static const uint8_t glyphBitmap_60[16] =
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

        static const BBGlyph glyph_60 =
        {
            8,
            glyphBitmap_60
        };

        static const uint8_t glyphBitmap_61[16] =
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

        static const BBGlyph glyph_61 =
        {
            8,
            glyphBitmap_61
        };

        static const uint8_t glyphBitmap_62[16] =
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

        static const BBGlyph glyph_62 =
        {
            8,
            glyphBitmap_62
        };

        static const uint8_t glyphBitmap_63[16] =
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

        static const BBGlyph glyph_63 =
        {
            8,
            glyphBitmap_63
        };

        static const uint8_t glyphBitmap_64[16] =
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

        static const BBGlyph glyph_64 =
        {
            8,
            glyphBitmap_64
        };

        static const uint8_t glyphBitmap_65[16] =
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

        static const BBGlyph glyph_65 =
        {
            8,
            glyphBitmap_65
        };

        static const uint8_t glyphBitmap_66[16] =
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

        static const BBGlyph glyph_66 =
        {
            8,
            glyphBitmap_66
        };

        static const uint8_t glyphBitmap_67[16] =
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

        static const BBGlyph glyph_67 =
        {
            8,
            glyphBitmap_67
        };

        static const uint8_t glyphBitmap_68[16] =
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

        static const BBGlyph glyph_68 =
        {
            8,
            glyphBitmap_68
        };

        static const uint8_t glyphBitmap_69[16] =
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

        static const BBGlyph glyph_69 =
        {
            8,
            glyphBitmap_69
        };

        static const uint8_t glyphBitmap_70[16] =
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

        static const BBGlyph glyph_70 =
        {
            8,
            glyphBitmap_70
        };

        static const uint8_t glyphBitmap_71[16] =
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

        static const BBGlyph glyph_71 =
        {
            8,
            glyphBitmap_71
        };

        static const uint8_t glyphBitmap_72[16] =
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

        static const BBGlyph glyph_72 =
        {
            8,
            glyphBitmap_72
        };

        static const uint8_t glyphBitmap_73[16] =
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

        static const BBGlyph glyph_73 =
        {
            8,
            glyphBitmap_73
        };

        static const uint8_t glyphBitmap_74[16] =
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

        static const BBGlyph glyph_74 =
        {
            8,
            glyphBitmap_74
        };

        static const uint8_t glyphBitmap_75[16] =
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

        static const BBGlyph glyph_75 =
        {
            8,
            glyphBitmap_75
        };

        static const uint8_t glyphBitmap_76[16] =
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

        static const BBGlyph glyph_76 =
        {
            8,
            glyphBitmap_76
        };

        static const uint8_t glyphBitmap_77[16] =
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

        static const BBGlyph glyph_77 =
        {
            8,
            glyphBitmap_77
        };

        static const uint8_t glyphBitmap_78[16] =
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

        static const BBGlyph glyph_78 =
        {
            8,
            glyphBitmap_78
        };

        static const uint8_t glyphBitmap_79[16] =
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

        static const BBGlyph glyph_79 =
        {
            8,
            glyphBitmap_79
        };

        static const uint8_t glyphBitmap_80[16] =
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

        static const BBGlyph glyph_80 =
        {
            8,
            glyphBitmap_80
        };

        static const uint8_t glyphBitmap_81[16] =
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

        static const BBGlyph glyph_81 =
        {
            8,
            glyphBitmap_81
        };

        static const uint8_t glyphBitmap_82[16] =
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

        static const BBGlyph glyph_82 =
        {
            8,
            glyphBitmap_82
        };

        static const uint8_t glyphBitmap_83[16] =
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

        static const BBGlyph glyph_83 =
        {
            8,
            glyphBitmap_83
        };

        static const uint8_t glyphBitmap_84[16] =
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

        static const BBGlyph glyph_84 =
        {
            8,
            glyphBitmap_84
        };

        static const uint8_t glyphBitmap_85[16] =
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

        static const BBGlyph glyph_85 =
        {
            8,
            glyphBitmap_85
        };

        static const uint8_t glyphBitmap_86[16] =
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

        static const BBGlyph glyph_86 =
        {
            8,
            glyphBitmap_86
        };

        static const uint8_t glyphBitmap_87[16] =
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

        static const BBGlyph glyph_87 =
        {
            8,
            glyphBitmap_87
        };

        static const uint8_t glyphBitmap_88[16] =
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

        static const BBGlyph glyph_88 =
        {
            8,
            glyphBitmap_88
        };

        static const uint8_t glyphBitmap_89[16] =
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

        static const BBGlyph glyph_89 =
        {
            8,
            glyphBitmap_89
        };

        static const uint8_t glyphBitmap_90[16] =
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

        static const BBGlyph glyph_90 =
        {
            8,
            glyphBitmap_90
        };

        static const uint8_t glyphBitmap_91[16] =
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

        static const BBGlyph glyph_91 =
        {
            8,
            glyphBitmap_91
        };

        static const uint8_t glyphBitmap_92[16] =
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

        static const BBGlyph glyph_92 =
        {
            8,
            glyphBitmap_92
        };

        static const uint8_t glyphBitmap_93[16] =
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

        static const BBGlyph glyph_93 =
        {
            8,
            glyphBitmap_93
        };

        static const uint8_t glyphBitmap_94[16] =
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

        static const BBGlyph glyph_94 =
        {
            8,
            glyphBitmap_94
        };

        static const uint8_t glyphBitmap_95[16] =
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

        static const BBGlyph glyph_95 =
        {
            8,
            glyphBitmap_95
        };

        static const uint8_t glyphBitmap_96[16] =
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

        static const BBGlyph glyph_96 =
        {
            8,
            glyphBitmap_96
        };

        static const uint8_t glyphBitmap_97[16] =
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

        static const BBGlyph glyph_97 =
        {
            8,
            glyphBitmap_97
        };

        static const uint8_t glyphBitmap_98[16] =
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

        static const BBGlyph glyph_98 =
        {
            8,
            glyphBitmap_98
        };

        static const uint8_t glyphBitmap_99[16] =
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

        static const BBGlyph glyph_99 =
        {
            8,
            glyphBitmap_99
        };

        static const uint8_t glyphBitmap_100[16] =
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

        static const BBGlyph glyph_100 =
        {
            8,
            glyphBitmap_100
        };

        static const uint8_t glyphBitmap_101[16] =
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

        static const BBGlyph glyph_101 =
        {
            8,
            glyphBitmap_101
        };

        static const uint8_t glyphBitmap_102[16] =
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

        static const BBGlyph glyph_102 =
        {
            8,
            glyphBitmap_102
        };

        static const uint8_t glyphBitmap_103[16] =
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

        static const BBGlyph glyph_103 =
        {
            8,
            glyphBitmap_103
        };

        static const uint8_t glyphBitmap_104[16] =
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

        static const BBGlyph glyph_104 =
        {
            8,
            glyphBitmap_104
        };

        static const uint8_t glyphBitmap_105[16] =
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

        static const BBGlyph glyph_105 =
        {
            8,
            glyphBitmap_105
        };

        static const uint8_t glyphBitmap_106[16] =
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

        static const BBGlyph glyph_106 =
        {
            8,
            glyphBitmap_106
        };

        static const uint8_t glyphBitmap_107[16] =
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

        static const BBGlyph glyph_107 =
        {
            8,
            glyphBitmap_107
        };

        static const uint8_t glyphBitmap_108[16] =
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

        static const BBGlyph glyph_108 =
        {
            8,
            glyphBitmap_108
        };

        static const uint8_t glyphBitmap_109[16] =
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

        static const BBGlyph glyph_109 =
        {
            8,
            glyphBitmap_109
        };

        static const uint8_t glyphBitmap_110[16] =
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

        static const BBGlyph glyph_110 =
        {
            8,
            glyphBitmap_110
        };

        static const uint8_t glyphBitmap_111[16] =
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

        static const BBGlyph glyph_111 =
        {
            8,
            glyphBitmap_111
        };

        static const uint8_t glyphBitmap_112[16] =
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

        static const BBGlyph glyph_112 =
        {
            8,
            glyphBitmap_112
        };

        static const uint8_t glyphBitmap_113[16] =
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

        static const BBGlyph glyph_113 =
        {
            8,
            glyphBitmap_113
        };

        static const uint8_t glyphBitmap_114[16] =
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

        static const BBGlyph glyph_114 =
        {
            8,
            glyphBitmap_114
        };

        static const uint8_t glyphBitmap_115[16] =
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

        static const BBGlyph glyph_115 =
        {
            8,
            glyphBitmap_115
        };

        static const uint8_t glyphBitmap_116[16] =
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

        static const BBGlyph glyph_116 =
        {
            8,
            glyphBitmap_116
        };

        static const uint8_t glyphBitmap_117[16] =
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

        static const BBGlyph glyph_117 =
        {
            8,
            glyphBitmap_117
        };

        static const uint8_t glyphBitmap_118[16] =
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

        static const BBGlyph glyph_118 =
        {
            8,
            glyphBitmap_118
        };

        static const uint8_t glyphBitmap_119[16] =
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

        static const BBGlyph glyph_119 =
        {
            8,
            glyphBitmap_119
        };

        static const uint8_t glyphBitmap_120[16] =
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

        static const BBGlyph glyph_120 =
        {
            8,
            glyphBitmap_120
        };

        static const uint8_t glyphBitmap_121[16] =
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

        static const BBGlyph glyph_121 =
        {
            8,
            glyphBitmap_121
        };

        static const uint8_t glyphBitmap_122[16] =
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

        static const BBGlyph glyph_122 =
        {
            8,
            glyphBitmap_122
        };

        static const uint8_t glyphBitmap_123[16] =
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

        static const BBGlyph glyph_123 =
        {
            8,
            glyphBitmap_123
        };

        static const uint8_t glyphBitmap_124[16] =
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

        static const BBGlyph glyph_124 =
        {
            8,
            glyphBitmap_124
        };

        static const uint8_t glyphBitmap_125[16] =
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

        static const BBGlyph glyph_125 =
        {
            8,
            glyphBitmap_125
        };

        static const uint8_t glyphBitmap_126[16] =
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

        static const BBGlyph glyph_126 =
        {
            8,
            glyphBitmap_126
        };

        switch (character)
        {
            case ' ': return &glyph_32;
            case '!': return &glyph_33;
            case '"': return &glyph_34;
            case '#': return &glyph_35;
            case '$': return &glyph_36;
            case '%': return &glyph_37;
            case '&': return &glyph_38;
            case '\'': return &glyph_39;
            case '(': return &glyph_40;
            case ')': return &glyph_41;
            case '*': return &glyph_42;
            case '+': return &glyph_43;
            case ',': return &glyph_44;
            case '-': return &glyph_45;
            case '.': return &glyph_46;
            case '/': return &glyph_47;
            case '0': return &glyph_48;
            case '1': return &glyph_49;
            case '2': return &glyph_50;
            case '3': return &glyph_51;
            case '4': return &glyph_52;
            case '5': return &glyph_53;
            case '6': return &glyph_54;
            case '7': return &glyph_55;
            case '8': return &glyph_56;
            case '9': return &glyph_57;
            case ':': return &glyph_58;
            case ';': return &glyph_59;
            case '<': return &glyph_60;
            case '=': return &glyph_61;
            case '>': return &glyph_62;
            case '?': return &glyph_63;
            case '@': return &glyph_64;
            case 'A': return &glyph_65;
            case 'B': return &glyph_66;
            case 'C': return &glyph_67;
            case 'D': return &glyph_68;
            case 'E': return &glyph_69;
            case 'F': return &glyph_70;
            case 'G': return &glyph_71;
            case 'H': return &glyph_72;
            case 'I': return &glyph_73;
            case 'J': return &glyph_74;
            case 'K': return &glyph_75;
            case 'L': return &glyph_76;
            case 'M': return &glyph_77;
            case 'N': return &glyph_78;
            case 'O': return &glyph_79;
            case 'P': return &glyph_80;
            case 'Q': return &glyph_81;
            case 'R': return &glyph_82;
            case 'S': return &glyph_83;
            case 'T': return &glyph_84;
            case 'U': return &glyph_85;
            case 'V': return &glyph_86;
            case 'W': return &glyph_87;
            case 'X': return &glyph_88;
            case 'Y': return &glyph_89;
            case 'Z': return &glyph_90;
            case '[': return &glyph_91;
            case '\\': return &glyph_92;
            case ']': return &glyph_93;
            case '^': return &glyph_94;
            case '_': return &glyph_95;
            case '`': return &glyph_96;
            case 'a': return &glyph_97;
            case 'b': return &glyph_98;
            case 'c': return &glyph_99;
            case 'd': return &glyph_100;
            case 'e': return &glyph_101;
            case 'f': return &glyph_102;
            case 'g': return &glyph_103;
            case 'h': return &glyph_104;
            case 'i': return &glyph_105;
            case 'j': return &glyph_106;
            case 'k': return &glyph_107;
            case 'l': return &glyph_108;
            case 'm': return &glyph_109;
            case 'n': return &glyph_110;
            case 'o': return &glyph_111;
            case 'p': return &glyph_112;
            case 'q': return &glyph_113;
            case 'r': return &glyph_114;
            case 's': return &glyph_115;
            case 't': return &glyph_116;
            case 'u': return &glyph_117;
            case 'v': return &glyph_118;
            case 'w': return &glyph_119;
            case 'x': return &glyph_120;
            case 'y': return &glyph_121;
            case 'z': return &glyph_122;
            case '{': return &glyph_123;
            case '|': return &glyph_124;
            case '}': return &glyph_125;
            case '~': return &glyph_126;

            default: return nullptr;
        }
    }
};

}
