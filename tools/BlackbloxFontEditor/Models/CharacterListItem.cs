namespace BlackbloxFontEditor.Models;

public sealed class CharacterListItem
{
    public char Character { get; }
    public string DisplayText { get; }

    public CharacterListItem(char character, string displayText)
    {
        Character = character;
        DisplayText = displayText;
    }

    public override string ToString() => DisplayText;
}