using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using ChatGPTMulti.Controls;
using ChatGPTMulti.Models;
using ChatGPTMulti.Services;
using Microsoft.Web.WebView2.Wpf;

namespace ChatGPTMulti;

public partial class MainWindow : Window
{
    public const int MaximumPanes = 8;
    private sealed class LayoutNode
    {
        public ChatPane? Pane;
        public SplitDirection Direction;
        public double Ratio = 0.5;
        public LayoutNode? First, Second;
    }

    private readonly List<ChatPane> _panes = [];
    private readonly WindowSnapshot? _savedState;
    private readonly LayoutNode _root;
    private bool _lastMaximized;
    private HwndSource? _source;
    internal WindowManager Manager { get; }
    public ChatPane ActivePane { get; private set; } = null!;
    public IReadOnlyList<ChatPane> Panes => Leaves(_root).ToList();
    public WebView2 Browser => ActivePane.Browser;
    public bool IsClosed { get; private set; }
    public bool IsRestorable => _panes.Any(p => p.IsRestorable);
    public string CurrentUrl => ActivePane.CurrentUrl;

    public MainWindow(WindowManager manager, string? initialUrl, WindowSnapshot? savedState, bool popup)
    {
        Manager = manager;
        _savedState = savedState;
        InitializeComponent();
        var layout = SettingsService.SanitizeLayout(savedState?.Layout);
        _root = layout is null
            ? new LayoutNode { Pane = CreatePane(initialUrl, popup) }
            : RestoreLayout(layout);
        RenderWorkspace();
        SetActivePane(Panes[Math.Clamp(savedState?.ActivePane ?? 0, 0, _panes.Count - 1)]);
        LocationChanged += (_, _) => Manager.ScheduleSave();
        SizeChanged += (_, _) => Manager.ScheduleSave();
        StateChanged += (_, _) =>
        {
            if (WindowState != WindowState.Minimized) _lastMaximized = WindowState == WindowState.Maximized;
            Manager.ScheduleSave();
        };
    }

    private ChatPane CreatePane(string? url, bool popup = false)
    {
        var pane = new ChatPane(this, url, popup);
        _panes.Add(pane);
        Manager.NotifyPaneCreated(pane);
        return pane;
    }

    private LayoutNode RestoreLayout(PaneLayout layout) => layout.First is not null && layout.Second is not null
        ? new LayoutNode { Direction = layout.Direction, Ratio = layout.Ratio, First = RestoreLayout(layout.First), Second = RestoreLayout(layout.Second) }
        : new LayoutNode { Pane = CreatePane(layout.Url ?? NavigationPolicy.Home) };

    private static IEnumerable<ChatPane> Leaves(LayoutNode node) => node.Pane is not null
        ? [node.Pane] : Leaves(node.First!).Concat(Leaves(node.Second!));

    private static LayoutNode? Find(LayoutNode node, ChatPane pane) => node.Pane == pane ? node
        : node.Pane is null ? Find(node.First!, pane) ?? Find(node.Second!, pane) : null;

    private static PaneLayout CaptureLayout(LayoutNode node) => node.Pane is not null
        ? new PaneLayout { Url = node.Pane.SavedUrl }
        : new PaneLayout { Direction = node.Direction, Ratio = node.Ratio, First = CaptureLayout(node.First!), Second = CaptureLayout(node.Second!) };

    private void RenderWorkspace()
    {
        // Reuse the controls; changing the grid must not reload pages or discard drafts.
        foreach (var pane in _panes)
            if (pane.Parent is Panel parent) parent.Children.Remove(pane);
        WorkspaceHost.Children.Clear();
        WorkspaceHost.Children.Add(RenderNode(_root));
    }

