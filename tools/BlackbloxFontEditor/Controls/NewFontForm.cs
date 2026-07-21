namespace BlackbloxFontEditor;

public sealed class NewFontForm : Form
{
    private readonly TextBox _nameBox;
    private readonly NumericUpDown _widthBox;
    private readonly NumericUpDown _heightBox;

    public string FontName => string.IsNullOrWhiteSpace(_nameBox.Text)
        ? $"font{SelectedWidth}x{SelectedHeight}"
        : _nameBox.Text.Trim();

    public int SelectedWidth => (int)_widthBox.Value;
    public int SelectedHeight => (int)_heightBox.Value;

    public NewFontForm(string currentName, int currentWidth, int currentHeight)
    {
        Text = "New Font";
        ClientSize = new Size(330, 190);
        FormBorderStyle = FormBorderStyle.FixedDialog;
        MaximizeBox = false;
        MinimizeBox = false;
        ShowInTaskbar = false;
        StartPosition = FormStartPosition.CenterParent;

        Label nameLabel = new()
        {
            Left = 20,
            Top = 24,
            Width = 80,
            Text = "Name:"
        };

        _nameBox = new TextBox
        {
            Left = 110,
            Top = 20,
            Width = 190,
            Text = currentName == "Untitled" ? string.Empty : currentName
        };

        Label widthLabel = new()
        {
            Left = 20,
            Top = 65,
            Width = 80,
            Text = "Width:"
        };

        _widthBox = new NumericUpDown
        {
            Left = 110,
            Top = 61,
            Width = 80,
            Minimum = 1,
            Maximum = 64,
            Value = Math.Clamp(currentWidth, 1, 64)
        };

        Label heightLabel = new()
        {
            Left = 20,
            Top = 104,
            Width = 80,
            Text = "Height:"
        };

        _heightBox = new NumericUpDown
        {
            Left = 110,
            Top = 100,
            Width = 80,
            Minimum = 1,
            Maximum = 64,
            Value = Math.Clamp(currentHeight, 1, 64)
        };

        Button okButton = new()
        {
            Left = 134,
            Top = 145,
            Width = 80,
            Text = "OK",
            DialogResult = DialogResult.OK
        };

        Button cancelButton = new()
        {
            Left = 220,
            Top = 145,
            Width = 80,
            Text = "Cancel",
            DialogResult = DialogResult.Cancel
        };

        AcceptButton = okButton;
        CancelButton = cancelButton;

        Controls.Add(nameLabel);
        Controls.Add(_nameBox);
        Controls.Add(widthLabel);
        Controls.Add(_widthBox);
        Controls.Add(heightLabel);
        Controls.Add(_heightBox);
        Controls.Add(okButton);
        Controls.Add(cancelButton);
    }
}