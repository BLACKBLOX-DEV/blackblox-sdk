using BlackbloxFontEditor.Editing;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor;

public partial class MainForm
{
    private void CopyGlyph()
    {
        _clipboardPixels = BitmapEditor.CopyPixels(_font.GetGlyph(CurrentCharacter));
        UpdateInterface("Glyph copied");
    }

    private void PasteGlyph()
    {
        if (_clipboardPixels is null)
        {
            UpdateInterface("Clipboard is empty");
            return;
        }

        ApplyGlyphOperation(
            glyph => BitmapEditor.PastePixels(glyph, _clipboardPixels),
            "Glyph pasted");
    }

    private void ApplyGlyphOperation(Action<Glyph> operation, string status)
    {
        Glyph glyph = _font.GetGlyph(CurrentCharacter);
        GetHistory(CurrentCharacter).Push(glyph);

        operation(glyph);

        _lastGlyphSnapshot = BitmapEditor.CopyPixels(glyph);
        RefreshAfterHistoryChange(status);
    }

    private GlyphHistory GetHistory(char character)
    {
        if (!_histories.TryGetValue(character, out GlyphHistory? history))
        {
            history = new GlyphHistory();
            _histories.Add(character, history);
        }

        return history;
    }

    private void UndoGlyph()
    {
        Glyph glyph = _font.GetGlyph(CurrentCharacter);

        if (!GetHistory(CurrentCharacter).Undo(glyph))
        {
            UpdateInterface("Nothing to undo");
            return;
        }

        _lastGlyphSnapshot = BitmapEditor.CopyPixels(glyph);
        RefreshAfterHistoryChange("Undo");
    }

    private void RedoGlyph()
    {
        Glyph glyph = _font.GetGlyph(CurrentCharacter);

        if (!GetHistory(CurrentCharacter).Redo(glyph))
        {
            UpdateInterface("Nothing to redo");
            return;
        }

        _lastGlyphSnapshot = BitmapEditor.CopyPixels(glyph);
        RefreshAfterHistoryChange("Redo");
    }

    private void RefreshAfterHistoryChange(string status)
    {
        _grid.Invalidate();
        _previewPanel.Invalidate();
        _outputBox.Clear();
        _isDirty = true;
        UpdateInterface(status);
    }
}
