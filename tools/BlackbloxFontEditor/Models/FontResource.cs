using System.Collections.Generic;
using System.Linq;

namespace BlackbloxFontEditor.Models;

public class FontResource
{
    /// <summary>
    /// Physical bitmap width of every glyph.
    /// </summary>
    public int Width { get; }

    /// <summary>
    /// Physical bitmap height of every glyph.
    /// </summary>
    public int Height { get; }

    public Dictionary<char, Glyph> Glyphs { get; } = new();

    public IEnumerable<char> Characters =>
        Glyphs.Keys.OrderBy(character => character);

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

    /// <summary>
    /// Recalculates the visible width of one glyph.
    /// </summary>
    public void CalculateDisplayWidth(char character)
    {
        Glyph glyph = GetGlyph(character);
        glyph.CalculateDisplayWidth();
    }

    /// <summary>
    /// Recalculates the visible width of every existing glyph.
    /// </summary>
    public void CalculateAllDisplayWidths()
    {
        foreach (Glyph glyph in Glyphs.Values)
        {
            glyph.CalculateDisplayWidth();
        }
    }

    /// <summary>
    /// Sets all glyphs back to fixed-width rendering.
    /// </summary>
    public void ResetAllDisplayWidths()
    {
        foreach (Glyph glyph in Glyphs.Values)
        {
            glyph.SetDisplayWidth(Width);
        }
    }
}