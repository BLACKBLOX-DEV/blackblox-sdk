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
    private readonly Button _nextButton;
    private readonly Button _previousButton;






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
        _characterBox.KeyDown += CharacterBox_KeyDown;

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

        _nextButton = new Button
        {
            Left = 320,
            Top = 570,
            Width = 50,
            Height = 35,
            Text = ">"
        };

        _previousButton = new Button
        {
            Left = 260,
            Top = 570,
            Width = 50,
            Height = 35,
            Text = "<"
        };

        _clearButton.Click += ClearButton_Click;
        _generateButton.Click += GenerateButton_Click;
        _nextButton.Click += NextButton_Click;
        _previousButton.Click += PreviousButton_Click;


        Controls.Add(characterLabel);
        Controls.Add(_characterBox);
        Controls.Add(_grid);
        Controls.Add(_clearButton);
        Controls.Add(_generateButton);
        Controls.Add(_outputBox);
        Controls.Add(_nextButton);
        Controls.Add(_previousButton);
    }

    private void ClearButton_Click(object? sender, EventArgs e)
    {
        _font.GetGlyph(CurrentCharacter).Clear();

        _grid.Invalidate();

        _outputBox.Clear();
    }

private void GenerateButton_Click(object? sender, EventArgs e)
{
    if (_characterBox.TextLength != 1)
        return;

    string name = $"font5x7_{CurrentCharacter}";

    if (_grid.Glyph is null)
        return;

    _outputBox.Text = CppGenerator.Generate(
        _grid.Glyph,
        name);

    _outputBox.SelectAll();
    _outputBox.Focus();
}
private void CharacterBox_TextChanged(object? sender, EventArgs e)
{
    if (_characterBox.Text.Length != 1)
        return;

    _grid.SetGlyph(_font.GetGlyph(_characterBox.Text[0]));
    _outputBox.Clear();
}

private void SelectCharacter(char c)
{
    if (_characterBox.Text == c.ToString())
        return;

    _characterBox.Text = c.ToString();
}
private void NextButton_Click(object? sender, EventArgs e)
{
    if (_characterBox.Text.Length != 1)
        return;

    char c = CurrentCharacter;

    c = (c >= '~') ? ' ' : (char)(c + 1);
        SelectCharacter(c);

        _characterBox.Focus();
}

private void PreviousButton_Click(object? sender, EventArgs e)
{
    if (_characterBox.Text.Length != 1)
        return;

    char c = CurrentCharacter;

    if (c > ' ')
        SelectCharacter(c);
        _characterBox.Focus();
}
private void CharacterBox_KeyDown(object? sender, KeyEventArgs e)
{
    if (e.KeyCode == Keys.Enter)
        GenerateButton_Click(null, EventArgs.Empty);
        _outputBox.SelectAll();
        _outputBox.Focus();
}
private char CurrentCharacter => _characterBox.Text[0];
}