using BlackbloxFontEditor.Editing;

namespace BlackbloxFontEditor;

public partial class MainForm
{
    private FlowLayoutPanel CreateToolsPanel()
    {
        FlowLayoutPanel panel = new()
        {
            Left = 175,
            Top = 78,
            Width = 430,
            Height = 35,
            WrapContents = false,
            AutoSize = false
        };

        panel.Controls.Add(CreateToolButton("↶", (_, _) => UndoGlyph(), 34));
        panel.Controls.Add(CreateToolButton("↷", (_, _) => RedoGlyph(), 34));
        panel.Controls.Add(CreateToolButton("Copy", (_, _) => CopyGlyph(), 58));
        panel.Controls.Add(CreateToolButton("Paste", (_, _) => PasteGlyph(), 58));
        panel.Controls.Add(CreateToolButton("←", (_, _) => ApplyGlyphOperation(BitmapEditor.ShiftLeft, "Shifted left"), 34));
        panel.Controls.Add(CreateToolButton("→", (_, _) => ApplyGlyphOperation(BitmapEditor.ShiftRight, "Shifted right"), 34));
        panel.Controls.Add(CreateToolButton("↑", (_, _) => ApplyGlyphOperation(BitmapEditor.ShiftUp, "Shifted up"), 34));
        panel.Controls.Add(CreateToolButton("↓", (_, _) => ApplyGlyphOperation(BitmapEditor.ShiftDown, "Shifted down"), 34));
        panel.Controls.Add(CreateToolButton("Rot", (_, _) => ApplyGlyphOperation(BitmapEditor.RotateClockwise, "Glyph rotated"), 42));
        panel.Controls.Add(CreateToolButton("H", (_, _) => ApplyGlyphOperation(BitmapEditor.MirrorHorizontal, "Mirrored horizontally"), 34));
        panel.Controls.Add(CreateToolButton("V", (_, _) => ApplyGlyphOperation(BitmapEditor.MirrorVertical, "Mirrored vertically"), 34));
        panel.Controls.Add(CreateToolButton("Inv", (_, _) => ApplyGlyphOperation(BitmapEditor.Invert, "Glyph inverted"), 40));

        return panel;
    }

    private static Button CreateToolButton(
        string text,
        EventHandler clickHandler,
        int width)
    {
        Button button = new()
        {
            Width = width,
            Height = 30,
            Text = text,
            Margin = new Padding(0, 0, 4, 0)
        };

        button.Click += clickHandler;
        return button;
    }
}
