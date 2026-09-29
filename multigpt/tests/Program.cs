using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Input;
using ChatGPTMulti;
using ChatGPTMulti.Controls;
using ChatGPTMulti.Models;
using ChatGPTMulti.Services;
using Microsoft.Web.WebView2.Core;

internal static partial class Program
{
    private static int _checks;
    private static WindowManager? _manager;
    private const string FixtureUrl = "https://chatgpt.com/c/multi-test-conversation";
    private const string FixtureHtml = """
        <!doctype html><meta charset="utf-8"><title>ChatGPT Multi test fixture</title>
        <style>body{margin:0;background:#202020;color:#eee;font:16px Segoe UI;display:flex;height:100vh}
        aside{width:210px;flex-shrink:0;background:#161616;padding:20px;box-sizing:border-box}
        a{display:block;color:#b6dcc9;padding:15px 0;text-decoration:none}main{padding:24px;min-width:0}
        textarea{display:block;margin-top:20px;max-width:100%;background:#303030;color:#eee;border:1px solid #777;padding:12px}</style>
        <aside><b>Test chat sidebar</b><a href="https://chatgpt.com/c/planning-chat">Planning chat</a>
        <a href="https://chatgpt.com/c/code-review">Code review chat</a></aside>
        <main><h2>Local drag test</h2><p>Drag a sidebar link onto a green edge to split.</p>
        <p>This fixture never contacts ChatGPT.</p><textarea id="draft" placeholder="Unsent draft"></textarea></main>
        """;

    [STAThread]
    private static int Main(string[] args)
    {
        if (args.Length != 2 || args[0] is not ("core" or "restart" or "live" or "split" or "split-restart" or "drag-demo"))
        {
            Console.Error.WriteLine("Usage: ChatGPTMulti.Tests <core|restart|live|split|split-restart|drag-demo> <isolated-test-folder>");
            return 2;
        }
        string root = Path.GetFullPath(args[1]);
        if (root.StartsWith(Path.GetDirectoryName(AppPaths.Default.ProfileDirectory)!, StringComparison.OrdinalIgnoreCase))
            throw new InvalidOperationException("Tests must not use the normal application profile.");
        var app = new Application { ShutdownMode = ShutdownMode.OnExplicitShutdown };
        int result = 1;
        app.Startup += async (_, _) =>
        {
            try
            {
                Directory.CreateDirectory(root);
                if (args[0] == "core") TestSettingsAndPolicies(root);
                var paths = new AppPaths(Path.Combine(root, "WebView2"), Path.Combine(root, "session.json"), Path.Combine(root, "Logs"));
                var log = new AppLog(paths.LogDirectory);
                var webViews = new WebViewManager(paths, log);
                var environment = await webViews.GetEnvironmentAsync().WaitAsync(TimeSpan.FromSeconds(45));
                _manager = new WindowManager(webViews, new SettingsService(paths.SettingsFile, log), log);
                if (args[0] is "split" or "split-restart" or "drag-demo") _manager.PaneCreated += Fixture;
                if (args[0] == "live") await TestLivePage(_manager, root);
                else if (args[0] == "restart") await TestRestart(_manager);
                else if (args[0] == "split") await TestSplits(_manager, root);
                else if (args[0] == "split-restart") await TestSplitRestart(_manager);
                else if (args[0] == "drag-demo") await DragDemo(_manager);
                else await TestWindows(_manager, environment);
                Console.WriteLine($"PASS: {_checks} checks ({args[0]}).");
                result = 0;
            }
            catch (Exception ex) { Console.Error.WriteLine(ex); }
            finally
            {
                _manager?.ExitAll();
                app.Shutdown(result);
            }
        };
        app.Run();
        return result;
    }

    private static void Check(bool value, string description)
    {
        if (!value) throw new InvalidOperationException("FAIL: " + description);
        Console.WriteLine("PASS: " + description);
        _checks++;
    }

