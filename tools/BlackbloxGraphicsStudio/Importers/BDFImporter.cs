using System.Globalization;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor.Importers;

public static class BdfImporter
{
    public static int Import(
        string fileName,
        FontResource font)
    {
        string[] lines = File.ReadAllLines(fileName);

        int importedGlyphs = 0;

        int encoding = -1;

        int bitmapWidth = 0;
        int bitmapHeight = 0;
        int bitmapXOffset = 0;
        int bitmapYOffset = 0;

        bool insideCharacter = false;
        bool readingBitmap = false;

        List<string> bitmapRows = new();

        foreach (string rawLine in lines)
        {
            string line = rawLine.Trim();

            if (line.StartsWith("STARTCHAR "))
            {
                insideCharacter = true;
                readingBitmap = false;

                encoding = -1;

                bitmapWidth = 0;
                bitmapHeight = 0;
                bitmapXOffset = 0;
                bitmapYOffset = 0;

                bitmapRows.Clear();

                continue;
            }

            if (!insideCharacter)
                continue;

            if (line.StartsWith("ENCODING "))
            {
                string value =
                    line["ENCODING ".Length..];

                int.TryParse(
                    value,
                    NumberStyles.Integer,
                    CultureInfo.InvariantCulture,
                    out encoding);

                continue;
            }

            if (line.StartsWith("BBX "))
            {
                ParseBoundingBox(
                    line,
                    out bitmapWidth,
                    out bitmapHeight,
                    out bitmapXOffset,
                    out bitmapYOffset);

                continue;
            }

            if (line == "BITMAP")
            {
                readingBitmap = true;
                bitmapRows.Clear();

                continue;
            }

            if (line == "ENDCHAR")
            {
                if (encoding is >= 32 and <= 126)
                {
                    ImportGlyph(
                        font,
                        (char)encoding,
                        bitmapRows,
                        bitmapWidth,
                        bitmapHeight,
                        bitmapXOffset,
                        bitmapYOffset);

                    importedGlyphs++;
                }

                insideCharacter = false;
                readingBitmap = false;

                continue;
            }

            if (readingBitmap && line.Length > 0)
            {
                bitmapRows.Add(line);
            }
        }

        return importedGlyphs;
    }

    private static void ParseBoundingBox(
        string line,
        out int width,
        out int height,
        out int xOffset,
        out int yOffset)
    {
        width = 0;
        height = 0;
        xOffset = 0;
        yOffset = 0;

        string[] parts = line.Split(
            ' ',
            StringSplitOptions.RemoveEmptyEntries);

        // BBX width height xOffset yOffset
        if (parts.Length < 5)
            return;

        int.TryParse(
            parts[1],
            NumberStyles.Integer,
            CultureInfo.InvariantCulture,
            out width);

        int.TryParse(
            parts[2],
            NumberStyles.Integer,
            CultureInfo.InvariantCulture,
            out height);

        int.TryParse(
            parts[3],
            NumberStyles.Integer,
            CultureInfo.InvariantCulture,
            out xOffset);

        int.TryParse(
            parts[4],
            NumberStyles.Integer,
            CultureInfo.InvariantCulture,
            out yOffset);
    }

    private static void ImportGlyph(
        FontResource font,
        char character,
        IReadOnlyList<string> bitmapRows,
        int bitmapWidth,
        int bitmapHeight,
        int bitmapXOffset,
        int bitmapYOffset)
    {
        Glyph glyph = font.GetGlyph(character);
        glyph.Clear();

        if (bitmapWidth <= 0 ||
            bitmapHeight <= 0 ||
            bitmapRows.Count == 0)
        {
            return;
        }

        int rowsToRead = Math.Min(
            bitmapHeight,
            bitmapRows.Count);

        /*
         * Za zdaj znak uvažamo brez skaliranja,
         * obrezovanja ali centriranja.
         *
         * BDF bitmap je zapisan od zgornje proti
         * spodnji vrstici.
         *
         * xOffset upoštevamo horizontalno.
         *
         * yOffset namenoma ne vpliva na položaj,
         * ker želimo bitmap dobiti v editor v
         * čim bolj neposredni obliki in ga nato
         * po potrebi ročno popraviti.
         */
        int targetOriginX = bitmapXOffset;
        int targetOriginY = 0;

        for (int sourceY = 0;
             sourceY < rowsToRead;
             sourceY++)
        {
            string hexRow = bitmapRows[sourceY];

            if (!ulong.TryParse(
                    hexRow,
                    NumberStyles.HexNumber,
                    CultureInfo.InvariantCulture,
                    out ulong rowValue))
            {
                continue;
            }

            int storedBitCount =
                hexRow.Length * 4;

            int targetY =
                targetOriginY + sourceY;

            if (targetY < 0 ||
                targetY >= glyph.Height)
            {
                continue;
            }

            for (int sourceX = 0;
                 sourceX < bitmapWidth;
                 sourceX++)
            {
                int bitPosition =
                    storedBitCount - 1 - sourceX;

                if (bitPosition < 0 ||
                    bitPosition >= 64)
                {
                    continue;
                }

                bool pixelOn =
                    (rowValue &
                     (1UL << bitPosition)) != 0;

                if (!pixelOn)
                    continue;

                int targetX =
                    targetOriginX + sourceX;

                if (targetX < 0 ||
                    targetX >= glyph.Width)
                {
                    continue;
                }

                glyph.Pixels[targetX, targetY] = true;
            }
        }
    }
}