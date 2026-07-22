using BlackbloxFontEditor.Editing;

namespace BlackbloxFontEditor;

public partial class MainForm
{
    private MenuStrip CreateMenu()
    {
        MenuStrip menu = new();

        ToolStripMenuItem fileMenu = new("File");
        ToolStripMenuItem newItem = new("New...")
        {
            ShortcutKeys = Keys.Control | Keys.N
        };
        ToolStripMenuItem openItem = new("Open...")
        {
            ShortcutKeys = Keys.Control | Keys.O
        };
        ToolStripMenuItem saveItem = new("Save")
        {
            ShortcutKeys = Keys.Control | Keys.S
        };
        ToolStripMenuItem saveAsItem = new("Save As...")
        {
            ShortcutKeys = Keys.Control | Keys.Shift | Keys.S
        };
        ToolStripMenuItem importItem = new("Import BDF...");
        ToolStripMenuItem exitItem = new("Exit");

        newItem.Click += NewMenu_Click;
        openItem.Click += OpenMenu_Click;
        saveItem.Click += SaveMenu_Click;
        saveAsItem.Click += SaveAsMenu_Click;
        importItem.Click += ImportBdfMenu_Click;
        exitItem.Click += (_, _) => Close();

        fileMenu.DropDownItems.Add(newItem);
        fileMenu.DropDownItems.Add(openItem);
        fileMenu.DropDownItems.Add(new ToolStripSeparator());
        fileMenu.DropDownItems.Add(saveItem);
        fileMenu.DropDownItems.Add(saveAsItem);
        fileMenu.DropDownItems.Add(new ToolStripSeparator());
        fileMenu.DropDownItems.Add(importItem);
        fileMenu.DropDownItems.Add(new ToolStripSeparator());
        fileMenu.DropDownItems.Add(exitItem);

        ToolStripMenuItem editMenu = new("Edit");

        ToolStripMenuItem undoItem = new("Undo")
        {
            ShortcutKeys = Keys.Control | Keys.Z
        };
        ToolStripMenuItem redoItem = new("Redo")
        {
            ShortcutKeys = Keys.Control | Keys.Y
        };
        ToolStripMenuItem copyItem = new("Copy Glyph")
        {
            ShortcutKeys = Keys.Control | Keys.C
        };
        ToolStripMenuItem pasteItem = new("Paste Glyph")
        {
            ShortcutKeys = Keys.Control | Keys.V
        };
        ToolStripMenuItem invertItem = new("Invert");
        ToolStripMenuItem mirrorHItem = new("Mirror Horizontal");
        ToolStripMenuItem mirrorVItem = new("Mirror Vertical");
        ToolStripMenuItem rotateItem = new("Rotate Clockwise");

        undoItem.Click += (_, _) => UndoGlyph();
        redoItem.Click += (_, _) => RedoGlyph();
        copyItem.Click += (_, _) => CopyGlyph();
        pasteItem.Click += (_, _) => PasteGlyph();
        invertItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.Invert, "Glyph inverted");
        mirrorHItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.MirrorHorizontal, "Glyph mirrored horizontally");
        mirrorVItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.MirrorVertical, "Glyph mirrored vertically");
        rotateItem.Click += (_, _) => ApplyGlyphOperation(BitmapEditor.RotateClockwise, "Glyph rotated");

        editMenu.DropDownItems.Add(undoItem);
        editMenu.DropDownItems.Add(redoItem);
        editMenu.DropDownItems.Add(new ToolStripSeparator());
        editMenu.DropDownItems.Add(copyItem);
        editMenu.DropDownItems.Add(pasteItem);
        editMenu.DropDownItems.Add(new ToolStripSeparator());
        editMenu.DropDownItems.Add(invertItem);
        editMenu.DropDownItems.Add(mirrorHItem);
        editMenu.DropDownItems.Add(mirrorVItem);
        editMenu.DropDownItems.Add(rotateItem);

        ToolStripMenuItem helpMenu = new("Help");
        ToolStripMenuItem aboutItem = new("About");
        aboutItem.Click += (_, _) => MessageBox.Show(
            "BLACKBLOX Font Editor\n\nBitmap font editor for the BLACKBLOX SDK.",
            "About",
            MessageBoxButtons.OK,
            MessageBoxIcon.Information);
        helpMenu.DropDownItems.Add(aboutItem);

        menu.Items.Add(fileMenu);
        menu.Items.Add(editMenu);
        menu.Items.Add(helpMenu);
        return menu;
    }
}
