using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Editing;

public static class BitmapEditor
{
    public static bool[,] CopyPixels(Glyph glyph)
    {
        bool[,] copy = new bool[glyph.Width, glyph.Height];

        for (int y = 0; y < glyph.Height; y++)
        {
            for (int x = 0; x < glyph.Width; x++)
                copy[x, y] = glyph.Pixels[x, y];
        }

        return copy;
    }

    public static void PastePixels(Glyph glyph, bool[,] source)
    {
        glyph.Clear();

        int width = Math.Min(glyph.Width, source.GetLength(0));
        int height = Math.Min(glyph.Height, source.GetLength(1));

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
                glyph.Pixels[x, y] = source[x, y];
        }
    }

    public static void Invert(Glyph glyph)
    {
        for (int y = 0; y < glyph.Height; y++)
        {
            for (int x = 0; x < glyph.Width; x++)
                glyph.Pixels[x, y] = !glyph.Pixels[x, y];
        }
    }

    public static void MirrorHorizontal(Glyph glyph)
    {
        for (int y = 0; y < glyph.Height; y++)
        {
            for (int x = 0; x < glyph.Width / 2; x++)
            {
                int opposite = glyph.Width - 1 - x;
                (glyph.Pixels[x, y], glyph.Pixels[opposite, y]) =
                    (glyph.Pixels[opposite, y], glyph.Pixels[x, y]);
            }
        }
    }

    public static void MirrorVertical(Glyph glyph)
    {
        for (int y = 0; y < glyph.Height / 2; y++)
        {
            int opposite = glyph.Height - 1 - y;

            for (int x = 0; x < glyph.Width; x++)
            {
                (glyph.Pixels[x, y], glyph.Pixels[x, opposite]) =
                    (glyph.Pixels[x, opposite], glyph.Pixels[x, y]);
            }
        }
    }

    public static void ShiftLeft(Glyph glyph)
    {
        for (int y = 0; y < glyph.Height; y++)
        {
            for (int x = 0; x < glyph.Width - 1; x++)
                glyph.Pixels[x, y] = glyph.Pixels[x + 1, y];

            glyph.Pixels[glyph.Width - 1, y] = false;
        }
    }

    public static void ShiftRight(Glyph glyph)
    {
        for (int y = 0; y < glyph.Height; y++)
        {
            for (int x = glyph.Width - 1; x > 0; x--)
                glyph.Pixels[x, y] = glyph.Pixels[x - 1, y];

            glyph.Pixels[0, y] = false;
        }
    }

    public static void ShiftUp(Glyph glyph)
    {
        for (int x = 0; x < glyph.Width; x++)
        {
            for (int y = 0; y < glyph.Height - 1; y++)
                glyph.Pixels[x, y] = glyph.Pixels[x, y + 1];

            glyph.Pixels[x, glyph.Height - 1] = false;
        }
    }

    public static void ShiftDown(Glyph glyph)
    {
        for (int x = 0; x < glyph.Width; x++)
        {
            for (int y = glyph.Height - 1; y > 0; y--)
                glyph.Pixels[x, y] = glyph.Pixels[x, y - 1];

            glyph.Pixels[x, 0] = false;
        }
    }

    public static void RotateClockwise(Glyph glyph)
    {
        bool[,] source = CopyPixels(glyph);
        glyph.Clear();

        int sourceWidth = source.GetLength(0);
        int sourceHeight = source.GetLength(1);

        for (int y = 0; y < glyph.Height; y++)
        {
            for (int x = 0; x < glyph.Width; x++)
            {
                int sourceX = y;
                int sourceY = sourceHeight - 1 - x;

                if (sourceX >= 0 && sourceX < sourceWidth &&
                    sourceY >= 0 && sourceY < sourceHeight)
                {
                    glyph.Pixels[x, y] = source[sourceX, sourceY];
                }
            }
        }
    }
}