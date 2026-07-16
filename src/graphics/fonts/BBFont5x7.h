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
            5,                      // width
            7,                      // height
            1,                      // spacing
            BBFontFormat::Rows,     // bitmap format
            &BBFont5x7::getGlyph
        };

        return descriptor;
    }

    static const uint8_t* getGlyph(char character)
    {
        // Vsak byte predstavlja eno vrstico.
        // Ker je font širok 5 pik, uporabljamo bite 7..3.
        // Bit 7 je levi piksel.

        static const uint8_t space[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t digit0[7] =
        {
            0b01110000,
            0b10001000,
            0b10011000,
            0b10101000,
            0b11001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t digit1[7] =
        {
            0b00100000,
            0b01100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b00100000,
            0b01110000
        };

        static const uint8_t digit2[7] =
        {
            0b01110000,
            0b10001000,
            0b00001000,
            0b00010000,
            0b00100000,
            0b01000000,
            0b11111000
        };

        static const uint8_t digit3[7] =
        {
            0b11110000,
            0b00001000,
            0b00001000,
            0b01110000,
            0b00001000,
            0b00001000,
            0b11110000
        };

        static const uint8_t digit4[7] =
        {
            0b00010000,
            0b00110000,
            0b01010000,
            0b10010000,
            0b11111000,
            0b00010000,
            0b00010000
        };

        static const uint8_t digit5[7] =
        {
            0b11111000,
            0b10000000,
            0b10000000,
            0b11110000,
            0b00001000,
            0b00001000,
            0b11110000
        };

        static const uint8_t digit6[7] =
        {
            0b01110000,
            0b10000000,
            0b10000000,
            0b11110000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t digit7[7] =
        {
            0b11111000,
            0b00001000,
            0b00010000,
            0b00100000,
            0b01000000,
            0b01000000,
            0b01000000
        };

        static const uint8_t digit8[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b01110000,
            0b10001000,
            0b10001000,
            0b01110000
        };

        static const uint8_t digit9[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b01111000,
            0b00001000,
            0b00001000,
            0b01110000
        };

        static const uint8_t colon[7] =
        {
            0b00000000,
            0b00100000,
            0b00100000,
            0b00000000,
            0b00100000,
            0b00100000,
            0b00000000
        };

        static const uint8_t dash[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b11111000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const uint8_t dot[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00100000,
            0b00100000
        };

        static const uint8_t letterA[7] =
        {
            0b01110000,
            0b10001000,
            0b10001000,
            0b11111000,
            0b10001000,
            0b10001000,
            0b10001000
        };

        static const uint8_t letterB[7] =
        {
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000,
            0b10001000,
            0b10001000,
            0b11110000
        };

        switch (character)
        {
            case ' ': return space;

            case '0': return digit0;
            case '1': return digit1;
            case '2': return digit2;
            case '3': return digit3;
            case '4': return digit4;
            case '5': return digit5;
            case '6': return digit6;
            case '7': return digit7;
            case '8': return digit8;
            case '9': return digit9;

            case ':': return colon;
            case '-': return dash;
            case '.': return dot;

            case 'A': return letterA;
            case 'B': return letterB;

            default: return nullptr;
        }
    }
};

}