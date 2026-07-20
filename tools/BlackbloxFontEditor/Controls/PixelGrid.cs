using System;
using System.Drawing;
using System.Windows.Forms;

namespace BlackbloxFontEditor.Controls;

public class PixelGrid : Control
{
    private readonly bool[,] _pixels;

    public int Columns { get; } = 5;

    public int Rows { get; } = 7;

    public PixelGrid()
    {
        _pixels = new bool[Columns, Rows];

        DoubleBuffered = true;
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        base.OnPaint(e);

        int cellWidth = Width / Columns;
        int cellHeight = Height / Rows;

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
                    _pixels[x, y]
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

        int cellWidth = Width / Columns;
        int cellHeight = Height / Rows;

        int x = e.X / cellWidth;
        int y = e.Y / cellHeight;

        if (x < 0 || x >= Columns)
            return;

        if (y < 0 || y >= Rows)
            return;

        _pixels[x, y] = !_pixels[x, y];

        Invalidate();
    }

    public void Clear()
    {
        Array.Clear(_pixels);

        Invalidate();
    }

    public bool GetPixel(int x, int y)
    {
        return _pixels[x, y];
    }

    public void SetPixel(int x, int y, bool value)
    {
        _pixels[x, y] = value;

        Invalidate();
    }
}