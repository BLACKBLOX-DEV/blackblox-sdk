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
        static const uint8_t glyphBitmap_32[7] =
        {
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
            5,
            glyphBitmap_32
        };

        static const uint8_t glyphBitmap_33[7] =
        {
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
            5,
            glyphBitmap_33
        };

        static const uint8_t glyphBitmap_34[7] =
        {
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
            5,
            glyphBitmap_34
        };

        static const uint8_t glyphBitmap_35[7] =
        {
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
            5,
            glyphBitmap_35
        };

        static const uint8_t glyphBitmap_36[7] =
        {
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
            5,
            glyphBitmap_36
        };

        static const uint8_t glyphBitmap_37[7] =
        {
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
            5,
            glyphBitmap_37
        };

        static const uint8_t glyphBitmap_38[7] =
        {
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
            5,
            glyphBitmap_38
        };

        static const uint8_t glyphBitmap_39[7] =
        {
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
            5,
            glyphBitmap_39
        };

        static const uint8_t glyphBitmap_40[7] =
        {
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
            5,
            glyphBitmap_40
        };

        static const uint8_t glyphBitmap_41[7] =
        {
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
            5,
            glyphBitmap_41
        };

        static const uint8_t glyphBitmap_42[7] =
        {
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
            5,
            glyphBitmap_42
        };

        static const uint8_t glyphBitmap_43[7] =
        {
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
            5,
            glyphBitmap_43
        };

        static const uint8_t glyphBitmap_44[7] =
        {
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
            5,
            glyphBitmap_44
        };

        static const uint8_t glyphBitmap_45[7] =
        {
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
            5,
            glyphBitmap_45
        };

        static const uint8_t glyphBitmap_46[7] =
        {
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
            5,
            glyphBitmap_46
        };

        static const uint8_t glyphBitmap_47[7] =
        {
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
            5,
            glyphBitmap_47
        };

        static const uint8_t glyphBitmap_48[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_48 =
        {
            5,
            glyphBitmap_48
        };

        static const uint8_t glyphBitmap_49[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_49 =
        {
            5,
            glyphBitmap_49
        };

        static const uint8_t glyphBitmap_50[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_50 =
        {
            5,
            glyphBitmap_50
        };

        static const uint8_t glyphBitmap_51[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_51 =
        {
            5,
            glyphBitmap_51
        };

        static const uint8_t glyphBitmap_52[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_52 =
        {
            5,
            glyphBitmap_52
        };

        static const uint8_t glyphBitmap_53[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_53 =
        {
            5,
            glyphBitmap_53
        };

        static const uint8_t glyphBitmap_54[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_54 =
        {
            5,
            glyphBitmap_54
        };

        static const uint8_t glyphBitmap_55[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_55 =
        {
            5,
            glyphBitmap_55
        };

        static const uint8_t glyphBitmap_56[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_56 =
        {
            5,
            glyphBitmap_56
        };

        static const uint8_t glyphBitmap_57[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_57 =
        {
            5,
            glyphBitmap_57
        };

        static const uint8_t glyphBitmap_58[7] =
        {
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000000
        };

        static const BBGlyph glyph_58 =
        {
            5,
            glyphBitmap_58
        };

        static const uint8_t glyphBitmap_59[7] =
        {
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
            5,
            glyphBitmap_59
        };

        static const uint8_t glyphBitmap_60[7] =
        {
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
            5,
            glyphBitmap_60
        };

        static const uint8_t glyphBitmap_61[7] =
        {
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
            5,
            glyphBitmap_61
        };

        static const uint8_t glyphBitmap_62[7] =
        {
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
            5,
            glyphBitmap_62
        };

        static const uint8_t glyphBitmap_63[7] =
        {
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
            5,
            glyphBitmap_63
        };

        static const uint8_t glyphBitmap_64[7] =
        {
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
            5,
            glyphBitmap_64
        };

        static const uint8_t glyphBitmap_65[7] =
        {
            0b01110000,
            0b01010000,
            0b10001000,
            0b10001000,
            0b10001000,
            0b11111000,
            0b10001000
        };

        static const BBGlyph glyph_65 =
        {
            5,
            glyphBitmap_65
        };

        static const uint8_t glyphBitmap_66[7] =
        {
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
            5,
            glyphBitmap_66
        };

        static const uint8_t glyphBitmap_67[7] =
        {
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
            5,
            glyphBitmap_67
        };

        static const uint8_t glyphBitmap_68[7] =
        {
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
            5,
            glyphBitmap_68
        };

        static const uint8_t glyphBitmap_69[7] =
        {
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
            5,
            glyphBitmap_69
        };

        static const uint8_t glyphBitmap_70[7] =
        {
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
            5,
            glyphBitmap_70
        };

        static const uint8_t glyphBitmap_71[7] =
        {
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
            5,
            glyphBitmap_71
        };

        static const uint8_t glyphBitmap_72[7] =
        {
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
            5,
            glyphBitmap_72
        };

        static const uint8_t glyphBitmap_73[7] =
        {
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
            5,
            glyphBitmap_73
        };

        static const uint8_t glyphBitmap_74[7] =
        {
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
            5,
            glyphBitmap_74
        };

        static const uint8_t glyphBitmap_75[7] =
        {
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
            5,
            glyphBitmap_75
        };

        static const uint8_t glyphBitmap_76[7] =
        {
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
            5,
            glyphBitmap_76
        };

        static const uint8_t glyphBitmap_77[7] =
        {
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
            5,
            glyphBitmap_77
        };

        static const uint8_t glyphBitmap_78[7] =
        {
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
            5,
            glyphBitmap_78
        };

        static const uint8_t glyphBitmap_79[7] =
        {
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
            5,
            glyphBitmap_79
        };

        static const uint8_t glyphBitmap_80[7] =
        {
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
            5,
            glyphBitmap_80
        };

        static const uint8_t glyphBitmap_81[7] =
        {
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
            5,
            glyphBitmap_81
        };

        static const uint8_t glyphBitmap_82[7] =
        {
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
            5,
            glyphBitmap_82
        };

        static const uint8_t glyphBitmap_83[7] =
        {
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
            5,
            glyphBitmap_83
        };

        static const uint8_t glyphBitmap_84[7] =
        {
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
            5,
            glyphBitmap_84
        };

        static const uint8_t glyphBitmap_85[7] =
        {
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
            5,
            glyphBitmap_85
        };

        static const uint8_t glyphBitmap_86[7] =
        {
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
            5,
            glyphBitmap_86
        };

        static const uint8_t glyphBitmap_87[7] =
        {
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
            5,
            glyphBitmap_87
        };

        static const uint8_t glyphBitmap_88[7] =
        {
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
            5,
            glyphBitmap_88
        };

        static const uint8_t glyphBitmap_89[7] =
        {
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
            5,
            glyphBitmap_89
        };

        static const uint8_t glyphBitmap_90[7] =
        {
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
            5,
            glyphBitmap_90
        };

        static const uint8_t glyphBitmap_91[7] =
        {
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
            5,
            glyphBitmap_91
        };

        static const uint8_t glyphBitmap_92[7] =
        {
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
            5,
            glyphBitmap_92
        };

        static const uint8_t glyphBitmap_93[7] =
        {
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
            5,
            glyphBitmap_93
        };

        static const uint8_t glyphBitmap_94[7] =
        {
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
            5,
            glyphBitmap_94
        };

        static const uint8_t glyphBitmap_95[7] =
        {
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
            5,
            glyphBitmap_95
        };

        static const uint8_t glyphBitmap_96[7] =
        {
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
            5,
            glyphBitmap_96
        };

        static const uint8_t glyphBitmap_97[7] =
        {
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
            5,
            glyphBitmap_97
        };

        static const uint8_t glyphBitmap_98[7] =
        {
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
            5,
            glyphBitmap_98
        };

        static const uint8_t glyphBitmap_99[7] =
        {
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
            5,
            glyphBitmap_99
        };

        static const uint8_t glyphBitmap_100[7] =
        {
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
            5,
            glyphBitmap_100
        };

        static const uint8_t glyphBitmap_101[7] =
        {
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
            5,
            glyphBitmap_101
        };

        static const uint8_t glyphBitmap_102[7] =
        {
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
            5,
            glyphBitmap_102
        };

        static const uint8_t glyphBitmap_103[7] =
        {
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
            5,
            glyphBitmap_103
        };

        static const uint8_t glyphBitmap_104[7] =
        {
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
            5,
            glyphBitmap_104
        };

        static const uint8_t glyphBitmap_105[7] =
        {
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
            5,
            glyphBitmap_105
        };

        static const uint8_t glyphBitmap_106[7] =
        {
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
            5,
            glyphBitmap_106
        };

        static const uint8_t glyphBitmap_107[7] =
        {
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
            5,
            glyphBitmap_107
        };

        static const uint8_t glyphBitmap_108[7] =
        {
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
            5,
            glyphBitmap_108
        };

        static const uint8_t glyphBitmap_109[7] =
        {
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
            5,
            glyphBitmap_109
        };

        static const uint8_t glyphBitmap_110[7] =
        {
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
            5,
            glyphBitmap_110
        };

        static const uint8_t glyphBitmap_111[7] =
        {
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
            5,
            glyphBitmap_111
        };

        static const uint8_t glyphBitmap_112[7] =
        {
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
            5,
            glyphBitmap_112
        };

        static const uint8_t glyphBitmap_113[7] =
        {
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
            5,
            glyphBitmap_113
        };

        static const uint8_t glyphBitmap_114[7] =
        {
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
            5,
            glyphBitmap_114
        };

        static const uint8_t glyphBitmap_115[7] =
        {
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
            5,
            glyphBitmap_115
        };

        static const uint8_t glyphBitmap_116[7] =
        {
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
            5,
            glyphBitmap_116
        };

        static const uint8_t glyphBitmap_117[7] =
        {
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
            5,
            glyphBitmap_117
        };

        static const uint8_t glyphBitmap_118[7] =
        {
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
            5,
            glyphBitmap_118
        };

        static const uint8_t glyphBitmap_119[7] =
        {
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
            5,
            glyphBitmap_119
        };

        static const uint8_t glyphBitmap_120[7] =
        {
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
            5,
            glyphBitmap_120
        };

        static const uint8_t glyphBitmap_121[7] =
        {
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
            5,
            glyphBitmap_121
        };

        static const uint8_t glyphBitmap_122[7] =
        {
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
            5,
            glyphBitmap_122
        };

        static const uint8_t glyphBitmap_123[7] =
        {
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
            5,
            glyphBitmap_123
        };

        static const uint8_t glyphBitmap_124[7] =
        {
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
            5,
            glyphBitmap_124
        };

        static const uint8_t glyphBitmap_125[7] =
        {
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
            5,
            glyphBitmap_125
        };

        static const uint8_t glyphBitmap_126[7] =
        {
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
            5,
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
