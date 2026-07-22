using System.Text.Json;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Persistence;

public static class FontFileSerializer
{
    private sealed class FontFileData
    {
        public string Name { get; set; } = "Untitled";

        public int Width { get; set; }

        public int Height { get; set; }

        public Dictionary<int, string[]> Glyphs { get; set; } = new();
    }

    public static void Save(
        string fileName,
        FontResource font,
        string fontName)
    {
        FontFileData data = new()
        {
            Name = fontName,
            Width = font.Width,
            Height = font.Height
        };

        foreach (KeyValuePair<char, Glyph> item in font.Glyphs)
        {
            string[] rows = new string[font.Height];

            for (int y = 0; y < font.Height; y++)
            {
                char[] pixels = new char[font.Width];

                for (int x = 0; x < font.Width; x++)
                {
                    pixels[x] = item.Value.Pixels[x, y]
                        ? '1'
                        : '0';
                }

                rows[y] = new string(pixels);
            }

            data.Glyphs[(int)item.Key] = rows;
        }

        JsonSerializerOptions options = new()
        {
            WriteIndented = true
        };

        string json = JsonSerializer.Serialize(
            data,
            options);

        File.WriteAllText(
            fileName,
            json);
    }

    public static FontResource Load(
        string fileName,
        out string fontName)
    {
        string json = File.ReadAllText(fileName);

        FontFileData? data =
            JsonSerializer.Deserialize<FontFileData>(json);

        if (data is null)
        {
            throw new InvalidDataException(
                "Datoteka ne vsebuje veljavnega fonta.");
        }

        if (data.Width <= 0 || data.Height <= 0)
        {
            throw new InvalidDataException(
                "Dimenzije fonta niso veljavne.");
        }

        FontResource font = new(
            data.Width,
            data.Height);

        foreach (KeyValuePair<int, string[]> item in data.Glyphs)
        {
            if (item.Key < char.MinValue ||
                item.Key > char.MaxValue)
            {
                continue;
            }

            Glyph glyph =
                font.GetGlyph((char)item.Key);

            string[] rows = item.Value;

            for (int y = 0;
                 y < font.Height && y < rows.Length;
                 y++)
            {
                string row = rows[y];

                for (int x = 0;
                     x < font.Width && x < row.Length;
                     x++)
                {
                    glyph.Pixels[x, y] =
                        row[x] == '1';
                }
            }
        }

        fontName = string.IsNullOrWhiteSpace(data.Name)
            ? "Untitled"
            : data.Name;

        return font;
    }
}