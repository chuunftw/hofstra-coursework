using System.Windows.Threading;
using ChatGPTMulti.Models;

namespace ChatGPTMulti.Services;

public sealed class WindowManager
{
    private readonly List<MainWindow> _windows = [];
    private readonly DispatcherTimer _saveTimer;
    private bool _restoring;
    private bool _exiting;
    public WebViewManager WebViews { get; }
    public SettingsService Settings { get; }
    public AppLog Log { get; }
    public IReadOnlyList<MainWindow> Windows => _windows;
    internal event Action<Controls.ChatPane>? PaneCreated;
    internal void NotifyPaneCreated(Controls.ChatPane pane) => PaneCreated?.Invoke(pane);

    public WindowManager(WebViewManager webViews, SettingsService settings, AppLog log)
    {
        WebViews = webViews;
        Settings = settings;
        Log = log;
        _saveTimer = new DispatcherTimer { Interval = TimeSpan.FromMilliseconds(500) };
        _saveTimer.Tick += (_, _) => { _saveTimer.Stop(); SaveSession(); };
    }

    public MainWindow OpenWindow(string? url = NavigationPolicy.Home, WindowSnapshot? state = null, bool popup = false)
    {
        var window = new MainWindow(this, url, state, popup);
        _windows.Add(window);
        window.Show();
        Log.Write(popup ? "Popup window created." : "ChatGPT window created.");
        ScheduleSave();
        return window;
    }

    public void RestoreSession()
    {
        _restoring = true;
        try
        {
            var saved = Settings.Load();
            var warning = Settings.Warning;
            foreach (var state in saved) OpenWindow(state.Url, state);
            Log.Write($"Restored {saved.Count} window(s).");
            if (warning is not null) _windows[0].ShowNotice(warning);
        }
        finally { _restoring = false; }
    }

    public void ScheduleSave()
    {
        if (_restoring || _exiting) return;
        _saveTimer.Stop();
        _saveTimer.Start();
    }

    public void SaveSession()
    {
        if (_restoring || _exiting) return;
        var snapshots = _windows.Where(w => w.IsRestorable && !w.IsClosed).Select(w => w.Snapshot()).ToList();
        if (snapshots.Count > 0 && !Settings.Save(snapshots))
            _windows.FirstOrDefault()?.ShowNotice(Settings.Warning!);
    }

    internal void Closing(MainWindow window)
    {
        if (!_exiting && window.IsRestorable)
        {
            var remaining = _windows.Where(w => w != window && w.IsRestorable && !w.IsClosed).ToList();
            // Closing individual windows removes them; the last window remains available next launch.
            if (!Settings.Save(remaining.Count == 0 ? [window.Snapshot()] : remaining.Select(w => w.Snapshot())))
                remaining.FirstOrDefault()?.ShowNotice(Settings.Warning!);
        }
        _windows.Remove(window);
        if (_windows.Count == 0) _saveTimer.Stop();
    }

    public void ExitAll()
    {
        SaveSession();
        FreezeSession();
        foreach (var window in _windows.ToArray()) window.Close();
    }

    public void FreezeSession()
    {
        _exiting = true;
        _saveTimer.Stop();
    }
}
