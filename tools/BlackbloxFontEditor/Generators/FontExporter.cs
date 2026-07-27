using System.Text;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Generators;

public static class FontExporter
{
    public static string GenerateHeader(
        FontResource font,
        string className,
        int spacing = 1)
    {
        ArgumentNullException.ThrowIfNull(font);

        if (font.Width < 1 || font.Width > 8)
        {
            throw new NotSupportedException(
                "The current BLACKBLOX BBFont format supports glyph widths from 1 to 8 pixels.");
        }

        if (font.Height < 1 || font.Height > byte.MaxValue)
        {
            throw new NotSupportedException(
                "The font height must be between 1 and 255 pixels.");
        }

        if (spacing < 0 || spacing > byte.MaxValue)
        {
            throw new ArgumentOutOfRangeException(
                nameof(spacing));
        }

        ValidateGlyphWidths(font);

        className = SanitizeIdentifier(className);

        List<KeyValuePair<char, Glyph>> orderedGlyphs =
            font.Glyphs
                .OrderBy(item => item.Key)
                .ToList();

        StringBuilder sb = new();

        sb.AppendLine("#pragma once");
        sb.AppendLine();
        sb.AppendLine("#include <stdint.h>");
        sb.AppendLine("#include \"BBFont.h\"");
        sb.AppendLine();
        sb.AppendLine("namespace blackblox");
        sb.AppendLine("{");
        sb.AppendLine();
        sb.AppendLine($"class {className}");
        sb.AppendLine("{");
        sb.AppendLine("public:");
        sb.AppendLine();

        AppendFontDescriptor(
            sb,
            font,
            className,
            spacing);

        sb.AppendLine();

        AppendGetGlyphMethod(
            sb,
            orderedGlyphs);

        sb.AppendLine("};");
        sb.AppendLine();
        sb.AppendLine("}");

        return sb.ToString();
    }

    public static void ExportHeader(
        FontResource font,
        string className,
        string filePath,
        int spacing = 1)
    {
        string source =
            GenerateHeader(
                font,
                className,
                spacing);

        File.WriteAllText(
            filePath,
            source,
            new UTF8Encoding(
                encoderShouldEmitUTF8Identifier: false));
    }

    private static void AppendFontDescriptor(
        StringBuilder sb,
        FontResource font,
        string className,
        int spacing)
    {
        sb.AppendLine("    static const BBFont& font()");
        sb.AppendLine("    {");
        sb.AppendLine("        static const BBFont descriptor =");
        sb.AppendLine("        {");
        sb.AppendLine($"            {font.Width},");
        sb.AppendLine($"            {font.Height},");
        sb.AppendLine($"            {spacing},");
        sb.AppendLine("            BBFontFormat::Rows,");
        sb.AppendLine($"            &{className}::getGlyph");
        sb.AppendLine("        };");
        sb.AppendLine();
        sb.AppendLine("        return descriptor;");
        sb.AppendLine("    }");
    }

    private static void AppendGetGlyphMethod(
        StringBuilder sb,
        IReadOnlyList<KeyValuePair<char, Glyph>> glyphs)
    {
        sb.AppendLine(
            "    static const BBGlyph* getGlyph(char character)");

        sb.AppendLine("    {");

        foreach (KeyValuePair<char, Glyph> item in glyphs)
        {
            AppendGlyph(
                sb,
                item.Key,
                item.Value);
        }

        sb.AppendLine("        switch (character)");
        sb.AppendLine("        {");

        foreach (KeyValuePair<char, Glyph> item in glyphs)
        {
            string characterLiteral =
                GetCharacterLiteral(item.Key);

            string glyphObjectName =
                GetGlyphObjectName(item.Key);

            sb.AppendLine(
                $"            case {characterLiteral}: return &{glyphObjectName};");
        }

        sb.AppendLine();
        sb.AppendLine("            default: return nullptr;");
        sb.AppendLine("        }");
        sb.AppendLine("    }");
    }

