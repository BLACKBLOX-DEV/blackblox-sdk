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
            throw new NotSupportedException(
                "The current BLACKBLOX BBFont format supports glyph widths from 1 to 8 pixels.");

        if (font.Height < 1 || font.Height > byte.MaxValue)
            throw new NotSupportedException(
                "The font height must be between 1 and 255 pixels.");

        if (spacing < 0 || spacing > byte.MaxValue)
            throw new ArgumentOutOfRangeException(nameof(spacing));

        className = SanitizeIdentifier(className);

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
        sb.AppendLine();
        sb.AppendLine("    static const uint8_t* getGlyph(char character)");
        sb.AppendLine("    {");

        foreach (KeyValuePair<char, Glyph> item in font.Glyphs.OrderBy(item => item.Key))
            AppendGlyphArray(sb, item.Key, item.Value);

        sb.AppendLine("        switch (character)");
        sb.AppendLine("        {");

        foreach (KeyValuePair<char, Glyph> item in font.Glyphs.OrderBy(item => item.Key))
        {
            string characterLiteral = GetCharacterLiteral(item.Key);
            string glyphName = GetGlyphName(item.Key);
            sb.AppendLine($"            case {characterLiteral}: return {glyphName};");
        }

        sb.AppendLine();
        sb.AppendLine("            default: return nullptr;");
        sb.AppendLine("        }");
        sb.AppendLine("    }");
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
        string source = GenerateHeader(font, className, spacing);
        File.WriteAllText(
            filePath,
            source,
            new UTF8Encoding(encoderShouldEmitUTF8Identifier: false));
    }

    private static void AppendGlyphArray(
        StringBuilder sb,
        char character,
        Glyph glyph)
    {
        string glyphName = GetGlyphName(character);

        sb.AppendLine($"        static const uint8_t {glyphName}[{glyph.Height}] =");
        sb.AppendLine("        {");

        for (int y = 0; y < glyph.Height; y++)
        {
            sb.Append("            0b");

            for (int bit = 0; bit < 8; bit++)
            {
                bool pixelOn = bit < glyph.Width && glyph.Pixels[bit, y];
                sb.Append(pixelOn ? '1' : '0');
            }

            if (y < glyph.Height - 1)
                sb.Append(',');

            sb.AppendLine();
        }

        sb.AppendLine("        };");
        sb.AppendLine();
    }

    private static string GetGlyphName(char character) => $"glyph_{(int)character}";

    private static string GetCharacterLiteral(char character)
    {
        return character switch
        {
            '\'' => @"'\''",
            '\\' => @"'\\'",
            '\0' => @"'\0'",
            '\n' => @"'\n'",
            '\r' => @"'\r'",
            '\t' => @"'\t'",
            _ when char.IsControl(character) => $"static_cast<char>({(int)character})",
            _ => $"'{character}'"
        };
    }

    private static string SanitizeIdentifier(string value)
    {
        if (string.IsNullOrWhiteSpace(value))
            return "BBFont";

        StringBuilder sb = new();

        foreach (char character in value)
        {
            if (char.IsLetterOrDigit(character) || character == '_')
                sb.Append(character);
        }

        if (sb.Length == 0)
            return "BBFont";

        if (char.IsDigit(sb[0]))
            sb.Insert(0, '_');

        return sb.ToString();
    }
}