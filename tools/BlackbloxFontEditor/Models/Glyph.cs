namespace BlackbloxFontEditor.Models;

public class Glyph
{
    /// <summary>
    /// Width of bitmap (5, 8, ...)
    /// </summary>
    public int Width { get; }

    /// <summary>
    /// Height of bitmap.
    /// </summary>
    public int Height { get; }

    /// <summary>
    /// Visible width when rendering.
    /// </summary>
    public int DisplayWidth { get; private set; }

    public bool[,] Pixels { get; }

    public Glyph(int width, int height)
    {
        Width = width;
        Height = height;
        DisplayWidth = width;

        Pixels = new bool[width, height];
    }

    public void Clear()
    {
        Array.Clear(Pixels);
        DisplayWidth = Width;
    }

    public void CalculateDisplayWidth()
    {
        int lastUsedColumn = -1;

        for (int x = Width - 1; x >= 0; x--)
        {
            for (int y = 0; y < Height; y++)
            {
                if (Pixels[x, y])
                {
                    lastUsedColumn = x;
                    goto Done;
                }
            }
        }

Done:

        if (lastUsedColumn < 0)
        {
            // Space or empty glyph
            DisplayWidth = Width;
        }
        else
        {
            DisplayWidth = lastUsedColumn + 1;
        }
    }

    public void SetDisplayWidth(int width)
    {
        DisplayWidth = Math.Clamp(width, 1, Width);
    }
}