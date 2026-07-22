using BlackbloxFontEditor.Controls;
using BlackbloxFontEditor.Editing;
using BlackbloxFontEditor.Generators;
using BlackbloxFontEditor.Importers;
using BlackbloxFontEditor.Models;
using BlackbloxFontEditor.Persistence;
using BlackbloxFontEditor.Rendering;

namespace BlackbloxFontEditor;

public partial class MainForm : Form
{
    private readonly PixelGrid _grid;
    private readonly TextBox _characterBox;
    private readonly Label _asciiValueLabel;
    private readonly Label _fontNameValueLabel;
    private readonly Label _fontSizeValueLabel;
    private readonly TextBox _outputBox;
    private readonly ToolStripStatusLabel _statusLabel;
    private readonly ListBox _characterList;
    private readonly TextBox _previewTextBox;
    private readonly Panel _previewPanel;

    private FontResource _font;
    private string? _currentFileName;
    private string _fontName = "Untitled";
    private bool _isDirty;
    private bool _updatingCharacterSelection;
    private bool[,]? _clipboardPixels;

    public MainForm()
    {
        InitializeComponent();

        Text = "BLACKBLOX Font Editor";
        ClientSize = new Size(1240, 800);
        MinimumSize = new Size(1080, 720);
        StartPosition = FormStartPosition.CenterScreen;
        KeyPreview = true;

        MenuStrip menu = CreateMenu();
        MainMenuStrip = menu;
        Controls.Add(menu);

        _font = new FontResource(5, 7);

        Label charactersLabel = new()
        {
            Left = 20,
            Top = 47,
            Width = 110,
            Text = "Characters:"
        };

        _characterList = new ListBox
        {
            Left = 20,
            Top = 70,
            Width = 135,
            Height = 610,
            IntegralHeight = false,
            Font = new Font("Consolas", 10),
            Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left
        };

        PopulateCharacterList();

        Label characterLabel = new()
        {
            Left = 175,
            Top = 47,
            Width = 78,
            Text = "Character:"
        };

        _characterBox = new TextBox
        {
            Left = 253,
            Top = 43,
            Width = 36,
            Text = "A",
            MaxLength = 1,
            TextAlign = HorizontalAlignment.Center
        };

        Label asciiLabel = new()
        {
            Left = 305,
            Top = 47,
            Width = 43,
            Text = "ASCII:"
        };

        _asciiValueLabel = new Label
        {
            Left = 350,
            Top = 47,
            Width = 45,
            Text = "65"
        };

        Label fontNameLabel = new()
        {
            Left = 420,
            Top = 47,
            Width = 38,
            Text = "Font:"
        };

        _fontNameValueLabel = new Label
        {
            Left = 460,
            Top = 47,
            Width = 220,
            AutoEllipsis = true,
            Text = _fontName
        };

        Label fontSizeLabel = new()
        {
            Left = 700,
            Top = 47,
            Width = 34,
            Text = "Size:"
        };

        _fontSizeValueLabel = new Label
        {
            Left = 738,
            Top = 47,
            Width = 80,
            Text = "5 x 7"
        };

        FlowLayoutPanel toolsPanel = CreateToolsPanel();

        _grid = new PixelGrid
        {
            Left = 175,
            Top = 120,
            Width = 430,
            Height = 560,
            Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left
        };
        _grid.SetGlyph(_font.GetGlyph('A'));
        _grid.PixelChanged += Grid_PixelChanged;

        Label outputLabel = new()
        {
            Left = 630,
            Top = 78,
            Width = 120,
            Text = "Generated C++:"
        };

        _outputBox = new TextBox
        {
            Left = 630,
            Top = 102,
            Width = 585,
            Height = 350,
            Multiline = true,
            ScrollBars = ScrollBars.Both,
            Font = new Font("Consolas", 10),
            WordWrap = false,
            Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right
        };

        Label previewTextLabel = new()
        {
            Left = 630,
            Top = 472,
            Width = 90,
            Text = "Preview text:"
        };

        _previewTextBox = new TextBox
        {
            Left = 720,
            Top = 468,
            Width = 495,
            Text = "BLACKBLOX",
            Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right
        };

        Label previewLabel = new()
        {
            Left = 630,
            Top = 510,
            Width = 100,
            Text = "Preview:"
        };

        _previewPanel = new Panel
        {
            Left = 630,
            Top = 535,
            Width = 585,
            Height = 145,
            BorderStyle = BorderStyle.FixedSingle,
            BackColor = Color.White,
            Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right
        };
        _previewPanel.Paint += PreviewPanel_Paint;

        Button clearButton = new()
        {
            Left = 175,
            Top = 700,
            Width = 90,
            Height = 35,
            Text = "Clear",
            Anchor = AnchorStyles.Bottom | AnchorStyles.Left
        };

        Button exportButton = new()
        {
            Left = 275,
            Top = 700,
            Width = 120,
            Height = 35,
            Text = "Export C++",
            Anchor = AnchorStyles.Bottom | AnchorStyles.Left
        };

        Button previousButton = new()
        {
            Left = 415,
            Top = 700,
            Width = 50,
            Height = 35,
            Text = "◀",
            Anchor = AnchorStyles.Bottom | AnchorStyles.Left
        };

        Button nextButton = new()
        {
            Left = 475,
            Top = 700,
            Width = 50,
            Height = 35,
            Text = "▶",
            Anchor = AnchorStyles.Bottom | AnchorStyles.Left
        };

        StatusStrip statusStrip = new();
        _statusLabel = new ToolStripStatusLabel
        {
            Spring = true,
            TextAlign = ContentAlignment.MiddleLeft
        };
        statusStrip.Items.Add(_statusLabel);

        _characterList.SelectedIndexChanged += CharacterList_SelectedIndexChanged;
        _characterBox.TextChanged += CharacterBox_TextChanged;
        _characterBox.KeyDown += CharacterBox_KeyDown;
        _previewTextBox.TextChanged += (_, _) => _previewPanel.Invalidate();
        clearButton.Click += (_, _) => ApplyGlyphOperation(
            glyph => glyph.Clear(),
            "Glyph cleared");
        exportButton.Click += ExportButton_Click;
        previousButton.Click += PreviousButton_Click;
        nextButton.Click += NextButton_Click;
        FormClosing += MainForm_FormClosing;
        KeyDown += MainForm_KeyDown;

        Controls.Add(charactersLabel);
        Controls.Add(_characterList);
        Controls.Add(characterLabel);
        Controls.Add(_characterBox);
        Controls.Add(asciiLabel);
        Controls.Add(_asciiValueLabel);
        Controls.Add(fontNameLabel);
        Controls.Add(_fontNameValueLabel);
        Controls.Add(fontSizeLabel);
        Controls.Add(_fontSizeValueLabel);
        Controls.Add(toolsPanel);
        Controls.Add(_grid);
        Controls.Add(outputLabel);
        Controls.Add(_outputBox);
        Controls.Add(previewTextLabel);
        Controls.Add(_previewTextBox);
        Controls.Add(previewLabel);
        Controls.Add(_previewPanel);
        Controls.Add(clearButton);
        Controls.Add(exportButton);
        Controls.Add(previousButton);
        Controls.Add(nextButton);
        Controls.Add(statusStrip);

        SelectCharacter('A');
        UpdateInterface("Ready");
    }

