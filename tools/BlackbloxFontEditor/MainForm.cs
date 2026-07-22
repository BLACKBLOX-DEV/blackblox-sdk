using BlackbloxFontEditor.Controls;
using BlackbloxFontEditor.Editing;
using BlackbloxFontEditor.Models;

namespace BlackbloxFontEditor;

public partial class MainForm : Form
{
    private PixelGrid _grid = null!;
    private TextBox _characterBox = null!;
    private Label _asciiValueLabel = null!;
    private Label _fontNameValueLabel = null!;
    private Label _fontSizeValueLabel = null!;
    private TextBox _outputBox = null!;
    private ToolStripStatusLabel _statusLabel = null!;
    private ListBox _characterList = null!;
    private TextBox _previewTextBox = null!;
    private Panel _previewPanel = null!;

    private FontResource _font;
    private string? _currentFileName;
    private string _fontName = "Untitled";
    private bool _isDirty;
    private bool _updatingCharacterSelection;
    private bool[,]? _clipboardPixels;
    private readonly Dictionary<char, GlyphHistory> _histories = new();
    private bool[,]? _lastGlyphSnapshot;

    public MainForm()
    {
        InitializeComponent();
        _font = new FontResource(5, 7);
        InitializeUserInterface();
        SelectCharacter('A');
        UpdateInterface("Ready");
    }
}
