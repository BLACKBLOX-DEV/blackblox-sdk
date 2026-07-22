using BlackbloxFontEditor.Editing;
using BlackbloxFontEditor.Models;
using BlackbloxFontEditor.Rendering;

namespace BlackbloxFontEditor;

public partial class MainForm
{
    private void PreviewPanel_Paint(object? sender, PaintEventArgs e)
    {
        PreviewRenderer.Draw(
            e.Graphics,
            _previewPanel.ClientRectangle,
            _previewPanel.BackColor,
            Color.Black,
            _font,
            _previewTextBox.Text,
            spacing: 1);
    }

    private void MainForm_KeyDown(object? sender, KeyEventArgs e)
    {
        if (e.Control && e.KeyCode == Keys.Z)
        {
            UndoGlyph();
            e.SuppressKeyPress = true;
            return;
        }

        if (e.Control && e.KeyCode == Keys.Y)
        {
            RedoGlyph();
            e.SuppressKeyPress = true;
            return;
        }

        if (e.Control && e.KeyCode == Keys.C)
        {
            CopyGlyph();
            e.SuppressKeyPress = true;
            return;
        }

        if (e.Control && e.KeyCode == Keys.V)
        {
            PasteGlyph();
            e.SuppressKeyPress = true;
            return;
        }

        if (_characterBox.Focused || _previewTextBox.Focused || _outputBox.Focused)
            return;

        switch (e.KeyCode)
        {
            case Keys.Left:
                ApplyGlyphOperation(BitmapEditor.ShiftLeft, "Shifted left");
                e.SuppressKeyPress = true;
                break;

            case Keys.Right:
                ApplyGlyphOperation(BitmapEditor.ShiftRight, "Shifted right");
                e.SuppressKeyPress = true;
                break;

            case Keys.Up:
                ApplyGlyphOperation(BitmapEditor.ShiftUp, "Shifted up");
                e.SuppressKeyPress = true;
                break;

            case Keys.Down:
                ApplyGlyphOperation(BitmapEditor.ShiftDown, "Shifted down");
                e.SuppressKeyPress = true;
                break;

            case Keys.Delete:
                ApplyGlyphOperation(glyph => glyph.Clear(), "Glyph cleared");
                e.SuppressKeyPress = true;
                break;
        }
    }

    private void MainForm_FormClosing(object? sender, FormClosingEventArgs e)
    {
        if (!ConfirmDiscardChanges())
            e.Cancel = true;
    }
}
