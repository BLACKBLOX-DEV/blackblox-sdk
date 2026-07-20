using System;
using System.Drawing;
using System.Windows.Forms;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Controls;

public class PixelGrid : Control
{
    public Glyph? Glyph { get; private set; }

    public int Columns => Glyph?.Width ?? 0;

    public int Rows => Glyph?.Height ?? 0;

    public PixelGrid()
    {
        DoubleBuffered = true;
    }

    public void SetGlyph(Glyph glyph)
    {
        Glyph = glyph ?? throw new ArgumentNullException(nameof(glyph));

        Invalidate();
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        base.OnPaint(e);

        if (Glyph is null || Columns == 0 || Rows == 0)
            return;

        int cellWidth = Width / Columns;
        int cellHeight = Height / Rows;

        if (cellWidth <= 0 || cellHeight <= 0)
            return;

        for (int y = 0; y < Rows; y++)
        {
            for (int x = 0; x < Columns; x++)
            {
                Rectangle r = new Rectangle(
                    x * cellWidth,
                    y * cellHeight,
                    cellWidth - 1,
                    cellHeight - 1);

                e.Graphics.FillRectangle(
                    Glyph.Pixels[x, y]
                        ? Brushes.Black
                        : Brushes.White,
                    r);

                e.Graphics.DrawRectangle(
                    Pens.Gray,
                    r);
            }
        }
    }

    protected override void OnMouseDown(MouseEventArgs e)
    {
        base.OnMouseDown(e);

        if (Glyph is null || Columns == 0 || Rows == 0)
            return;

        int cellWidth = Width / Columns;
        int cellHeight = Height / Rows;

        if (cellWidth <= 0 || cellHeight <= 0)
            return;

        int x = e.X / cellWidth;
        int y = e.Y / cellHeight;

        if (x < 0 || x >= Columns)
            return;

        if (y < 0 || y >= Rows)
            return;

        Glyph.Pixels[x, y] = !Glyph.Pixels[x, y];

        Invalidate();
    }

    public void Clear()
    {
        Glyph?.Clear();

        Invalidate();
    }

    public bool GetPixel(int x, int y)
    {
        if (Glyph is null)
            return false;

        return Glyph.Pixels[x, y];
    }

    public void SetPixel(int x, int y, bool value)
    {
        if (Glyph is null)
            return;

        Glyph.Pixels[x, y] = value;

        Invalidate();
    }
}