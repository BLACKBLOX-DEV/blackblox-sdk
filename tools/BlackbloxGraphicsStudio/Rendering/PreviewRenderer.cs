using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Rendering;

public static class PreviewRenderer
{
    public static void Draw(
        Graphics graphics,
        Rectangle clientRectangle,
        Color backgroundColor,
        Color pixelColor,
        FontResource font,
        string text,
        int spacing = 1,
        int margin = 10)
    {
        graphics.Clear(backgroundColor);

        if (string.IsNullOrEmpty(text))
            return;

        int pixelScale = Math.Max(
            1,
            Math.Min(
                10,
                (clientRectangle.Height - (margin * 2)) / Math.Max(1, font.Height)));

        int x = margin;
        int y = margin;

        using SolidBrush pixelBrush = new(pixelColor);

        foreach (char character in text)
        {
            if (character == '\r')
                continue;

            if (character == '\n')
            {
                x = margin;
                y += (font.Height + spacing) * pixelScale;
                continue;
            }

            Glyph glyph = font.GetGlyph(character);

            if (x + ((glyph.Width + spacing) * pixelScale) > clientRectangle.Width - margin)
            {
                x = margin;
                y += (font.Height + spacing) * pixelScale;
            }

            if (y + (font.Height * pixelScale) > clientRectangle.Height - margin)
                break;

            for (int row = 0; row < glyph.Height; row++)
            {
                for (int column = 0; column < glyph.Width; column++)
                {
                    if (!glyph.Pixels[column, row])
                        continue;

                    graphics.FillRectangle(
                        pixelBrush,
                        x + (column * pixelScale),
                        y + (row * pixelScale),
                        pixelScale,
                        pixelScale);
                }
            }

            x += (glyph.Width + spacing) * pixelScale;
        }
    }
}