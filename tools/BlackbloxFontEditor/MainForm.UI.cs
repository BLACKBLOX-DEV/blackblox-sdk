using BlackbloxFontEditor.Controls;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor;

public partial class MainForm
{
    private Label _progressLabel = null!;
    private Button _nextMissingButton = null!;

    private Label _glyphWidthLabel = null!;
    private Button _autoWidthButton = null!;
    private Button _autoWidthAllButton = null!;

    private void InitializeUserInterface()
    {
        Text = "BLACKBLOX Font Editor 1.0";
        ClientSize = new Size(1240, 800);
        MinimumSize = new Size(1080, 720);
        StartPosition = FormStartPosition.CenterScreen;
        KeyPreview = true;

        MenuStrip menu = CreateMenu();
        MainMenuStrip = menu;
        Controls.Add(menu);

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
            Anchor =
                AnchorStyles.Top |
                AnchorStyles.Bottom |
                AnchorStyles.Left
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

        _progressLabel = new Label
        {
            Left = 830,
            Top = 47,
            AutoSize = true,
            Text = "Completed: 0 / 95"
        };

        _nextMissingButton = new Button
        {
            Left = 1000,
            Top = 40,
            Width = 120,
            Height = 29,
            Text = "Next Missing",
            UseVisualStyleBackColor = true,
            Anchor =
                AnchorStyles.Top |
                AnchorStyles.Right
        };

        FlowLayoutPanel toolsPanel = CreateToolsPanel();

        _grid = new PixelGrid
        {
            Left = 175,
            Top = 120,
            Width = 430,
            Height = 560,
            Anchor =
                AnchorStyles.Top |
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

        _grid.SetGlyph(_font.GetGlyph('A'));

        _grid.PixelChanged += Grid_PixelChanged;
        _grid.PixelChanged += (_, _) =>
        {
            UpdateGlyphWidthLabel();
            _previewPanel.Invalidate();
        };

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
            Anchor =
                AnchorStyles.Top |
                AnchorStyles.Left |
                AnchorStyles.Right
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
            Anchor =
                AnchorStyles.Top |
                AnchorStyles.Left |
                AnchorStyles.Right
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
            Anchor =
                AnchorStyles.Top |
                AnchorStyles.Bottom |
                AnchorStyles.Left |
                AnchorStyles.Right
        };

        _previewPanel.Paint += PreviewPanel_Paint;

        Button clearButton = new()
        {
            Left = 175,
            Top = 700,
            Width = 90,
            Height = 35,
            Text = "Clear",
            Anchor =
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

        Button exportButton = new()
        {
            Left = 275,
            Top = 700,
            Width = 120,
            Height = 35,
            Text = "Export C++",
            Anchor =
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

        Button previousButton = new()
        {
            Left = 415,
            Top = 700,
            Width = 50,
            Height = 35,
            Text = "◀",
            Anchor =
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

        Button nextButton = new()
        {
            Left = 475,
            Top = 700,
            Width = 50,
            Height = 35,
            Text = "▶",
            Anchor =
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

       _glyphWidthLabel = new Label
        {
            Left = 630,
            Top = 709,
            Width = 145,
            Height = 23,
            Text = "Glyph width: 5 / 5",
            TextAlign = ContentAlignment.MiddleLeft,
            Anchor =
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

        _autoWidthButton = new Button
        {
            Left = 785,
            Top = 700,
            Width = 115,
            Height = 35,
            Text = "Auto Width",
            UseVisualStyleBackColor = true,
            Anchor =
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

        _autoWidthAllButton = new Button
        {
            Left = 910,
            Top = 700,
            Width = 140,
            Height = 35,
            Text = "Auto Width All",
            UseVisualStyleBackColor = true,
            Anchor =
                AnchorStyles.Bottom |
                AnchorStyles.Left
        };

        StatusStrip statusStrip = new();

        _statusLabel = new ToolStripStatusLabel
        {
            Spring = true,
            TextAlign = ContentAlignment.MiddleLeft
        };

        statusStrip.Items.Add(_statusLabel);

        _characterList.SelectedIndexChanged +=
            CharacterList_SelectedIndexChanged;

        
        _characterBox.TextChanged += CharacterBox_TextChanged;

       

        _characterBox.KeyDown += CharacterBox_KeyDown;

        _previewTextBox.TextChanged +=
            (_, _) => _previewPanel.Invalidate();

        clearButton.Click += (_, _) =>
        {
            ApplyGlyphOperation(
                glyph => glyph.Clear(),
                "Glyph cleared");

            UpdateGlyphWidthLabel();
            _previewPanel.Invalidate();
        };

        exportButton.Click += ExportButton_Click;
        previousButton.Click += PreviousButton_Click;
        nextButton.Click += NextButton_Click;

        _autoWidthButton.Click += AutoWidthButton_Click;
        _autoWidthAllButton.Click += AutoWidthAllButton_Click;

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
        Controls.Add(_progressLabel);
        Controls.Add(_nextMissingButton);
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
        Controls.Add(_glyphWidthLabel);
        Controls.Add(_autoWidthButton);
        Controls.Add(_autoWidthAllButton);
        Controls.Add(statusStrip);

        UpdateGlyphWidthLabel();
    }

    private void PopulateCharacterList()
    {
        _characterList.Items.Clear();

        for (int code = 32; code <= 126; code++)
        {
            char character = (char)code;

            string description =
                character == ' '
                    ? "Space"
                    : character.ToString();

            _characterList.Items.Add(
                new CharacterListItem(
                    character,
                    $"{code,3}   {description}"));
        }
    }

    private void AutoWidthButton_Click(
        object? sender,
        EventArgs e)
    {
        Glyph? glyph = _grid.Glyph;

        if (glyph is null)
            return;

        glyph.CalculateDisplayWidth();

        UpdateGlyphWidthLabel();
        _previewPanel.Invalidate();

        _statusLabel.Text =
            $"Glyph width calculated: {glyph.DisplayWidth}";
    }

    private void AutoWidthAllButton_Click(
        object? sender,
        EventArgs e)
    {
        _font.CalculateAllDisplayWidths();

        UpdateGlyphWidthLabel();
        _previewPanel.Invalidate();

        _statusLabel.Text =
            "Widths calculated for all glyphs";
    }

    private void UpdateGlyphWidthLabel()
    {
        if (_glyphWidthLabel is null)
            return;

        Glyph? glyph = _grid?.Glyph;

        if (glyph is null)
        {
            _glyphWidthLabel.Text = "Glyph width: -";
            return;
        }

        _glyphWidthLabel.Text =
            $"Glyph width: {glyph.DisplayWidth} / {glyph.Width}";
    }
}
