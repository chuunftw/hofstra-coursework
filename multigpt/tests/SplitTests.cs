using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Input;
using ChatGPTMulti;
using ChatGPTMulti.Controls;
using ChatGPTMulti.Models;
using ChatGPTMulti.Services;

internal static partial class Program
{
    private static async Task Ready(ChatPane pane)
    {
        Check(await pane.InitializeBrowserAsync(), "pane initializes");
        await WaitUntil(() => pane.Browser.CoreWebView2.DocumentTitle == "ChatGPT Multi test fixture", "pane fixture loads");
    }

    private static async Task TestSplits(WindowManager manager, string root)
    {
        var textDrop = new DataObject(DataFormats.UnicodeText, FixtureUrl);
        Check(ChatLinkDrop.Read(textDrop) == FixtureUrl, "plain-text conversation drag resolves");
        var nativeDrop = new DataObject();
        nativeDrop.SetData("UniformResourceLocatorW", new MemoryStream(Encoding.Unicode.GetBytes(FixtureUrl + "\0")));
        Check(ChatLinkDrop.Read(nativeDrop) == FixtureUrl, "native Chromium Unicode URL drag resolves");
        var htmlDrop = new DataObject(DataFormats.Html, "<a href=\"https://chatgpt.com/c/planning-chat?a=1&amp;b=2\">Chat</a>");
        Check(ChatLinkDrop.Read(htmlDrop) == "https://chatgpt.com/c/planning-chat?a=1&b=2", "HTML link drag is decoded without executing content");
        Check(ChatLinkDrop.IsConversation("https://chatgpt.com/g/project/c/conversation"), "nested project conversation links are accepted");
        foreach (string unsafeUrl in new[] { "https://example.org/c/123", "https://chatgpt.com.evil.test/c/123", "javascript:alert(1)", "file:///C:/private", "https://chatgpt.com/auth/callback", "https://chatgpt.com/" })
            Check(ChatLinkDrop.Read(new DataObject(DataFormats.Text, unsafeUrl)) is null, "non-conversation drag rejected: " + unsafeUrl);
        Check(ChatLinkDrop.Read(new DataObject(DataFormats.Text, new string('a', 70_000))) is null, "oversized drag payload is rejected");

        var window = manager.OpenWindow(FixtureUrl);
        var left = window.ActivePane;
        await Ready(left);
        var originalCore = left.Browser.CoreWebView2;
        await originalCore.ExecuteScriptAsync("document.querySelector('#draft').value = 'Keep my unsent draft'; window.paneMarker = 'alive';");
        Check(window.DropConversation(left, nativeDrop, SplitDirection.Right), "dropping a sidebar conversation splits the target pane");
        var right = window.ActivePane;
        await Ready(right);
        Check(manager.Windows.Count == 1 && window.Panes.Count == 2, "split creates two chats inside one native window");
        Check(left.Browser.CoreWebView2 == originalCore && await originalCore.ExecuteScriptAsync("window.paneMarker") == "\"alive\""
            && await originalCore.ExecuteScriptAsync("document.querySelector('#draft').value") == "\"Keep my unsent draft\"", "splitting preserves the original browser and unsent draft");
        Check(right.CurrentUrl == FixtureUrl && right.Browser.CoreWebView2.Profile.ProfilePath == originalCore.Profile.ProfilePath,
            "dropped chat uses the exact URL and shared profile");
        Check(right.TranslatePoint(new Point(), window).X > left.TranslatePoint(new Point(), window).X,
            "right split places the new pane to the right without overlap");
        Check(window.DropConversation(right, htmlDrop, SplitDirection.Below), "a second sidebar drop splits an existing pane below");
        var below = window.ActivePane;
        await Ready(below);
        Check(window.Panes.Count == 3 && manager.Windows.Count == 1, "nested splits remain in one window");
        Check(below.TranslatePoint(new Point(), window).Y > right.TranslatePoint(new Point(), window).Y,
            "below split places the pane below without overlap");
        window.ClosePane(right);
        Check(window.Panes.Count == 2 && right.IsDisposed && !left.IsDisposed && !below.IsDisposed,
            "closing a pane collapses only its split and disposes only that browser");
        Check(await originalCore.ExecuteScriptAsync("document.querySelector('#draft').value") == "\"Keep my unsent draft\"",
            "closing a sibling preserves the existing unsent draft");
        window.SetActivePane(left);
        window.ExecuteShortcut("split-below");
        var bottomLeft = window.ActivePane;
        await Ready(bottomLeft);
        Check(window.Panes.Count == 3 && MainWindow.Shortcut(Key.OemPipe, ModifierKeys.Control) == "split-right"
            && MainWindow.Shortcut(Key.OemPipe, ModifierKeys.Control | ModifierKeys.Shift) == "split-below", "split shortcuts duplicate the active chat within the window");
        Check(!window.DropConversation(left, new DataObject(DataFormats.Text, "https://example.org/"), SplitDirection.Right)
            && window.Panes.Count == 3, "invalid drops leave the existing layout intact");
        var saved = window.Snapshot();
        Check(saved.Layout is { Direction: SplitDirection.Right, First.First: not null, Second.Url: not null }
            && saved.ActivePane == 1, "snapshot captures nested layout and active pane in visual order");
        var settings = new SettingsService(Path.Combine(root, "layout-tests.json"), new AppLog(Path.Combine(root, "Logs")));
        var custom = saved with { Layout = saved.Layout! with { Ratio = 0.65 } };
        Check(settings.Save([custom]) && settings.Load()[0].Layout == custom.Layout, "split orientation, proportions and pane URLs round-trip");
        File.WriteAllText(Path.Combine(root, "layout-tests.json"), "{\"Version\":1,\"Windows\":[{\"Url\":\"https://chatgpt.com/c/old-chat\"}]}");
        Check(settings.Load()[0] is { Layout: null, Url: "https://chatgpt.com/c/old-chat" }, "old single-browser settings remain readable");
        var dirty = new PaneLayout { First = new() { Url = "https://auth.openai.com/?code=private" }, Second = new() { Url = FixtureUrl + "?secret=1#token" }, Ratio = 3 };
        var cleaned = SettingsService.SanitizeLayout(dirty)!;
        Check(cleaned.Ratio == 0.85 && cleaned.First!.Url == NavigationPolicy.Home && cleaned.Second!.Url == FixtureUrl,
            "layout settings sanitize authentication URLs and invalid proportions");
        var extras = new List<ChatPane>();
        while (window.Panes.Count < MainWindow.MaximumPanes)
        {
            var extra = window.SplitPane(left, FixtureUrl, SplitDirection.Right)!;
            extras.Add(extra);
            await Ready(extra);
        }
        Check(window.SplitPane(left, FixtureUrl, SplitDirection.Right) is null && window.Panes.Count == 8,
            "pane limit rejects another split without losing existing chats");
        foreach (var pane in extras) window.ClosePane(pane);
        window.SetActivePane(bottomLeft);
        await originalCore.ExecuteScriptAsync("localStorage.setItem('split-test', 'survives-restart');");
        manager.ExitAll();
        Check(manager.Settings.Load()[0].Layout == saved.Layout, "exit preserves the final three-pane layout");
    }

