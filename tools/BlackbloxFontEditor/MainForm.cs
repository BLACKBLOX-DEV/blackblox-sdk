using BlackbloxFontEditor.Controls;
using BlackbloxFontEditor.Generators;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor;

public partial class MainForm : Form
{
    private readonly PixelGrid _grid;
    private readonly TextBox _characterBox;
    private readonly Button _clearButton;
    private readonly Button _generateButton;
    private readonly TextBox _outputBox;
    private readonly FontResource _font;

    public MainForm()
    {
        InitializeComponent();

   

        Text = "BLACKBLOX Font Editor";
        ClientSize = new Size(900, 650);
        StartPosition = FormStartPosition.CenterScreen;

        _characterBox = new TextBox
        {
            Left = 120,
            Top = 20,
            Width = 50,
            Text = "A",
            MaxLength = 1
        };

        Label characterLabel = new Label
        {
            Left = 20,
            Top = 24,
            Width = 90,
            Text = "Character:"
        };

        _font = new FontResource();

        _grid = new PixelGrid
        {
            Left = 20,
            Top = 60,
            Width = 350,
            Height = 490
        };

        _grid.SetGlyph(_font.GetGlyph('A'));

        _characterBox.TextChanged += CharacterBox_TextChanged;

        _clearButton = new Button
        {
            Left = 20,
            Top = 570,
            Width = 100,
            Height = 35,
            Text = "Clear"
        };

        _generateButton = new Button
        {
            Left = 130,
            Top = 570,
            Width = 120,
            Height = 35,
            Text = "Generate C++"
        };

        _outputBox = new TextBox
        {
            Left = 400,
            Top = 60,
            Width = 470,
            Height = 545,
            Multiline = true,
            ScrollBars = ScrollBars.Both,
            Font = new Font("Consolas", 10),
            WordWrap = false
        };

        _clearButton.Click += ClearButton_Click;
        _generateButton.Click += GenerateButton_Click;

        Controls.Add(characterLabel);
        Controls.Add(_characterBox);
        Controls.Add(_grid);
        Controls.Add(_clearButton);
        Controls.Add(_generateButton);
        Controls.Add(_outputBox);
    }

    private void ClearButton_Click(object? sender, EventArgs e)
    {
        _font.GetGlyph(_characterBox.Text[0]).Clear();

        _grid.Invalidate();

        _outputBox.Clear();
    }

    private void GenerateButton_Click(object? sender, EventArgs e)
{
    string character = _characterBox.Text.Trim();

    if (string.IsNullOrEmpty(character))
    {
        MessageBox.Show(
            "Vpiši znak.",
            "BLACKBLOX Font Editor",
            MessageBoxButtons.OK,
            MessageBoxIcon.Warning);

        return;
    }

    string name = $"font5x7_{character[0]}";

    _outputBox.Text = CppGenerator.Generate(
        _grid.Glyph,
        name);
}
private void CharacterBox_TextChanged(object? sender, EventArgs e)
{
    if (_characterBox.Text.Length != 1)
        return;

    _grid.SetGlyph(_font.GetGlyph(_characterBox.Text[0]));
}
}