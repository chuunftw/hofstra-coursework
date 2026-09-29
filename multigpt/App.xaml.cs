using System.Windows;
using ChatGPTMulti.Services;
using Microsoft.Web.WebView2.Core;

namespace ChatGPTMulti;

public partial class App : Application
{
    private SingleInstance? _instance;
    private WindowManager? _windows;
    private AppLog? _log;
    private bool _pendingWindow;

    protected override async void OnStartup(StartupEventArgs e)
    {
        base.OnStartup(e);
        var paths = AppPaths.Default;
        _log = new AppLog(paths.LogDirectory);
        try
        {
            _instance = new SingleInstance(paths.ProfileDirectory);
            if (!_instance.IsPrimary)
            {
                _instance.RequestWindow();
                Shutdown();
                return;
            }
            _instance.Listen(() => Dispatcher.BeginInvoke(new Action(() =>
            {
                if (_windows is null) _pendingWindow = true;
                else _windows.OpenWindow().Activate();
            })));
            _log.Write("Application startup.");
            var webViews = new WebViewManager(paths, _log);
            await webViews.GetEnvironmentAsync();
            _windows = new WindowManager(webViews, new SettingsService(paths.SettingsFile, _log), _log);
            _windows.RestoreSession();
            if (_pendingWindow) _windows.OpenWindow();
        }
        catch (WebView2RuntimeNotFoundException ex)
        {
            _log.Write("WebView2 Runtime is missing.", ex);
            MessageBox.Show("ChatGPT Multi requires Microsoft Edge WebView2 Runtime.\n\nInstall the Evergreen Runtime from:\nhttps://developer.microsoft.com/microsoft-edge/webview2/\n\nThen reopen this application.",
                "WebView2 Runtime required", MessageBoxButton.OK, MessageBoxImage.Information);
            Shutdown(1);
        }
        catch (Exception ex)
        {
            _log.Write("Application startup failed.", ex);
            MessageBox.Show("ChatGPT Multi could not start its browser. Check that WebView2 Runtime is installed and your local application-data folder is writable.\n\nDetails: %LOCALAPPDATA%\\ChatGPTMulti\\Logs",
                "ChatGPT Multi", MessageBoxButton.OK, MessageBoxImage.Error);
            Shutdown(1);
        }
    }

    protected override void OnSessionEnding(SessionEndingCancelEventArgs e)
    {
        _windows?.SaveSession();
        _windows?.FreezeSession();
        base.OnSessionEnding(e);
    }

    protected override void OnExit(ExitEventArgs e)
    {
        _instance?.Dispose();
        _log?.Write("Application exit.");
        base.OnExit(e);
    }
}
