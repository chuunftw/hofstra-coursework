namespace ChatGPTMulti.Models;

public sealed record WindowSnapshot
{
    // Physical screen pixels, including negative coordinates on secondary monitors.
    public int X { get; init; } = 80;
    public int Y { get; init; } = 80;
    public int Width { get; init; } = 1200;
    public int Height { get; init; } = 850;
    public bool Maximized { get; init; }
    public string Url { get; init; } = Services.NavigationPolicy.Home;
    public PaneLayout? Layout { get; init; }
    public int ActivePane { get; init; }
}

public enum SplitDirection { Right, Below }

public sealed record PaneLayout
{
    public string? Url { get; init; }
    public SplitDirection Direction { get; init; }
    public double Ratio { get; init; } = 0.5;
    public PaneLayout? First { get; init; }
    public PaneLayout? Second { get; init; }
}

public sealed class AppSettings
{
    public int Version { get; set; } = 2;
    public List<WindowSnapshot?>? Windows { get; set; } = [];
}
