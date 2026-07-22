namespace BlackbloxFontEditor;

public partial class MainForm
{
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
