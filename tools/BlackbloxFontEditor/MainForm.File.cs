using BlackbloxFontEditor.Generators;
using BlackbloxFontEditor.Importers;
using BlackbloxFontEditor.Models;
using BlackbloxFontEditor.Persistence;
using BlackbloxFontEditor.Editing;

namespace BlackbloxFontEditor;

public partial class MainForm
{
    private void NewMenu_Click(object? sender, EventArgs e)
    {
        if (!ConfirmDiscardChanges())
            return;

        using NewFontForm dialog = new(_fontName, _font.Width, _font.Height);
        if (dialog.ShowDialog(this) != DialogResult.OK)
            return;

        _font = new FontResource(dialog.SelectedWidth, dialog.SelectedHeight);
        _histories.Clear();
        _lastGlyphSnapshot = null;
        _fontName = dialog.FontName;
        _currentFileName = null;
        _isDirty = false;

        _outputBox.Clear();
        SelectCharacter('A');
        UpdateInterface("New font created");
    }

    private void OpenMenu_Click(object? sender, EventArgs e)
    {
        if (!ConfirmDiscardChanges())
            return;

        using OpenFileDialog dialog = new()
        {
            Filter = "BLACKBLOX font files (*.bbfont)|*.bbfont|All files (*.*)|*.*",
            Title = "Open Font"
        };

        if (dialog.ShowDialog(this) != DialogResult.OK)
            return;

        try
        {
            _font = FontFileSerializer.Load(dialog.FileName, out _fontName);
            _histories.Clear();
            _lastGlyphSnapshot = null;
            _currentFileName = dialog.FileName;
            _isDirty = false;

            _outputBox.Clear();
            SelectCharacter(CurrentCharacter);
            UpdateInterface("Font opened");
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message, "Open Font", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }

    private void SaveMenu_Click(object? sender, EventArgs e)
    {
        if (string.IsNullOrWhiteSpace(_currentFileName))
        {
            SaveAsMenu_Click(sender, e);
            return;
        }

        SaveFont(_currentFileName);
    }

    private void SaveAsMenu_Click(object? sender, EventArgs e)
    {
        using SaveFileDialog dialog = new()
        {
            Filter = "BLACKBLOX font files (*.bbfont)|*.bbfont|All files (*.*)|*.*",
            Title = "Save Font As",
            DefaultExt = "bbfont",
            AddExtension = true,
            FileName = _fontName == "Untitled"
                ? $"font{_font.Width}x{_font.Height}.bbfont"
                : $"{_fontName}.bbfont"
        };

        if (dialog.ShowDialog(this) != DialogResult.OK)
            return;

        _currentFileName = dialog.FileName;
        _fontName = Path.GetFileNameWithoutExtension(dialog.FileName);
        SaveFont(dialog.FileName);
    }

    private void SaveFont(string fileName)
    {
        try
        {
            FontFileSerializer.Save(fileName, _font, _fontName);
            _isDirty = false;
            UpdateInterface("Font saved");
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message, "Save Font", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }

    private void ImportBdfMenu_Click(object? sender, EventArgs e)
    {
        using OpenFileDialog dialog = new()
        {
            Filter = "BDF font files (*.bdf)|*.bdf|All files (*.*)|*.*",
            Title = "Import BDF Font"
        };

        if (dialog.ShowDialog(this) != DialogResult.OK)
            return;

        try
        {
            int importedGlyphs = BdfImporter.Import(dialog.FileName, _font);
            _histories.Clear();
            _grid.SetGlyph(_font.GetGlyph(CurrentCharacter));
            _lastGlyphSnapshot = BitmapEditor.CopyPixels(_font.GetGlyph(CurrentCharacter));
            _outputBox.Clear();
            _previewPanel.Invalidate();
            _isDirty = true;
            UpdateInterface($"Imported {importedGlyphs} characters");

            MessageBox.Show(
                $"Imported characters: {importedGlyphs}\nTarget font size: {_font.Width} x {_font.Height}",
                "BDF Import",
                MessageBoxButtons.OK,
                MessageBoxIcon.Information);
        }
        catch (Exception ex)
        {
            MessageBox.Show(ex.Message, "BDF Import", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }

    private void ExportButton_Click(object? sender, EventArgs e)
    {
        using SaveFileDialog dialog = new()
        {
            Title = "Export BLACKBLOX C++ Font",
            Filter = "C++ header (*.h)|*.h",
            DefaultExt = "h",
            AddExtension = true,
            FileName = $"BBFont{_font.Width}x{_font.Height}.h"
        };

        if (dialog.ShowDialog(this) != DialogResult.OK)
            return;

        string className = Path.GetFileNameWithoutExtension(dialog.FileName);

        try
        {
            string source = FontExporter.GenerateHeader(
                _font,
                className,
                spacing: 1);

            File.WriteAllText(dialog.FileName, source);

            _outputBox.Text = source;
            _outputBox.Select(0, 0);

            UpdateInterface("Entire font exported");
        }
        catch (Exception ex)
        {
            MessageBox.Show(
                ex.Message,
                "Export failed",
                MessageBoxButtons.OK,
                MessageBoxIcon.Error);
        }
    }
}
