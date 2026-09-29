using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using ChatGPTMulti.Models;
using ChatGPTMulti.Services;
using Microsoft.Web.WebView2.Core;
using Microsoft.Web.WebView2.Wpf;

namespace ChatGPTMulti.Controls;

public partial class ChatPane : UserControl, IDisposable
{
    private readonly MainWindow _owner;
    private readonly string? _initialUrl;
    private Task<bool>? _initialization;
    private bool _popup;
    private string _lastChatUrl;
    private bool _disposed;
    public WebView2 Browser { get; private set; } = new();
    public bool IsRestorable { get; private set; }
    public string CurrentUrl => Browser.CoreWebView2?.Source ?? _initialUrl ?? NavigationPolicy.Home;
    public string SavedUrl => _lastChatUrl;
    public string PageTitle => PaneTitle.Text;
    public bool IsDisposed => _disposed;

    internal ChatPane(MainWindow owner, string? initialUrl, bool popup)
    {
        _owner = owner;
        _initialUrl = initialUrl;
        _popup = popup;
        IsRestorable = !popup;
        _lastChatUrl = NavigationPolicy.PersistableUrl(initialUrl);
        InitializeComponent();
        if (popup) RightDropTarget.Visibility = BelowDropTarget.Visibility = Visibility.Collapsed;
        AttachBrowser();
        Loaded += async (_, _) => await InitializeBrowserAsync();
    }

    private void AttachBrowser()
    {
        BrowserHost.Children.Add(Browser);
        Browser.GotKeyboardFocus += (_, _) => _owner.SetActivePane(this);
        Browser.GotFocus += (_, _) => _owner.SetActivePane(this);
    }

    public Task<bool> InitializeBrowserAsync() => _initialization ??= InitializeCoreAsync();

    private async Task<bool> InitializeCoreAsync()
    {
        try
        {
            var environment = await _owner.Manager.WebViews.GetEnvironmentAsync();
            if (_disposed) return false;
            await Browser.EnsureCoreWebView2Async(environment);
            if (_disposed) return false;
            var core = Browser.CoreWebView2;
            core.Settings.IsPasswordAutosaveEnabled = false;
            core.Settings.IsGeneralAutofillEnabled = false;
            core.Settings.IsWebMessageEnabled = false;
            core.NavigationStarting += NavigationStarting;
            core.NavigationCompleted += NavigationCompleted;
            core.NewWindowRequested += NewWindowRequested;
            core.SourceChanged += (_, _) => UpdatePage();
            core.HistoryChanged += (_, _) => UpdatePage();
            core.DocumentTitleChanged += (_, _) => UpdatePage();
            core.WindowCloseRequested += (_, _) => Dispatcher.BeginInvoke(new Action(() => _owner.ClosePane(this)));
            core.ProcessFailed += (_, args) =>
            {
                _owner.Manager.Log.Write($"WebView process failure: {args.ProcessFailedKind}.");
                ShowNotice("The browser stopped responding. Select Retry; if it cannot recover, exit all windows and reopen ChatGPT Multi.");
            };
            _owner.Manager.Log.Write("Pane WebView initialized with shared environment.");
            if (_initialUrl is not null) core.Navigate(_initialUrl);
            return true;
        }
        catch (Exception ex)
        {
            _owner.Manager.Log.Write("Pane WebView initialization failed.", ex);
            if (!_disposed) ShowNotice("The browser could not initialize. Select Retry, or restart the application. Check that WebView2 Runtime is installed.");
            return false;
        }
    }

    private void NavigationStarting(object? sender, CoreWebView2NavigationStartingEventArgs e)
    {
        if (e.Uri == "about:blank") return;
        if (!NavigationPolicy.IsWebUrl(e.Uri))
        {
            e.Cancel = true;
            ShowNotice("This link uses a protocol that ChatGPT Multi does not open.");
            return;
        }
        if (NavigationPolicy.OpenExternally(e.Uri, CurrentUrl, e.IsUserInitiated, e.IsRedirected, _popup))
        {
            e.Cancel = true;
            try { Process.Start(new ProcessStartInfo(e.Uri) { UseShellExecute = true }); }
            catch (Exception ex)
            {
                _owner.Manager.Log.Write("External browser could not open.", ex);
                ShowNotice("The default browser could not open this link. Check your Windows default browser setting.");
            }
            return;
        }
        PageStatus.Text = "Loading " + new Uri(e.Uri).GetLeftPart(UriPartial.Authority) + "...";
    }

    private void NavigationCompleted(object? sender, CoreWebView2NavigationCompletedEventArgs e)
    {
        if (!e.IsSuccess && e.WebErrorStatus != CoreWebView2WebErrorStatus.OperationCanceled)
        {
            _owner.Manager.Log.Write($"Navigation failed: {e.WebErrorStatus}; HTTP {e.HttpStatusCode}.");
            ShowNotice($"The page could not load ({e.WebErrorStatus}). Check your internet connection, then select Retry.");
        }
        else if (e.IsSuccess && e.HttpStatusCode >= 400)
        {
            _owner.Manager.Log.Write($"Navigation returned HTTP {e.HttpStatusCode}.");
            ShowNotice($"The website returned HTTP {e.HttpStatusCode}. Follow any instructions on the page, or retry later.");
        }
        UpdatePage();
    }

