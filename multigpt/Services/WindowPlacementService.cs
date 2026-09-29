using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Interop;
using ChatGPTMulti.Models;

namespace ChatGPTMulti.Services;

public static class WindowPlacementService
{
    [StructLayout(LayoutKind.Sequential)]
    public struct PixelRect { public int Left, Top, Right, Bottom; }
    [StructLayout(LayoutKind.Sequential)]
    private struct Point { public int X, Y; }
    [StructLayout(LayoutKind.Sequential)]
    private struct Placement
    {
        public int Length, Flags, ShowCommand;
        public Point MinimumPosition, MaximumPosition;
        public PixelRect NormalPosition;
    }
    [StructLayout(LayoutKind.Sequential)]
    private struct MonitorInfo { public int Size; public PixelRect Monitor, Work; public int Flags; }

    [DllImport("user32.dll")] private static extern bool GetWindowPlacement(IntPtr hwnd, ref Placement placement);
    [DllImport("user32.dll")] private static extern IntPtr MonitorFromRect(ref PixelRect rect, uint flags);
    [DllImport("user32.dll")] private static extern IntPtr MonitorFromWindow(IntPtr hwnd, uint flags);
    [DllImport("user32.dll", CharSet = CharSet.Auto)] private static extern bool GetMonitorInfo(IntPtr monitor, ref MonitorInfo info);
    [DllImport("user32.dll")] private static extern bool SetWindowPos(IntPtr hwnd, IntPtr after, int x, int y, int width, int height, uint flags);

    private static MonitorInfo GetMonitor(IntPtr handle)
    {
        var info = new MonitorInfo { Size = Marshal.SizeOf<MonitorInfo>() };
        if (!GetMonitorInfo(handle, ref info))
            info.Work = info.Monitor = new PixelRect { Right = 1280, Bottom = 800 };
        return info;
    }

    public static WindowSnapshot Clamp(WindowSnapshot state, PixelRect work)
    {
        int width = Math.Clamp(state.Width, Math.Min(640, work.Right - work.Left), Math.Max(1, work.Right - work.Left));
        int height = Math.Clamp(state.Height, Math.Min(480, work.Bottom - work.Top), Math.Max(1, work.Bottom - work.Top));
        return state with
        {
            X = Math.Clamp(state.X, work.Left, work.Right - width),
            Y = Math.Clamp(state.Y, work.Top, work.Bottom - height), Width = width, Height = height
        };
    }

    public static void Restore(Window window, WindowSnapshot state)
    {
        var rect = new PixelRect { Left = state.X, Top = state.Y, Right = state.X + state.Width, Bottom = state.Y + state.Height };
        var work = GetMonitor(MonitorFromRect(ref rect, 2)).Work;
        var safe = Clamp(state, work);
        SetWindowPos(new WindowInteropHelper(window).Handle, IntPtr.Zero, safe.X, safe.Y, safe.Width, safe.Height, 0x0014);
        if (state.Maximized) window.WindowState = System.Windows.WindowState.Maximized;
    }

    public static WindowSnapshot Capture(Window window, string url, bool maximized)
    {
        var handle = new WindowInteropHelper(window).Handle;
        var placement = new Placement { Length = Marshal.SizeOf<Placement>() };
        if (!GetWindowPlacement(handle, ref placement)) return new() { Url = url, Maximized = maximized };
        var monitor = GetMonitor(MonitorFromWindow(handle, 2));
        // WINDOWPLACEMENT uses workspace coordinates; persist physical screen coordinates.
        var rect = placement.NormalPosition;
        return new()
        {
            X = rect.Left + monitor.Work.Left - monitor.Monitor.Left,
            Y = rect.Top + monitor.Work.Top - monitor.Monitor.Top,
            Width = rect.Right - rect.Left, Height = rect.Bottom - rect.Top,
            Maximized = maximized, Url = NavigationPolicy.PersistableUrl(url)
        };
    }
}