    private static void TestSettingsAndPolicies(string root)
    {
        string file = Path.Combine(root, "settings-tests.json");
        var settings = new SettingsService(file, new AppLog(Path.Combine(root, "Logs")));
        Check(settings.Load().Count == 1, "missing settings return a default window");
        var state = new WindowSnapshot { X = -1400, Y = 50, Width = 1000, Height = 700, Maximized = true, Url = FixtureUrl };
        Check(settings.Save([state, new()]), "settings write succeeds");
        Check(settings.Load() is { Count: 2 } loaded && loaded[0] == state, "all window properties round-trip");
        foreach (string corrupt in new[] { "{", "null", "{\"Version\":8}", "{\"Version\":1,\"Windows\":null}", "{\"Version\":1,\"Windows\":[null]}" })
        {
            File.WriteAllText(file, corrupt);
            Check(settings.Load().Count == 1, "invalid settings recover: " + corrupt);
        }
        File.WriteAllText(file, "{\"Version\":1,\"Windows\":[{\"X\":2147483647,\"Y\":-2147483648,\"Width\":-5,\"Height\":0,\"Url\":\"file:///C:/private.txt\"}]}");
        var safe = settings.Load()[0];
        Check(safe.Width == 1200 && safe.Height == 850 && safe.Url == NavigationPolicy.Home && safe.X <= 100000, "invalid bounds and unsafe URLs are sanitized");
        var work = new WindowPlacementService.PixelRect { Left = -1920, Top = 0, Right = 0, Bottom = 1040 };
        safe = WindowPlacementService.Clamp(new() { X = 50000, Y = -50000, Width = 4000, Height = 3000 }, work);
        Check(safe.X >= -1920 && safe.Y >= 0 && safe.X + safe.Width <= 0 && safe.Y + safe.Height <= 1040, "disconnected-monitor bounds clamp inside a negative-coordinate display");
        Check(NavigationPolicy.IsChatGpt(FixtureUrl) && !NavigationPolicy.IsChatGpt("https://chatgpt.com.evil.example/c/1")
            && !NavigationPolicy.IsChatGpt("https://chatgpt.com@evil.example") && !NavigationPolicy.IsChatGpt("http://chatgpt.com/c/1"), "ChatGPT host checks reject deceptive or insecure URLs");
        Check(NavigationPolicy.PersistableUrl(FixtureUrl + "?code=secret#token") == FixtureUrl
            && NavigationPolicy.PersistableUrl("https://chatgpt.com/auth/callback?code=secret") == NavigationPolicy.Home
            && NavigationPolicy.PersistableUrl("https://auth.openai.com/callback?code=secret") == NavigationPolicy.Home, "authentication URLs, queries and fragments are never persisted");
        Check(NavigationPolicy.OpenExternally("https://example.org/", FixtureUrl, true, false, false)
            && !NavigationPolicy.OpenExternally(FixtureUrl, FixtureUrl, true, false, false)
            && !NavigationPolicy.OpenExternally("https://accounts.google.com/", FixtureUrl, true, false, false)
            && !NavigationPolicy.OpenExternally("https://sso.example.org/", "https://auth.openai.com/", true, false, false)
            && !NavigationPolicy.OpenExternally("https://sso.example.org/", FixtureUrl, true, true, false), "external links are separated from ChatGPT and authentication redirects");
        Check(MainWindow.Shortcut(Key.N, ModifierKeys.Control) == "new"
            && MainWindow.Shortcut(Key.N, ModifierKeys.Control | ModifierKeys.Shift) == "duplicate"
            && MainWindow.Shortcut(Key.R, ModifierKeys.Control) == "refresh"
            && MainWindow.Shortcut(Key.Left, ModifierKeys.Alt) == "back"
            && MainWindow.Shortcut(Key.Right, ModifierKeys.Alt) == "forward", "required shortcut combinations map correctly");
        string blockedPath = Path.Combine(root, "not-a-directory");
        File.WriteAllText(blockedPath, "fixture");
        var blocked = new SettingsService(Path.Combine(blockedPath, "settings.json"), new AppLog(Path.Combine(root, "Logs")));
        Check(!blocked.Save([state]) && blocked.Warning is not null, "unwritable settings report a recoverable failure");
    }