    private MenuStrip CreateMenu()
    {
        MenuStrip menu = new();

        ToolStripMenuItem fileMenu = new("File");
        ToolStripMenuItem newItem = new("New...")
        {
            ShortcutKeys = Keys.Control | Keys.N
        };
        ToolStripMenuItem openItem = new("Open...")
        {
            ShortcutKeys = Keys.Control | Keys.O
        };
        ToolStripMenuItem saveItem = new("Save")
        {
            ShortcutKeys = Keys.Control | Keys.S
        };
        ToolStripMenuItem saveAsItem = new("Save As...")
        {
            ShortcutKeys = Keys.Control | Keys.Shift | Keys.S
        };
        ToolStripMenuItem importItem = new("Import BDF...");
        ToolStripMenuItem exitItem = new("Exit");

        newItem.Click += NewMenu_Click;
        openItem.Click += OpenMenu_Click;
        saveItem.Click += SaveMenu_Click;
        saveAsItem.Click += SaveAsMenu_Click;
        importItem.Click += ImportBdfMenu_Click;
        exitItem.Click += (_, _) => Close();

        fileMenu.DropDownItems.Add(newItem);
        fileMenu.DropDownItems.Add(openItem);
        fileMenu.DropDownItems.Add(new ToolStripSeparator());
        fileMenu.DropDownItems.Add(saveItem);
        fileMenu.DropDownItems.Add(saveAsItem);
        fileMenu.DropDownItems.Add(new ToolStripSeparator());
        fileMenu.DropDownItems.Add(importItem);
        fileMenu.DropDownItems.Add(new ToolStripSeparator());
        fileMenu.DropDownItems.Add(exitItem);

        ToolStripMenuItem editMenu = new("Edit");

        ToolStripMenuItem copyItem = new("Copy Glyph")
        {
            ShortcutKeys = Keys.Control | Keys.C
        };
        ToolStripMenuItem pasteItem = new("Paste Glyph")
        {
            ShortcutKeys = Keys.Control | Keys.V
        };
        ToolStripMenuItem invertItem = new("Invert");
        ToolStripMenuItem mirrorHItem = new("Mirror Horizontal");
        ToolStripMenuItem mirrorVItem = new("Mirror Vertical");
        ToolStripMenuItem rotateItem = new("Rotate Clockwise");

        copyItem.Click += (_, _) => CopyGlyph();
        pasteItem.Click += (_, _) => PasteGlyph();
        invertItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.Invert, "Glyph inverted");
        mirrorHItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.MirrorHorizontal, "Glyph mirrored horizontally");
        mirrorVItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.MirrorVertical, "Glyph mirrored vertically");
        rotateItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.RotateClockwise, "Glyph rotated");

        editMenu.DropDownItems.Add(copyItem);
        editMenu.DropDownItems.Add(pasteItem);
        editMenu.DropDownItems.Add(new ToolStripSeparator());
        editMenu.DropDownItems.Add(invertItem);
        editMenu.DropDownItems.Add(mirrorHItem);
        editMenu.DropDownItems.Add(mirrorVItem);
        editMenu.DropDownItems.Add(rotateItem);

        ToolStripMenuItem helpMenu = new("Help");
        ToolStripMenuItem aboutItem = new("About");
        aboutItem.Click += (_, _) => MessageBox.Show(
            "BLACKBLOX Font Editor\n\nBitmap font editor for the BLACKBLOX SDK.",
            "About",
            MessageBoxButtons.OK,
            MessageBoxIcon.Information);
        helpMenu.DropDownItems.Add(aboutItem);

        menu.Items.Add(fileMenu);
        menu.Items.Add(editMenu);
        menu.Items.Add(helpMenu);
        return menu;
    }

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

    private void PopulateCharacterList()
    {
        _characterList.Items.Clear();

        for (int code = 32; code <= 126; code++)
        {
            char character = (char)code;
            string description = character == ' ' ? "Space" : character.ToString();
            _characterList.Items.Add(
                new CharacterListItem(character, $"{code,3}   {description}"));
        }
    }

    private void NewMenu_Click(object? sender, EventArgs e)
    {
        if (!ConfirmDiscardChanges())
            return;

        using NewFontForm dialog = new(_fontName, _font.Width, _font.Height);
        if (dialog.ShowDialog(this) != DialogResult.OK)
            return;

        _font = new FontResource(dialog.SelectedWidth, dialog.SelectedHeight);
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
            _grid.SetGlyph(_font.GetGlyph(CurrentCharacter));
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
        operation(_font.GetGlyph(CurrentCharacter));
        _grid.Invalidate();
        _previewPanel.Invalidate();
        _outputBox.Clear();
        _isDirty = true;
        UpdateInterface(status);
    }

    private void CharacterList_SelectedIndexChanged(object? sender, EventArgs e)
    {
        if (_updatingCharacterSelection)
            return;

        if (_characterList.SelectedItem is CharacterListItem item)
            SelectCharacter(item.Character);
    }

    private void CharacterBox_TextChanged(object? sender, EventArgs e)
    {
        if (_updatingCharacterSelection || _characterBox.Text.Length != 1)
            return;

        SelectCharacter(_characterBox.Text[0]);
    }

    private void CharacterBox_KeyDown(object? sender, KeyEventArgs e)
    {
        if (e.KeyCode != Keys.Enter)
            return;

        e.SuppressKeyPress = true;
        _grid.Focus();
    }

    private void Grid_PixelChanged(object? sender, EventArgs e)
    {
        _isDirty = true;
        _outputBox.Clear();
        _previewPanel.Invalidate();
        UpdateInterface("Glyph modified");
    }

    private void NextButton_Click(object? sender, EventArgs e)
    {
        char character = CurrentCharacter >= '~'
            ? ' '
            : (char)(CurrentCharacter + 1);

        SelectCharacter(character);
    }

    private void PreviousButton_Click(object? sender, EventArgs e)
    {
        char character = CurrentCharacter <= ' '
            ? '~'
            : (char)(CurrentCharacter - 1);

        SelectCharacter(character);
    }

    private void SelectCharacter(char character)
    {
        if (character < ' ' || character > '~')
            return;

        _updatingCharacterSelection = true;

        try
        {
            _characterBox.Text = character.ToString();

            for (int i = 0; i < _characterList.Items.Count; i++)
            {
                if (_characterList.Items[i] is CharacterListItem item &&
                    item.Character == character)
                {
                    _characterList.SelectedIndex = i;
                    break;
                }
            }

            _grid.SetGlyph(_font.GetGlyph(character));
            _outputBox.Clear();
            UpdateInterface();
        }
        finally
        {
            _updatingCharacterSelection = false;
        }
    }

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

    private bool ConfirmDiscardChanges()
    {
        if (!_isDirty)
            return true;

        DialogResult result = MessageBox.Show(
            "The current font contains unsaved changes.\n\nSave before continuing?",
            "Unsaved Changes",
            MessageBoxButtons.YesNoCancel,
            MessageBoxIcon.Warning);

        if (result == DialogResult.Cancel)
            return false;

        if (result == DialogResult.No)
            return true;

        SaveMenu_Click(null, EventArgs.Empty);
        return !_isDirty;
    }

    private void UpdateInterface(string? status = null)
    {
        _asciiValueLabel.Text = ((int)CurrentCharacter).ToString();
        _fontNameValueLabel.Text = _fontName;
        _fontSizeValueLabel.Text = $"{_font.Width} x {_font.Height}";

        string dirtyMarker = _isDirty ? "*" : string.Empty;
        Text = $"{dirtyMarker}{_fontName} - BLACKBLOX Font Editor";

        _statusLabel.Text = status ??
            $"Character: {GetCharacterDescription(CurrentCharacter)}   ASCII: {(int)CurrentCharacter}   Size: {_font.Width} x {_font.Height}";

        _previewPanel.Invalidate();
    }

    private static string GetCharacterDescription(char character)
    {
        return character == ' ' ? "Space" : character.ToString();
    }

    private char CurrentCharacter =>
        _characterBox.Text.Length == 1 ? _characterBox.Text[0] : 'A';
}