    private static void AppendGlyph(
        StringBuilder sb,
        char character,
        Glyph glyph)
    {
        string bitmapName =
            GetGlyphBitmapName(character);

        string glyphObjectName =
            GetGlyphObjectName(character);

        sb.AppendLine(
            $"        static const uint8_t {bitmapName}[{glyph.Height}] =");

        sb.AppendLine("        {");

        for (int y = 0; y < glyph.Height; y++)
        {
            sb.Append("            0b");

            for (int bit = 0; bit < 8; bit++)
            {
                bool pixelOn =
                    bit < glyph.Width &&
                    glyph.Pixels[bit, y];

                sb.Append(pixelOn ? '1' : '0');
            }

            if (y < glyph.Height - 1)
            {
                sb.Append(',');
            }

            sb.AppendLine();
        }

        sb.AppendLine("        };");
        sb.AppendLine();

        int displayWidth =
            CalculateDisplayWidth(glyph);

        sb.AppendLine(
            $"        static const BBGlyph {glyphObjectName} =");

        sb.AppendLine("        {");
        sb.AppendLine($"            {displayWidth},");
        sb.AppendLine($"            {bitmapName}");
        sb.AppendLine("        };");
        sb.AppendLine();
    }

    private static int CalculateDisplayWidth(
        Glyph glyph)
    {
        int configuredWidth =
            Math.Clamp(
                glyph.DisplayWidth,
                1,
                glyph.Width);

        int rightmostPixel = -1;

        for (int x = 0; x < glyph.Width; x++)
        {
            for (int y = 0; y < glyph.Height; y++)
            {
                if (glyph.Pixels[x, y])
                {
                    rightmostPixel =
                        Math.Max(
                            rightmostPixel,
                            x);
                }
            }
        }

        // Prazni glifi, predvsem presledek, nimajo naravne
        // širine. Pri njih ohranimo širino, nastavljeno v editorju.
        if (rightmostPixel < 0)
        {
            return configuredWidth;
        }

        int bitmapWidth =
            rightmostPixel + 1;

        // Samodejno odstranimo prazne stolpce na desni,
        // vendar še vedno dovolimo ročno nastavljeno ožjo širino.
        return Math.Min(
            configuredWidth,
            bitmapWidth);
    }

    private static void ValidateGlyphWidths(
        FontResource font)
    {
        foreach (KeyValuePair<char, Glyph> item in font.Glyphs)
        {
            Glyph glyph = item.Value;

            if (glyph.DisplayWidth < 1 ||
                glyph.DisplayWidth > glyph.Width)
            {
                throw new InvalidOperationException(
                    $"Character {(int)item.Key} has an invalid display width of " +
                    $"{glyph.DisplayWidth}. The valid range is 1 to {glyph.Width}.");
            }
        }
    }

    private static string GetGlyphBitmapName(
        char character)
    {
        return $"glyphBitmap_{(int)character}";
    }

    private static string GetGlyphObjectName(
        char character)
    {
        return $"glyph_{(int)character}";
    }

    private static string GetCharacterLiteral(
        char character)
    {
        return character switch
        {
            '\'' => @"'\''",
            '\\' => @"'\\'",
            '\0' => @"'\0'",
            '\n' => @"'\n'",
            '\r' => @"'\r'",
            '\t' => @"'\t'",

            _ when char.IsControl(character) =>
                $"static_cast<char>({(int)character})",

            _ => $"'{character}'"
        };
    }

    private static string SanitizeIdentifier(
        string value)
    {
        if (string.IsNullOrWhiteSpace(value))
        {
            return "BBFont";
        }

        StringBuilder sb = new();

        foreach (char character in value)
        {
            if (char.IsLetterOrDigit(character) ||
                character == '_')
            {
                sb.Append(character);
            }
        }

        if (sb.Length == 0)
        {
            return "BBFont";
        }

        if (char.IsDigit(sb[0]))
        {
            sb.Insert(0, '_');
        }

        return sb.ToString();
    }
}