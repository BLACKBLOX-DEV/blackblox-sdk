using System.Collections.Generic;

namespace BlackbloxFontEditor.Models;

public class FontResource
{
    public Dictionary<char, Glyph> Glyphs { get; } = new();

    public Glyph GetGlyph(char character)
    {
        if (!Glyphs.TryGetValue(character, out Glyph? glyph))
        {
            glyph = new Glyph(5, 7);
            Glyphs[character] = glyph;
        }

        return glyph;
    }
}