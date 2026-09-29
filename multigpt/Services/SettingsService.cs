using System.IO;
using System.Text.Json;
using ChatGPTMulti.Models;

namespace ChatGPTMulti.Services;

public sealed class SettingsService(string path, AppLog log)
{
    private static readonly JsonSerializerOptions JsonOptions = new() { WriteIndented = true };
    public string? Warning { get; private set; }

    public IReadOnlyList<WindowSnapshot> Load()
    {
        Warning = null;
        try
        {
            if (!File.Exists(path)) return [new()];
            if (new FileInfo(path).Length > 1024 * 1024) throw new InvalidDataException();
            var settings = JsonSerializer.Deserialize<AppSettings>(File.ReadAllText(path));
            if (settings is not { Version: 1 or 2, Windows: not null }) throw new InvalidDataException();
            var windows = settings.Windows.Where(w => w is not null).Take(50)
                .Select(w => Sanitize(w!)).ToList();
            return windows.Count == 0 ? [new()] : windows;
        }
        catch (Exception ex) when (ex is IOException or InvalidDataException or UnauthorizedAccessException or JsonException or NotSupportedException)
        {
            log.Write("Settings could not be read; starting with default window.", ex);
            Warning = "Saved windows could not be read. A default window was opened.";
            return [new()];
        }
    }

    public bool Save(IEnumerable<WindowSnapshot> windows)
    {
        string temporary = path + ".tmp";
        try
        {
            Directory.CreateDirectory(Path.GetDirectoryName(path)!);
            var settings = new AppSettings { Windows = windows.Select(w => (WindowSnapshot?)Sanitize(w)).ToList() };
            File.WriteAllText(temporary, JsonSerializer.Serialize(settings, JsonOptions));
            File.Move(temporary, path, true);
            Warning = null;
            return true;
        }
        catch (Exception ex) when (ex is IOException or UnauthorizedAccessException or JsonException)
        {
            log.Write("Settings could not be saved.", ex);
            Warning = "Window settings could not be saved. Check access to the settings folder.";
            return false;
        }
    }

    private static WindowSnapshot Sanitize(WindowSnapshot window) => window with
    {
        X = Math.Clamp(window.X, -100_000, 100_000),
        Y = Math.Clamp(window.Y, -100_000, 100_000),
        Width = window.Width is >= 320 and <= 16_384 ? window.Width : 1200,
        Height = window.Height is >= 240 and <= 16_384 ? window.Height : 850,
        Url = NavigationPolicy.PersistableUrl(window.Url),
        Layout = SanitizeLayout(window.Layout),
        ActivePane = Math.Clamp(window.ActivePane, 0, 7)
    };

    public static PaneLayout? SanitizeLayout(PaneLayout? layout)
    {
        int remaining = 8;
        return Clean(layout, 0, ref remaining);
    }

    private static PaneLayout? Clean(PaneLayout? layout, int depth, ref int remaining)
    {
        if (layout is null || remaining == 0) return null;
        if (depth < 8 && layout.First is not null && layout.Second is not null)
        {
            var first = Clean(layout.First, depth + 1, ref remaining);
            var second = Clean(layout.Second, depth + 1, ref remaining);
            if (first is null) return second;
            if (second is null) return first;
            return new PaneLayout
            {
                First = first, Second = second,
                Direction = layout.Direction == SplitDirection.Below ? SplitDirection.Below : SplitDirection.Right,
                Ratio = double.IsFinite(layout.Ratio) ? Math.Clamp(layout.Ratio, 0.15, 0.85) : 0.5
            };
        }
        remaining--;
        return new PaneLayout { Url = NavigationPolicy.PersistableUrl(layout.Url) };
    }
}