    private static void Fixture(MainWindow window) => Fixture(window.ActivePane);

    private static void Fixture(ChatPane window)
    {
        void Configure(CoreWebView2 core)
        {
            core.AddWebResourceRequestedFilter("https://chatgpt.com/*", CoreWebView2WebResourceContext.All);
            core.WebResourceRequested += (_, e) =>
            {
                e.Response = core.Environment.CreateWebResourceResponse(new MemoryStream(Encoding.UTF8.GetBytes(FixtureHtml)),
                    200, "OK", "Content-Type: text/html; charset=utf-8\r\nCache-Control: no-store");
            };
        }
        if (window.Browser.CoreWebView2 is { } core) Configure(core);
        else window.Browser.CoreWebView2InitializationCompleted += (_, e) =>
        {
            if (e.IsSuccess) Configure(window.Browser.CoreWebView2);
        };
    }

    private static async Task Navigate(MainWindow window, string url)
    {
        var completion = new TaskCompletionSource<CoreWebView2NavigationCompletedEventArgs>();
        void Completed(object? sender, CoreWebView2NavigationCompletedEventArgs e) => completion.TrySetResult(e);
        window.Browser.CoreWebView2.NavigationCompleted += Completed;
        try
        {
            window.Browser.CoreWebView2.Navigate(url);
            var result = await completion.Task.WaitAsync(TimeSpan.FromSeconds(45));
            Check(result.IsSuccess && result.HttpStatusCode is >= 200 and < 400, "navigation completed successfully");
        }
        finally { window.Browser.CoreWebView2.NavigationCompleted -= Completed; }
    }

    private static async Task WaitUntil(Func<bool> condition, string description)
    {
        using var timeout = new CancellationTokenSource(TimeSpan.FromSeconds(30));
        while (!condition()) await Task.Delay(100, timeout.Token);
        Check(true, description);
    }

