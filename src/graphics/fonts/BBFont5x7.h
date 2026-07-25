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
        static const uint8_t glyph_32[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_33[7] =
        {
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b00000000,
            0b10000000
        };

        static const uint8_t glyph_34[7] =
        {
            0b10100000,
            0b01010000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_35[7] =
        {
            0b01010000,
            0b01010000,
            0b11111000,
            0b01010000,
            0b11111000,
            0b01010000,
            0b01010000
        };

        static const uint8_t glyph_36[7] =
        {
            0b00100000,
            0b11111000,
            0b10100000,
            0b11111000,
            0b00101000,
            0b11111000,
            0b00100000
        };

        static const uint8_t glyph_37[7] =
        {
            0b00001000,
            0b10010000,
            0b00010000,
            0b00100000,
            0b01000000,
            0b01000000,
            0b10001000
        };

        static const uint8_t glyph_38[7] =
        {
            0b01100000,
            0b10010000,
            0b10010000,
            0b01100000,
            0b10111000,
            0b10010000,
            0b01101000
        };

        static const uint8_t glyph_39[7] =
        {
            0b10000000,
            0b10000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_40[7] =
        {
            0b01110000,
            0b11000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b11000000,
            0b01110000
        };

        static const uint8_t glyph_41[7] =
        {
            0b01110000,
            0b00011000,
            0b00001000,
            0b00001000,
            0b00001000,
            0b00011000,
            0b01110000
        };

        static const uint8_t glyph_42[7] =
        {
            0b00101000,
            0b00010000,
            0b00101000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_43[7] =
        {
            0b00000000,
            0b00100000,
            0b00100000,
            0b11111000,
            0b00100000,
            0b00100000,
            0b00000000
        };

        static const uint8_t glyph_44[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b11000000,
            0b10000000
        };

        static const uint8_t glyph_45[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b11110000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_46[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b10000000
        };

        static const uint8_t glyph_47[7] =
        {
            0b00001000,
            0b00010000,
            0b00010000,
            0b00100000,
            0b01000000,
            0b01000000,
            0b10000000
        };

        static const uint8_t glyph_48[7] =
        {
            0b01110000,
            0b10001000,
            0b10011000,
            0b10101000,
            0b11001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t glyph_49[7] =
        {
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_50[7] =
        {
            0b11110000,
            0b00001000,
            0b00001000,
            0b01110000,
            0b10000000,
            0b10000000,
            0b01111000
        };

        static const uint8_t glyph_51[7] =
        {
            0b11110000,
            0b00001000,
            0b00001000,
            0b01110000,
            0b00001000,
            0b00001000,
            0b11110000
        };

        static const uint8_t glyph_52[7] =
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b01111000,
            0b00001000,
            0b00001000,
            0b00001000
        };

        static const uint8_t glyph_53[7] =
        {
            0b01111000,
            0b10000000,
            0b10000000,
            0b11110000,
            0b00001000,
            0b00001000,
            0b11110000
        };

        static const uint8_t glyph_54[7] =
        {
            0b01110000,
            0b10001000,
            0b10000000,
            0b11110000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t glyph_55[7] =
        {
            0b11110000,
            0b00010000,
            0b00010000,
            0b00111000,
            0b00010000,
            0b00010000,
            0b00010000
        };

        static const uint8_t glyph_56[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b01110000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t glyph_57[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b01111000,
            0b00001000,
            0b00001000,
            0b01110000
        };

        static const uint8_t glyph_58[7] =
        {
            0b00000000,
            0b00000000,
            0b10000000,
            0b00000000,
            0b10000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_59[7] =
        {
            0b00000000,
            0b00000000,
            0b10000000,
            0b00000000,
            0b11000000,
            0b10000000,
            0b00000000
        };

        static const uint8_t glyph_60[7] =
        {
            0b00010000,
            0b00100000,
            0b01000000,
            0b10000000,
            0b01000000,
            0b00100000,
            0b00010000
        };

        static const uint8_t glyph_61[7] =
        {
            0b00000000,
            0b00000000,
            0b11110000,
            0b00000000,
            0b11110000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_62[7] =
        {
            0b01000000,
            0b00100000,
            0b00010000,
            0b00001000,
            0b00010000,
            0b00100000,
            0b01000000
        };

        static const uint8_t glyph_63[7] =
        {
            0b11110000,
            0b00001000,
            0b00001000,
            0b00110000,
            0b00100000,
            0b00000000,
            0b00100000
        };

        static const uint8_t glyph_64[7] =
        {
            0b00000000,
            0b00000000,
            0b01100000,
            0b10110000,
            0b10110000,
            0b10000000,
            0b01110000
        };

        static const uint8_t glyph_65[7] =
        {
            0b00100000,
            0b01010000,
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
            0b01111000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b01111000
        };

        static const uint8_t glyph_68[7] =
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b11110000
        };

        static const uint8_t glyph_69[7] =
        {
            0b11111000,
            0b10000000,
            0b10000000,
            0b11110000,
            0b10000000,
            0b10000000,
            0b11111000
        };

        static const uint8_t glyph_70[7] =
        {
            0b11111000,
            0b10000000,
            0b10000000,
            0b11110000,
            0b10000000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_71[7] =
        {
            0b01110000,
            0b10001000,
            0b10000000,
            0b10111000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t glyph_72[7] =
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b11111000,
            0b10001000,
            0b10001000,
            0b10001000
        };

        static const uint8_t glyph_73[7] =
        {
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_74[7] =
        {
            0b00001000,
            0b00001000,
            0b00001000,
            0b00001000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t glyph_75[7] =
        {
            0b10001000,
            0b10010000,
            0b10100000,
            0b11000000,
            0b10100000,
            0b10010000,
            0b10001000
        };

        static const uint8_t glyph_76[7] =
        {
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b11111000
        };

        static const uint8_t glyph_77[7] =
        {
            0b11011000,
            0b11011000,
            0b10101000,
            0b10101000,
            0b10001000,
            0b10001000,
            0b10001000
        };

        static const uint8_t glyph_78[7] =
        {
            0b11001000,
            0b11001000,
            0b10101000,
            0b10101000,
            0b10101000,
            0b10011000,
            0b10011000
        };

        static const uint8_t glyph_79[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t glyph_80[7] =
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b10000000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_81[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10101000,
            0b10010000,
            0b01101000
        };

        static const uint8_t glyph_82[7] =
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b10100000,
            0b10010000,
            0b10001000
        };

        static const uint8_t glyph_83[7] =
        {
            0b01111000,
            0b10000000,
            0b10000000,
            0b01110000,
            0b00001000,
            0b00001000,
            0b11110000
        };

        static const uint8_t glyph_84[7] =
        {
            0b11111000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000
        };

        static const uint8_t glyph_85[7] =
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t glyph_86[7] =
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b01010000,
            0b01010000,
            0b00100000
        };

        static const uint8_t glyph_87[7] =
        {
            0b10001000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b10101000,
            0b10101000,
            0b01010000
        };

        static const uint8_t glyph_88[7] =
        {
            0b10001000,
            0b10001000,
            0b01010000,
            0b00100000,
            0b01010000,
            0b10001000,
            0b10001000
        };

        static const uint8_t glyph_89[7] =
        {
            0b10001000,
            0b10001000,
            0b01010000,
            0b01010000,
            0b00100000,
            0b00100000,
            0b00100000
        };

        static const uint8_t glyph_90[7] =
        {
            0b11111000,
            0b00001000,
            0b00010000,
            0b00100000,
            0b01000000,
            0b10000000,
            0b11111000
        };

        static const uint8_t glyph_91[7] =
        {
            0b11110000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b11110000
        };

        static const uint8_t glyph_92[7] =
        {
            0b10000000,
            0b01000000,
            0b01000000,
            0b00100000,
            0b00010000,
            0b00010000,
            0b00001000
        };

        static const uint8_t glyph_93[7] =
        {
            0b11110000,
            0b00010000,
            0b00010000,
            0b00010000,
            0b00010000,
            0b00010000,
            0b11110000
        };

        static const uint8_t glyph_94[7] =
        {
            0b01000000,
            0b10100000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_95[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b11111000
        };

        static const uint8_t glyph_96[7] =
        {
            0b10000000,
            0b01000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_97[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b01100000,
            0b10010000,
            0b10010000,
            0b01110000
        };

        static const uint8_t glyph_98[7] =
        {
            0b00000000,
            0b00000000,
            0b10000000,
            0b10000000,
            0b11100000,
            0b10010000,
            0b11100000
        };

        static const uint8_t glyph_99[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b01110000,
            0b10000000,
            0b10000000,
            0b01110000
        };

        static const uint8_t glyph_100[7] =
        {
            0b00000000,
            0b00000000,
            0b00010000,
            0b00010000,
            0b01110000,
            0b10010000,
            0b01110000
        };

        static const uint8_t glyph_101[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b01100000,
            0b11110000,
            0b10000000,
            0b01110000
        };

        static const uint8_t glyph_102[7] =
        {
            0b00000000,
            0b00000000,
            0b01110000,
            0b10000000,
            0b11100000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_103[7] =
        {
            0b00000000,
            0b00000000,
            0b01110000,
            0b10010000,
            0b01110000,
            0b00010000,
            0b11100000
        };

        static const uint8_t glyph_104[7] =
        {
            0b00000000,
            0b00000000,
            0b10000000,
            0b10100000,
            0b11010000,
            0b10010000,
            0b10010000
        };

        static const uint8_t glyph_105[7] =
        {
            0b00000000,
            0b00000000,
            0b10000000,
            0b00000000,
            0b10000000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_106[7] =
        {
            0b00000000,
            0b00100000,
            0b00000000,
            0b00100000,
            0b00100000,
            0b10100000,
            0b01000000
        };

        static const uint8_t glyph_107[7] =
        {
            0b00000000,
            0b00000000,
            0b10000000,
            0b10000000,
            0b10100000,
            0b11000000,
            0b10100000
        };

        static const uint8_t glyph_108[7] =
        {
            0b00000000,
            0b00000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b01100000
        };

        static const uint8_t glyph_109[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b11010000,
            0b10101000,
            0b10101000,
            0b10001000
        };

        static const uint8_t glyph_110[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b10100000,
            0b11110000,
            0b10010000,
            0b10010000
        };

        static const uint8_t glyph_111[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b01100000,
            0b10010000,
            0b10010000,
            0b01100000
        };

        static const uint8_t glyph_112[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b11100000,
            0b10010000,
            0b11100000,
            0b10000000
        };

        static const uint8_t glyph_113[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b01110000,
            0b10010000,
            0b01110000,
            0b00010000
        };

        static const uint8_t glyph_114[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b10100000,
            0b11010000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_115[7] =
        {
            0b00000000,
            0b00000000,
            0b01110000,
            0b10000000,
            0b01100000,
            0b00010000,
            0b11100000
        };

        static const uint8_t glyph_116[7] =
        {
            0b00000000,
            0b00000000,
            0b01000000,
            0b11100000,
            0b01000000,
            0b01000000,
            0b00100000
        };

        static const uint8_t glyph_117[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b10010000,
            0b10010000,
            0b10010000,
            0b01110000
        };

        static const uint8_t glyph_118[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b10010000,
            0b10010000,
            0b10010000,
            0b01100000
        };

        static const uint8_t glyph_119[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b10001000,
            0b10001000,
            0b10101000,
            0b01010000
        };

        static const uint8_t glyph_120[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b10100000,
            0b01000000,
            0b01000000,
            0b10100000
        };

        static const uint8_t glyph_121[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b10100000,
            0b10100000,
            0b01000000,
            0b01000000
        };

        static const uint8_t glyph_122[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b11110000,
            0b00100000,
            0b01000000,
            0b11110000
        };

        static const uint8_t glyph_123[7] =
        {
            0b01100000,
            0b01000000,
            0b01000000,
            0b10000000,
            0b01000000,
            0b01000000,
            0b01100000
        };

        static const uint8_t glyph_124[7] =
        {
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000,
            0b10000000
        };

        static const uint8_t glyph_125[7] =
        {
            0b11000000,
            0b01000000,
            0b01000000,
            0b00100000,
            0b01000000,
            0b01000000,
            0b11000000
        };

        static const uint8_t glyph_126[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b01010000,
            0b10100000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_180[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_272[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_273[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_352[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_381[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_382[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t glyph_711[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        switch (character)
        {
            case ' ': return glyph_32;
            case '!': return glyph_33;
            case '"': return glyph_34;
            case '#': return glyph_35;
            case '$': return glyph_36;
            case '%': return glyph_37;
            case '&': return glyph_38;
            case '\'': return glyph_39;
            case '(': return glyph_40;
            case ')': return glyph_41;
            case '*': return glyph_42;
            case '+': return glyph_43;
            case ',': return glyph_44;
            case '-': return glyph_45;
            case '.': return glyph_46;
            case '/': return glyph_47;
            case '0': return glyph_48;
            case '1': return glyph_49;
            case '2': return glyph_50;
            case '3': return glyph_51;
            case '4': return glyph_52;
            case '5': return glyph_53;
            case '6': return glyph_54;
            case '7': return glyph_55;
            case '8': return glyph_56;
            case '9': return glyph_57;
            case ':': return glyph_58;
            case ';': return glyph_59;
            case '<': return glyph_60;
            case '=': return glyph_61;
            case '>': return glyph_62;
            case '?': return glyph_63;
            case '@': return glyph_64;
            case 'A': return glyph_65;
            case 'B': return glyph_66;
            case 'C': return glyph_67;
            case 'D': return glyph_68;
            case 'E': return glyph_69;
            case 'F': return glyph_70;
            case 'G': return glyph_71;
            case 'H': return glyph_72;
            case 'I': return glyph_73;
            case 'J': return glyph_74;
            case 'K': return glyph_75;
            case 'L': return glyph_76;
            case 'M': return glyph_77;
            case 'N': return glyph_78;
            case 'O': return glyph_79;
            case 'P': return glyph_80;
            case 'Q': return glyph_81;
            case 'R': return glyph_82;
            case 'S': return glyph_83;
            case 'T': return glyph_84;
            case 'U': return glyph_85;
            case 'V': return glyph_86;
            case 'W': return glyph_87;
            case 'X': return glyph_88;
            case 'Y': return glyph_89;
            case 'Z': return glyph_90;
            case '[': return glyph_91;
            case '\\': return glyph_92;
            case ']': return glyph_93;
            case '^': return glyph_94;
            case '_': return glyph_95;
            case '`': return glyph_96;
            case 'a': return glyph_97;
            case 'b': return glyph_98;
            case 'c': return glyph_99;
            case 'd': return glyph_100;
            case 'e': return glyph_101;
            case 'f': return glyph_102;
            case 'g': return glyph_103;
            case 'h': return glyph_104;
            case 'i': return glyph_105;
            case 'j': return glyph_106;
            case 'k': return glyph_107;
            case 'l': return glyph_108;
            case 'm': return glyph_109;
            case 'n': return glyph_110;
            case 'o': return glyph_111;
            case 'p': return glyph_112;
            case 'q': return glyph_113;
            case 'r': return glyph_114;
            case 's': return glyph_115;
            case 't': return glyph_116;
            case 'u': return glyph_117;
            case 'v': return glyph_118;
            case 'w': return glyph_119;
            case 'x': return glyph_120;
            case 'y': return glyph_121;
            case 'z': return glyph_122;
            case '{': return glyph_123;
            case '|': return glyph_124;
            case '}': return glyph_125;
            case '~': return glyph_126;
            case '´': return glyph_180;
            case 'Đ': return glyph_272;
            case 'đ': return glyph_273;
            case 'Š': return glyph_352;
            case 'Ž': return glyph_381;
            case 'ž': return glyph_382;
            case 'ˇ': return glyph_711;

            default: return nullptr;
        }
    }
};

}
