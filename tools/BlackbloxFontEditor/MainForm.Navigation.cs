using BlackbloxFontEditor.Editing;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor;

public partial class MainForm
{
    private const char FirstCharacter = ' ';
    private const char LastCharacter = '~';
    private const int CharacterCount = LastCharacter - FirstCharacter + 1;

    private bool _nextMissingHandlerConnected;

    private void CharacterList_SelectedIndexChanged(
        object? sender,
        EventArgs e)
    {
        if (_updatingCharacterSelection)
            return;

        if (_characterList.SelectedItem is CharacterListItem item)
            SelectCharacter(item.Character);
    }

    private void CharacterBox_TextChanged(
        object? sender,
        EventArgs e)
    {
        if (_updatingCharacterSelection ||
            _characterBox.Text.Length != 1)
        {
            return;
        }

        SelectCharacter(_characterBox.Text[0]);
    }

    private void CharacterBox_KeyDown(
        object? sender,
        KeyEventArgs e)
    {
        if (e.KeyCode != Keys.Enter)
            return;

        e.SuppressKeyPress = true;
        _grid.Focus();
    }

    private void Grid_PixelChanged(
        object? sender,
        EventArgs e)
    {
        Glyph glyph = _font.GetGlyph(CurrentCharacter);

        if (_lastGlyphSnapshot is not null)
        {
            GetHistory(CurrentCharacter)
                .PushSnapshot(_lastGlyphSnapshot);
        }

        _lastGlyphSnapshot = BitmapEditor.CopyPixels(glyph);
        _isDirty = true;

        _outputBox.Clear();
        _previewPanel.Invalidate();

        RefreshGlyphProgress();
        UpdateInterface("Glyph modified");
    }

    private void NextButton_Click(
        object? sender,
        EventArgs e)
    {
        char character = CurrentCharacter >= LastCharacter
            ? FirstCharacter
            : (char)(CurrentCharacter + 1);

        SelectCharacter(character);
    }

    private void PreviousButton_Click(
        object? sender,
        EventArgs e)
    {
        char character = CurrentCharacter <= FirstCharacter
            ? LastCharacter
            : (char)(CurrentCharacter - 1);

        SelectCharacter(character);
    }

    private void NextMissingButton_Click(
        object? sender,
        EventArgs e)
    {
        char startCharacter = CurrentCharacter;

        for (int offset = 1; offset <= CharacterCount; offset++)
        {
            int code =
                FirstCharacter +
                ((startCharacter - FirstCharacter + offset) %
                 CharacterCount);

            char character = (char)code;

            if (!IsGlyphCompleted(character))
            {
                SelectCharacter(character);
                UpdateInterface(
                    $"Next missing glyph: {FormatCharacter(character)}");

                return;
            }
        }

        UpdateInterface("All glyphs are completed");
    }

    private void SelectCharacter(char character)
    {
        if (character < FirstCharacter ||
            character > LastCharacter)
        {
            return;
        }

        ConnectNextMissingHandler();

        _updatingCharacterSelection = true;

        try
        {
            _characterBox.Text = character.ToString();

            RefreshCharacterList(character);

            Glyph glyph = _font.GetGlyph(character);

            _grid.SetGlyph(glyph);

            _lastGlyphSnapshot =
                BitmapEditor.CopyPixels(glyph);

            _outputBox.Clear();
            _previewPanel.Invalidate();

            UpdateProgressLabel();
            UpdateInterface();
        }
        finally
        {
            _updatingCharacterSelection = false;
        }
    }

    private void ConnectNextMissingHandler()
    {
        if (_nextMissingHandlerConnected)
            return;

        _nextMissingButton.Click += NextMissingButton_Click;
        _nextMissingHandlerConnected = true;
    }

    private void RefreshGlyphProgress()
    {
        char selectedCharacter = CurrentCharacter;

        _updatingCharacterSelection = true;

        try
        {
            RefreshCharacterList(selectedCharacter);
            UpdateProgressLabel();
        }
        finally
        {
            _updatingCharacterSelection = false;
        }
    }

    private void RefreshCharacterList(char selectedCharacter)
    {
        _characterList.BeginUpdate();

        try
        {
            _characterList.Items.Clear();

            int selectedIndex = -1;

            for (int code = FirstCharacter;
                 code <= LastCharacter;
                 code++)
            {
                char character = (char)code;

                bool completed =
                    IsGlyphCompleted(character);

                string status =
                    completed ? "✓" : "□";

                string description =
                    character == FirstCharacter
                        ? "Space"
                        : character.ToString();

                CharacterListItem item = new(
                    character,
                    $"{status} {code,3}   {description}");

                _characterList.Items.Add(item);

                if (character == selectedCharacter)
                {
                    selectedIndex =
                        _characterList.Items.Count - 1;
                }
            }

            if (selectedIndex >= 0)
                _characterList.SelectedIndex = selectedIndex;
        }
        finally
        {
            _characterList.EndUpdate();
        }
    }

    private void UpdateProgressLabel()
    {
        int completedCount = 0;

        for (int code = FirstCharacter;
             code <= LastCharacter;
             code++)
        {
            if (IsGlyphCompleted((char)code))
                completedCount++;
        }

        _progressLabel.Text =
            $"Completed: {completedCount} / {CharacterCount}";
    }

    private bool IsGlyphCompleted(char character)
    {
        Glyph glyph = _font.GetGlyph(character);
        bool[,] pixels = BitmapEditor.CopyPixels(glyph);

        for (int y = 0; y < pixels.GetLength(1); y++)
        {
            for (int x = 0; x < pixels.GetLength(0); x++)
            {
                if (pixels[x, y])
                    return true;
            }
        }

        return false;
    }

    private static string FormatCharacter(char character)
    {
        return character == FirstCharacter
            ? "Space"
            : character.ToString();
    }
}
