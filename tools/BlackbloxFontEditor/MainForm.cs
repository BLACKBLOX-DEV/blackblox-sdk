using BlackbloxFontEditor.Controls;

namespace BlackbloxFontEditor;

public partial class MainForm : Form
{
    private readonly PixelGrid _grid;
    private readonly TextBox _characterBox;
    private readonly Button _clearButton;
    private readonly Button _generateButton;
    private readonly TextBox _outputBox;

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

        _grid = new PixelGrid
        {
            Left = 20,
            Top = 60,
            Width = 350,
            Height = 490
        };

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
        _grid.Clear();
        _outputBox.Clear();
    }

    private void GenerateButton_Click(object? sender, EventArgs e)
    {
        _outputBox.Text = "Generator še ni dodan.";
    }
}