using System.Collections.Generic;
using System.Linq;

namespace BlackbloxFontEditor.Models;

public class FontResource
{
    public int Width { get; }

    public int Height { get; }

    public Dictionary<char, Glyph> Glyphs { get; } = new();

    public IEnumerable<char> Characters =>
        Glyphs.Keys.OrderBy(c => c);

    public FontResource(
        int width,
        int height)
    {
        Width = width;
        Height = height;
    }

    public Glyph GetGlyph(char character)
    {
        if (!Glyphs.TryGetValue(
                character,
                out Glyph? glyph))
        {
            glyph = new Glyph(
                Width,
                Height);

            Glyphs[character] = glyph;
        }

        return glyph;
    }
}