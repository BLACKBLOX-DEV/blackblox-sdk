using System.Drawing;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Controls;

public class PixelGrid : Control
{
    public Glyph? Glyph { get; private set; }

    public int Columns => Glyph?.Width ?? 0;

    public int Rows => Glyph?.Height ?? 0;

    public event EventHandler? PixelChanged;

    public PixelGrid()
    {
        DoubleBuffered = true;
        BackColor = Color.White;
    }

    public void SetGlyph(Glyph glyph)
    {
        Glyph = glyph ?? throw new ArgumentNullException(nameof(glyph));

        Glyph.CalculateDisplayWidth();

        Invalidate();
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        base.OnPaint(e);

        if (Glyph is null || Columns == 0 || Rows == 0)
            return;

        int cellSize = Math.Min(
            ClientSize.Width / Columns,
            ClientSize.Height / Rows);

        if (cellSize <= 0)
            return;

        int gridWidth = cellSize * Columns;
        int gridHeight = cellSize * Rows;

        int offsetX =
            (ClientSize.Width - gridWidth) / 2;

        int offsetY =
            (ClientSize.Height - gridHeight) / 2;

        e.Graphics.Clear(BackColor);

        for (int y = 0; y < Rows; y++)
        {
            for (int x = 0; x < Columns; x++)
            {
                Rectangle rectangle = new(
                    offsetX + x * cellSize,
                    offsetY + y * cellSize,
                    cellSize,
                    cellSize);

                e.Graphics.FillRectangle(
                    Glyph.Pixels[x, y]
                        ? Brushes.Black
                        : Brushes.White,
                    rectangle);

                e.Graphics.DrawRectangle(
                    Pens.Gray,
                    rectangle);
            }
        }
    }

    protected override void OnMouseDown(MouseEventArgs e)
    {
        base.OnMouseDown(e);

        if (Glyph is null ||
            Columns == 0 ||
            Rows == 0)
        {
            return;
        }

        int cellSize = Math.Min(
            ClientSize.Width / Columns,
            ClientSize.Height / Rows);

        if (cellSize <= 0)
            return;

        int gridWidth = cellSize * Columns;
        int gridHeight = cellSize * Rows;

        int offsetX =
            (ClientSize.Width - gridWidth) / 2;

        int offsetY =
            (ClientSize.Height - gridHeight) / 2;

        int localX = e.X - offsetX;
        int localY = e.Y - offsetY;

        if (localX < 0 ||
            localY < 0 ||
            localX >= gridWidth ||
            localY >= gridHeight)
        {
            return;
        }

        int x = localX / cellSize;
        int y = localY / cellSize;

        Glyph.Pixels[x, y] =
            !Glyph.Pixels[x, y];

        Glyph.CalculateDisplayWidth();

        PixelChanged?.Invoke(
            this,
            EventArgs.Empty);

        Invalidate();
    }

    public void Clear()
    {
        if (Glyph is null)
            return;

        Glyph.Clear();

        PixelChanged?.Invoke(
            this,
            EventArgs.Empty);

        Invalidate();
    }

    public bool GetPixel(int x, int y)
    {
        if (Glyph is null)
            return false;

        ValidateCoordinates(x, y);

        return Glyph.Pixels[x, y];
    }

    public void SetPixel(
        int x,
        int y,
        bool value)
    {
        if (Glyph is null)
            return;

        ValidateCoordinates(x, y);

        if (Glyph.Pixels[x, y] == value)
            return;

        Glyph.Pixels[x, y] = value;

        Glyph.CalculateDisplayWidth();

        PixelChanged?.Invoke(
            this,
            EventArgs.Empty);

        Invalidate();
    }

    private void ValidateCoordinates(
        int x,
        int y)
    {
        if (Glyph is null)
            throw new InvalidOperationException(
                "No glyph is currently assigned.");

        if (x < 0 ||
            x >= Glyph.Width ||
            y < 0 ||
            y >= Glyph.Height)
        {
            throw new ArgumentOutOfRangeException(
                nameof(x),
                $"Pixel coordinates ({x}, {y}) are outside the glyph.");
        }
    }
}