using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Editing;

public sealed class GlyphHistory
{
    private readonly Stack<bool[,]> _undo = new();
    private readonly Stack<bool[,]> _redo = new();
    private readonly int _maximumEntries;

    public GlyphHistory(int maximumEntries = 100)
    {
        _maximumEntries = Math.Max(1, maximumEntries);
    }

    public bool CanUndo => _undo.Count > 0;
    public bool CanRedo => _redo.Count > 0;

    public void Push(Glyph glyph)
    {
        PushSnapshot(BitmapEditor.CopyPixels(glyph));
    }

    public void PushSnapshot(bool[,] pixels)
    {
        _undo.Push(ClonePixels(pixels));
        _redo.Clear();

        if (_undo.Count <= _maximumEntries)
            return;

        bool[][,] entries = _undo.Reverse().Skip(1).ToArray();
        _undo.Clear();

        foreach (bool[,] entry in entries)
            _undo.Push(entry);
    }

    public bool Undo(Glyph glyph)
    {
        if (!CanUndo)
            return false;

        _redo.Push(BitmapEditor.CopyPixels(glyph));
        BitmapEditor.PastePixels(glyph, _undo.Pop());
        return true;
    }

    public bool Redo(Glyph glyph)
    {
        if (!CanRedo)
            return false;

        _undo.Push(BitmapEditor.CopyPixels(glyph));
        BitmapEditor.PastePixels(glyph, _redo.Pop());
        return true;
    }

    public void Clear()
    {
        _undo.Clear();
        _redo.Clear();
    }

    private static bool[,] ClonePixels(bool[,] source)
    {
        int width = source.GetLength(0);
        int height = source.GetLength(1);
        bool[,] clone = new bool[width, height];

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
                clone[x, y] = source[x, y];
        }

        return clone;
    }
}