    private static async Task TestSplitRestart(WindowManager manager)
    {
        manager.RestoreSession();
        Check(manager.Windows.Count == 1, "split workspace restores into one window");
        var window = manager.Windows[0];
        Check(window.Panes.Count == 3, "all three conversation panes restore");
        foreach (var pane in window.Panes) await Ready(pane);
        Check(window.Snapshot().Layout is { Direction: SplitDirection.Right, First.Direction: SplitDirection.Below }, "nested split directions survive restart");
        Check(window.Panes[2].CurrentUrl == "https://chatgpt.com/c/planning-chat", "dropped conversation path survives restart without query data");
        Check(await window.Browser.CoreWebView2.ExecuteScriptAsync("localStorage.getItem('split-test')") == "\"survives-restart\"",
            "split panes reuse the persistent browser profile in a fresh process");
    }

    private static async Task DragDemo(WindowManager manager)
    {
        var window = manager.OpenWindow(FixtureUrl);
        await Ready(window.ActivePane);
        window.Title = "ChatGPT Multi - isolated sidebar drag test";
        var closed = new TaskCompletionSource();
        window.Closed += (_, _) => closed.TrySetResult();
        Console.WriteLine("Ready for native sidebar drag testing. Close the window to finish.");
        await closed.Task;
    }
}
