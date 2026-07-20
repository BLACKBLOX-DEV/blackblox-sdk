namespace BlackbloxFontEditor.Models;

public class Glyph
{
    public int Width { get; }

    public int Height { get; }

    public bool[,] Pixels { get; }

    public Glyph(int width, int height)
    {
        Width = width;
        Height = height;

        Pixels = new bool[width, height];
    }

    public void Clear()
    {
        Array.Clear(Pixels);
    }
}