    private static async Task TestWindows(WindowManager manager, CoreWebView2Environment environment)
    {
        var first = manager.OpenWindow(null);
        Fixture(first);
        Check(await first.InitializeBrowserAsync(), "native WPF window initializes WebView2");
        Check(first.IsVisible && first.IsLoaded, "application window is visible");
        await Navigate(first, FixtureUrl);
        await first.Browser.CoreWebView2.ExecuteScriptAsync("localStorage.setItem('chatgpt-multi-test', 'persistent-fixture');");
        first.ExecuteShortcut("new");
        var second = manager.Windows[^1];
        Fixture(second);
        Check(await second.InitializeBrowserAsync(), "New Window command initializes another WebView");
        await WaitUntil(() => second.Browser.CoreWebView2.DocumentTitle == "ChatGPT Multi test fixture", "second window loads ChatGPT home fixture");
        Check(manager.Windows.Count == 2 && first.IsVisible && second.IsVisible, "multiple independent native windows coexist");
        Check(ReferenceEquals(await manager.WebViews.GetEnvironmentAsync(), environment)
            && first.Browser.CoreWebView2.Environment.UserDataFolder == environment.UserDataFolder
            && second.Browser.CoreWebView2.Environment.UserDataFolder == environment.UserDataFolder
            && first.Browser.CoreWebView2.BrowserProcessId == second.Browser.CoreWebView2.BrowserProcessId
            && first.Browser.CoreWebView2.Profile.ProfilePath == second.Browser.CoreWebView2.Profile.ProfilePath, "all windows use the same environment, browser process and profile");
        Check(await second.Browser.CoreWebView2.ExecuteScriptAsync("localStorage.getItem('chatgpt-multi-test')") == "\"persistent-fixture\"", "browser storage is shared across windows");
        await Navigate(first, FixtureUrl + "?test=value#section");
        first.ExecuteShortcut("duplicate");
        var duplicate = manager.Windows[^1];
        Fixture(duplicate);
        Check(await duplicate.InitializeBrowserAsync(), "duplicate window initializes");
        await WaitUntil(() => duplicate.CurrentUrl == first.CurrentUrl, "duplicate preserves the exact current URL");
        Check(first.Snapshot().Url == FixtureUrl, "saved URL excludes query and fragment");
        duplicate.Close();
        Check(manager.Windows.Count == 2 && first.IsVisible && second.IsVisible, "closing one window leaves the others alive");
        var before = first.Snapshot();
        first.WindowState = WindowState.Maximized;
        await Task.Delay(150);
        var maximized = first.Snapshot();
        first.WindowState = WindowState.Minimized;
        Check(first.Snapshot().Maximized, "minimizing preserves prior maximized state");
        first.WindowState = WindowState.Normal;
        Check(maximized.Maximized && Math.Abs(maximized.Width - before.Width) <= 2, "maximized snapshot preserves restored dimensions");
        await first.Browser.CoreWebView2.ExecuteScriptAsync("window.testPopup = window.open('about:blank', 'multi-popup');");
        await WaitUntil(() => manager.Windows.Count == 3, "window.open creates a native popup");
        var popup = manager.Windows[^1];
        Check(await popup.InitializeBrowserAsync(), "popup initializes with shared environment");
        await Task.Delay(300);
        Check(await popup.Browser.CoreWebView2.ExecuteScriptAsync("window.opener !== null") == "true", "popup retains window.opener for authentication");
        Check(!popup.IsRestorable, "temporary authentication popup is excluded from session settings");
        await popup.Browser.CoreWebView2.ExecuteScriptAsync("window.close();");
        await WaitUntil(() => manager.Windows.Count == 2, "script-requested popup close is honored");
        manager.SaveSession();
        Check(manager.Settings.Load().Count == 2, "all open ChatGPT windows are saved");
        manager.ExitAll();
        Check(manager.Windows.Count == 0 && manager.Settings.Load().Count == 2, "Exit all closes windows while preserving the full session");
    }

    private static async Task TestRestart(WindowManager manager)
    {
        manager.RestoreSession();
        Check(manager.Windows.Count == 2, "a fresh process restores both saved windows");
        // Register every fixture before yielding, since the windows initialize concurrently.
        foreach (var window in manager.Windows) Fixture(window);
        foreach (var window in manager.Windows)
        {
            Check(await window.InitializeBrowserAsync(), "restored window initializes");
            await WaitUntil(() => window.Browser.CoreWebView2.DocumentTitle == "ChatGPT Multi test fixture", "restored conversation loads");
        }
        Check(manager.Windows[0].CurrentUrl == FixtureUrl, "conversation URL survives process restart");
        Check(await manager.Windows[0].Browser.CoreWebView2.ExecuteScriptAsync("localStorage.getItem('chatgpt-multi-test')") == "\"persistent-fixture\"", "browser profile data survives process restart");
        var closing = manager.Windows[0];
        closing.Close();
        Check(manager.Settings.Load().Count == 1, "closing one restored window removes it from the next session");
    }

    private static async Task TestLivePage(WindowManager manager, string root)
    {
        var window = manager.OpenWindow(null);
        Check(await window.InitializeBrowserAsync(), "live WebView initializes");
        await Navigate(window, NavigationPolicy.Home);
        await WaitUntil(() => !string.IsNullOrWhiteSpace(window.Browser.CoreWebView2.DocumentTitle), "live ChatGPT page sets a title");
        Console.WriteLine("Live page title: " + window.Browser.CoreWebView2.DocumentTitle);
        Check(NavigationPolicy.IsChatGpt(window.CurrentUrl), "live page remains on ChatGPT");
        await using var image = File.Create(Path.Combine(root, "live-page.png"));
        await window.Browser.CoreWebView2.CapturePreviewAsync(CoreWebView2CapturePreviewImageFormat.Png, image);
        // Allow visual observation; this test never signs in or submits a prompt.
        await Task.Delay(5000);
    }
}
