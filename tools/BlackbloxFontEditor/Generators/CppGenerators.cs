using System.Text;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Generators;

public static class CppGenerator
{
    public static string Generate(Glyph glyph, string name)
    {
        StringBuilder sb = new();

        sb.AppendLine($"static const uint8_t {name}[] =");
        sb.AppendLine("{");

        for (int y = 0; y < glyph.Height; y++)
        {
            sb.Append("    0b");

            for (int x = 0; x < glyph.Width; x++)
            {
                sb.Append(glyph.Pixels[x, y] ? '1' : '0');
            }

            sb.Append("000");

            if (y < glyph.Height - 1)
                sb.Append(",");

            sb.AppendLine();
        }

        sb.AppendLine("};");

        return sb.ToString();
    }
}