    private UIElement RenderNode(LayoutNode node)
    {
        if (node.Pane is not null) return node.Pane;
        var grid = new Grid();
        var first = RenderNode(node.First!);
        var second = RenderNode(node.Second!);
        Grid.SetColumn(first, 0);
        Grid.SetRow(first, 0);
        Grid.SetColumn(second, 0);
        Grid.SetRow(second, 0);
        var splitter = new GridSplitter
        {
            Background = new SolidColorBrush(Color.FromRgb(65, 65, 65)),
            HorizontalAlignment = HorizontalAlignment.Stretch,
            VerticalAlignment = VerticalAlignment.Stretch,
            ResizeBehavior = GridResizeBehavior.PreviousAndNext
        };
        if (node.Direction == SplitDirection.Right)
        {
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(node.Ratio, GridUnitType.Star), MinWidth = 100 });
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(6) });
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(1 - node.Ratio, GridUnitType.Star), MinWidth = 100 });
            Grid.SetColumn(splitter, 1);
            Grid.SetColumn(second, 2);
            splitter.ResizeDirection = GridResizeDirection.Columns;
        }
        else
        {
            grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(node.Ratio, GridUnitType.Star), MinHeight = 80 });
            grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(6) });
            grid.RowDefinitions.Add(new RowDefinition { Height = new GridLength(1 - node.Ratio, GridUnitType.Star), MinHeight = 80 });
            Grid.SetRow(splitter, 1);
            Grid.SetRow(second, 2);
            splitter.ResizeDirection = GridResizeDirection.Rows;
        }
        splitter.DragCompleted += (_, _) =>
        {
            double a = node.Direction == SplitDirection.Right ? grid.ColumnDefinitions[0].ActualWidth : grid.RowDefinitions[0].ActualHeight;
            double b = node.Direction == SplitDirection.Right ? grid.ColumnDefinitions[2].ActualWidth : grid.RowDefinitions[2].ActualHeight;
            if (a + b > 0) node.Ratio = Math.Clamp(a / (a + b), 0.15, 0.85);
            Manager.ScheduleSave();
        };
        grid.Children.Add(first);
        grid.Children.Add(splitter);
        grid.Children.Add(second);
        return grid;
    }

    public ChatPane? SplitPane(ChatPane target, string url, SplitDirection direction)
    {
        if (IsClosed || !_panes.Contains(target)) return null;
        if (_panes.Count >= MaximumPanes)
        {
            ShowNotice("This window has eight panes. Close a pane before opening another.");
            return null;
        }
        if (!NavigationPolicy.IsChatGpt(url) || NavigationPolicy.IsAuthentication(url)) url = NavigationPolicy.Home;
        var node = Find(_root, target)!;
        var added = CreatePane(url);
        node.Pane = null;
        node.Direction = direction;
        node.Ratio = 0.5;
        node.First = new LayoutNode { Pane = target };
        node.Second = new LayoutNode { Pane = added };
        RenderWorkspace();
        SetActivePane(added);
        Manager.ScheduleSave();
        Manager.Log.Write("Conversation pane added.");
        return added;
    }

    public bool DropConversation(ChatPane target, IDataObject data, SplitDirection direction)
    {
        string? url = ChatLinkDrop.Read(data);
        if (url is null) return false;
        return SplitPane(target, url, direction) is not null;
    }

    public void ClosePane(ChatPane pane)
    {
        if (IsClosed || !_panes.Contains(pane)) return;
        if (_panes.Count == 1) { Close(); return; }
        var parent = FindParent(_root, pane)!;
        var sibling = parent.First!.Pane == pane ? parent.Second! : parent.First;
        parent.Pane = sibling.Pane;
        parent.First = sibling.First;
        parent.Second = sibling.Second;
        parent.Direction = sibling.Direction;
        parent.Ratio = sibling.Ratio;
        if (pane.Parent is Panel container) container.Children.Remove(pane);
        _panes.Remove(pane);
        pane.Dispose();
        RenderWorkspace();
        SetActivePane(ActivePane == pane ? Panes[0] : ActivePane);
        Manager.ScheduleSave();
    }

    private static LayoutNode? FindParent(LayoutNode node, ChatPane pane)
    {
        if (node.Pane is not null) return null;
        if (node.First!.Pane == pane || node.Second!.Pane == pane) return node;
        return FindParent(node.First, pane) ?? FindParent(node.Second, pane);
    }

    public void SetActivePane(ChatPane pane)
    {
        if (IsClosed || !_panes.Contains(pane)) return;
        ActivePane = pane;
        foreach (var item in _panes) item.SetActive(item == pane);
        RefreshChrome();
        Manager.ScheduleSave();
    }

    internal void RefreshChrome()
    {
        if (IsClosed || ActivePane is null) return;
        var core = ActivePane.Browser.CoreWebView2;
        BackButton.IsEnabled = core?.CanGoBack ?? false;
        ForwardButton.IsEnabled = core?.CanGoForward ?? false;
        Title = ActivePane.PageTitle + " — ChatGPT Multi";
        PaneCount.Text = _panes.Count == 1 ? "Drag a sidebar chat to a green edge to split" : $"{_panes.Count} chats in this window";
    }

    protected override void OnSourceInitialized(EventArgs e)
    {
        base.OnSourceInitialized(e);
        _source = HwndSource.FromHwnd(new WindowInteropHelper(this).Handle);
        _source?.AddHook(WindowMessage);
        if (_savedState is not null) WindowPlacementService.Restore(this, _savedState);
    }

    private IntPtr WindowMessage(IntPtr hwnd, int message, IntPtr wParam, IntPtr lParam, ref bool handled)
    {
        if (message == 0x007E)
            Dispatcher.BeginInvoke(new Action(() =>
            {
                if (!IsClosed && WindowState == WindowState.Normal) WindowPlacementService.Restore(this, Snapshot());
            }));
        return IntPtr.Zero;
    }

    public Task<bool> InitializeBrowserAsync() => ActivePane.InitializeBrowserAsync();
    public WindowSnapshot Snapshot() => WindowPlacementService.Capture(this, ActivePane.SavedUrl, _lastMaximized) with
    {
        Layout = CaptureLayout(_root), ActivePane = Panes.ToList().IndexOf(ActivePane)
    };
    public void ShowNotice(string message) => ActivePane.ShowNotice(message);
    internal MainWindow DuplicateCurrent() => Manager.OpenWindow(
        NavigationPolicy.IsChatGpt(CurrentUrl) && !NavigationPolicy.IsAuthentication(CurrentUrl) ? CurrentUrl : NavigationPolicy.Home);

    internal static string? Shortcut(Key key, ModifierKeys modifiers) => (key, modifiers) switch
    {
        (Key.N, ModifierKeys.Control) => "new",
        (Key.N, ModifierKeys.Control | ModifierKeys.Shift) => "duplicate",
        (Key.OemPipe, ModifierKeys.Control) => "split-right",
        (Key.OemPipe, ModifierKeys.Control | ModifierKeys.Shift) => "split-below",
        (Key.W, ModifierKeys.Control | ModifierKeys.Shift) => "close-pane",
        (Key.Q, ModifierKeys.Control | ModifierKeys.Shift) => "exit",
        (Key.R, ModifierKeys.Control) => "refresh",
        (Key.Left, ModifierKeys.Alt) => "back",
        (Key.Right, ModifierKeys.Alt) => "forward",
        _ => null
    };

    private void OnPreviewKeyDown(object sender, KeyEventArgs e)
    {
        var key = e.Key == Key.System ? e.SystemKey : e.Key;
        string? command = Shortcut(key, Keyboard.Modifiers);
        if (command is null) return;
        if (Browser.IsKeyboardFocusWithin && command is "refresh" or "back" or "forward") return;
        e.Handled = true;
        if (!e.IsRepeat) Dispatcher.BeginInvoke(new Action(() => ExecuteShortcut(command)));
    }

    internal void ExecuteShortcut(string command)
    {
        if (IsClosed) return;
        switch (command)
        {
            case "new": Manager.OpenWindow(); break;
            case "duplicate": DuplicateCurrent(); break;
            case "split-right": SplitPane(ActivePane, CurrentUrl, SplitDirection.Right); break;
            case "split-below": SplitPane(ActivePane, CurrentUrl, SplitDirection.Below); break;
            case "close-pane": ClosePane(ActivePane); break;
            case "exit": Manager.ExitAll(); break;
            case "refresh": RefreshClick(this, new RoutedEventArgs()); break;
            case "back": ActivePane.NavigateSafely(core => { if (core.CanGoBack) core.GoBack(); }); break;
            case "forward": ActivePane.NavigateSafely(core => { if (core.CanGoForward) core.GoForward(); }); break;
        }
    }

    private async void RefreshClick(object sender, RoutedEventArgs e) => await ActivePane.RefreshAsync();
    private void BackClick(object sender, RoutedEventArgs e) => ExecuteShortcut("back");
    private void ForwardClick(object sender, RoutedEventArgs e) => ExecuteShortcut("forward");
    private void HomeClick(object sender, RoutedEventArgs e) => ActivePane.NavigateSafely(core => core.Navigate(NavigationPolicy.Home));
    private void NewWindowClick(object sender, RoutedEventArgs e) => ExecuteShortcut("new");
    private void DuplicateClick(object sender, RoutedEventArgs e) => DuplicateCurrent();
    private void SplitRightClick(object sender, RoutedEventArgs e) => ExecuteShortcut("split-right");
    private void SplitBelowClick(object sender, RoutedEventArgs e) => ExecuteShortcut("split-below");
    private void NewPaneClick(object sender, RoutedEventArgs e) => SplitPane(ActivePane, NavigationPolicy.Home, SplitDirection.Right);
    private void ExitAllClick(object sender, RoutedEventArgs e) => Manager.ExitAll();
    private void AppMenuClick(object sender, RoutedEventArgs e)
    {
        var button = (Button)sender;
        button.ContextMenu.PlacementTarget = button;
        button.ContextMenu.IsOpen = true;
    }

    protected override void OnClosing(CancelEventArgs e)
    {
        base.OnClosing(e);
        if (e.Cancel) return;
        Manager.Closing(this);
        IsClosed = true;
        _source?.RemoveHook(WindowMessage);
        foreach (var pane in _panes) pane.Dispose();
    }
}