    private void UpdatePage()
    {
        if (_disposed || Browser.CoreWebView2 is not { } core) return;
        if (Uri.TryCreate(core.Source, UriKind.Absolute, out var uri))
            PageStatus.Text = uri.Scheme is "https" or "http" ? uri.GetLeftPart(UriPartial.Authority) : "ChatGPT Multi";
        string title = core.DocumentTitle;
        PaneTitle.Text = string.IsNullOrWhiteSpace(title) ? "ChatGPT" : title[..Math.Min(title.Length, 120)];
        if (NavigationPolicy.IsChatGpt(core.Source) && !NavigationPolicy.IsAuthentication(core.Source))
        {
            _lastChatUrl = NavigationPolicy.PersistableUrl(core.Source);
            IsRestorable = true;
            _popup = false;
            RightDropTarget.Visibility = BelowDropTarget.Visibility = Visibility.Visible;
        }
        _owner.RefreshChrome();
        _owner.Manager.ScheduleSave();
    }

    private async void NewWindowRequested(object? sender, CoreWebView2NewWindowRequestedEventArgs e)
    {
        e.Handled = true;
        using var deferral = e.GetDeferral();
        MainWindow? popup = null;
        try
        {
            if (e.Uri != "about:blank" && !NavigationPolicy.IsWebUrl(e.Uri))
            {
                ShowNotice("This popup uses a protocol that ChatGPT Multi does not open.");
                return;
            }
            popup = _owner.Manager.OpenWindow(null, popup: true);
            if (!await popup.InitializeBrowserAsync() || _disposed || popup.IsClosed)
            {
                if (!popup.IsClosed) popup.Close();
                return;
            }
            // Assign an unnavigated view so authentication retains its opener connection.
            e.NewWindow = popup.Browser.CoreWebView2;
        }
        catch (Exception ex)
        {
            _owner.Manager.Log.Write("Popup creation failed.", ex);
            if (popup is { IsClosed: false }) popup.Close();
            if (!_disposed) ShowNotice("The popup could not open. Try the sign-in or link again.");
        }
    }

    public void ShowNotice(string message) { NoticeText.Text = message; NoticePanel.Visibility = Visibility.Visible; }

    public void NavigateSafely(Action<CoreWebView2> action)
    {
        if (_disposed || Browser.CoreWebView2 is not { } core) return;
        try { action(core); }
        catch (Exception ex)
        {
            _owner.Manager.Log.Write("Browser action failed.", ex);
            ShowNotice("The browser is unavailable. Exit all windows and reopen the application.");
        }
    }

    public async Task RefreshAsync()
    {
        if (_disposed) return;
        NoticePanel.Visibility = Visibility.Collapsed;
        if (_initialization is { IsCompletedSuccessfully: true, Result: false })
        {
            Browser.Dispose();
            BrowserHost.Children.Clear();
            Browser = new WebView2();
            AttachBrowser();
            _initialization = null;
        }
        if (await InitializeBrowserAsync() && !_disposed) NavigateSafely(core => core.Reload());
    }

    internal void SetActive(bool active) => PaneBorder.BorderBrush = Brush(active ? "#89BAA4" : "#3B3B3B");
    private static SolidColorBrush Brush(string color) => new((Color)ColorConverter.ConvertFromString(color));
    private static DragDropEffects DropEffect(DragEventArgs e) => (e.AllowedEffects & DragDropEffects.Copy) != 0
        ? DragDropEffects.Copy : (e.AllowedEffects & DragDropEffects.Link) != 0 ? DragDropEffects.Link : DragDropEffects.None;

    private void DropOver(object sender, DragEventArgs e)
    {
        bool accepted = ChatLinkDrop.Read(e.Data) is not null && _owner.Panes.Count < MainWindow.MaximumPanes;
        e.Effects = accepted ? DropEffect(e) : DragDropEffects.None;
        ((Border)sender).Background = Brush(accepted ? "#375F50" : "#242B2A");
        e.Handled = true;
    }

    private void DropLeave(object sender, DragEventArgs e) => ((Border)sender).Background = Brush("#242B2A");
    private void DropChat(object sender, DragEventArgs e)
    {
        var target = (Border)sender;
        target.Background = Brush("#242B2A");
        var direction = (string)target.Tag == "Below" ? SplitDirection.Below : SplitDirection.Right;
        string? url = ChatLinkDrop.Read(e.Data);
        bool accepted = url is not null && _owner.Panes.Count < MainWindow.MaximumPanes;
        e.Effects = accepted ? DropEffect(e) : DragDropEffects.None;
        if (e.Effects != DragDropEffects.None)
        {
            // Finish the OLE drop before changing native browser parents.
            Dispatcher.BeginInvoke(new Action(() => _owner.SplitPane(this, url!, direction)));
        }
        e.Handled = true;
    }

    private void HeaderClick(object sender, MouseButtonEventArgs e) => _owner.SetActivePane(this);
    private void CloseClick(object sender, RoutedEventArgs e) => _owner.ClosePane(this);
    private void DismissClick(object sender, RoutedEventArgs e) => NoticePanel.Visibility = Visibility.Collapsed;
    private async void RefreshClick(object sender, RoutedEventArgs e) => await RefreshAsync();
    public void Dispose()
    {
        if (_disposed) return;
        _disposed = true;
        Browser.Dispose();
    }
}
