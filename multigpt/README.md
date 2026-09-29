# ChatGPT Multi

An unofficial Windows desktop wrapper for the normal [ChatGPT website](https://chatgpt.com). It uses C#, .NET 10, WPF and Microsoft Edge WebView2 to show multiple conversations in resizable panes inside one window. Separate native windows are also available. **This project is not affiliated with or endorsed by OpenAI.** It does not use the OpenAI API or require an API key.

## Requirements

- Windows 10/11, with current Windows updates.
- [Microsoft Edge WebView2 Evergreen Runtime](https://developer.microsoft.com/microsoft-edge/webview2/). The app shows installation instructions if it is missing.
- [.NET 10 SDK](https://dotnet.microsoft.com/download/dotnet/10.0) to build from source. The `global.json` allows stable .NET 10 feature updates.
- A normal ChatGPT account and internet connection for the website. ChatGPT account limits and availability still apply.

A framework-dependent published build needs the **.NET 10 Desktop Runtime**. A self-contained build includes .NET, but still needs WebView2 Runtime.

## Run from source

In PowerShell, from the coursework repository root:

```powershell
cd .\multigpt
dotnet restore .\ChatGPTMulti.csproj
dotnet build .\ChatGPTMulti.csproj --no-restore
dotnet run --project .\ChatGPTMulti.csproj
```

Once inside `multigpt`, plain `dotnet run` also works. Open `ChatGPTMulti.sln` in a Visual Studio version supporting .NET 10, or open this folder in VS Code with C# tooling. The only application NuGet dependency is `Microsoft.Web.WebView2`, pinned in the project and lock file.

After updating the source, save any unsent drafts and exit the old running copy before launching the new build. A second launch otherwise asks the existing process to open a window.

## Use

### Drag chats into split panes

1. Open ChatGPT's sidebar in a pane.
2. Drag a conversation link from that sidebar onto the green **Drop chat here** strip at the right of a pane, or the green strip below it.
3. The conversation opens beside or below that pane, inside the same native window. You can split any pane again, up to eight panes per window.
4. Drag the gray divider to resize the panes. Use a pane's **Close** button to remove that pane and give its space back to its sibling.

The app accepts normal browser link-drag data (including Chromium's URL format). It does not scrape or replace ChatGPT's sidebar. Drops target the green app strips; dropping over the website body is handled by the website, rather than by the split workspace. If ChatGPT prevents dragging a particular sidebar item, open that chat and use **Split right** or **Split below**. These buttons duplicate the currently focused conversation into a pane; **New chat pane** opens ChatGPT home in a new pane.

Click inside a pane or its header to make it active. Its border is highlighted, and the top Back/Forward/Refresh/Home controls operate on that pane. Splitting, resizing or closing another pane keeps the remaining browser instances alive, preserving their in-memory page state and unsent drafts. Closing the pane itself or exiting the app ends that browser instance; the app does not save draft text.

| Action | Shortcut |
| --- | --- |
| Split the active chat to the right | Ctrl+\ |
| Split the active chat below | Ctrl+Shift+\ |
| Close the active pane | Ctrl+Shift+W |
| New native ChatGPT window | Ctrl+N |
| Open the current conversation in another native window | Ctrl+Shift+N |
| Refresh | Ctrl+R |
| Back / Forward | Alt+Left / Alt+Right |
| Save the open session and exit every window | Ctrl+Shift+Q |

The small toolbar provides navigation and split controls. The App menu retains New Window and Open Current Chat in New Window. All windows support normal Windows resizing, maximizing, minimizing, Snap and Alt+Tab. Each pane's header shows its current website origin, including during sign-in.

Sign in through the normal ChatGPT page. All panes and windows use one persistent WebView2 environment and the default profile. New panes share the resulting authentication state. An already-open page may need Refresh after signing in or out elsewhere. This profile is separate from your usual Edge/Chrome profile; logging in in your normal browser does not sign in the wrapper.

The duplicate command uses the current ChatGPT URL exactly, without scraping the page. During an authentication flow or while viewing an unrelated website, it opens ChatGPT home instead of duplicating authentication parameters.

### Window restoration

Use **App > Exit all windows** (or Ctrl+Shift+Q) to preserve the whole open session. Next launch restores the windows, their split layouts, divider proportions, pane URLs, restored bounds and maximized states. Minimized windows reopen in their previous normal/maximized state. Settings from the original single-browser version are still readable and start with one pane per saved window.

Closing a single window with X removes it from the next session. Closing the last ChatGPT window preserves that last window. Settings are also saved after navigation/movement and on Windows session shutdown. Temporary sign-in popups are not restored. A popup that reaches a regular ChatGPT page becomes a regular saved window.

Bounds are stored in physical screen pixels, including negative coordinates for monitors to the left of the primary display. On restoration, bounds are clamped to the nearest available monitor's work area. The app opts into per-monitor DPI awareness and handles display layout changes. Saved sessions are limited to 50 restored windows to contain malformed settings.

Launching the executable again requests a new window in the running process, avoiding competing settings writers.

### Links and sign-in popups

ChatGPT navigation stays in the app. Ordinary, user-initiated links to unrelated websites open the default browser. Authentication domains and redirects stay inside WebView2. Requested popups open in native app windows using WebView2's `NewWindow` mechanism, retaining their opener connection. This includes external popups because their role in an authentication flow cannot always be determined safely from the initial URL.

**Authentication compatibility requires a manual check with your account.** Some identity providers reject embedded browsers; Google documents [restrictions on OAuth in embedded webviews](https://developers.googleblog.com/upcoming-security-changes-to-googles-oauth-20-authorization-endpoint-in-embedded-webviews/). The wrapper cannot guarantee every sign-in method, nor can it transfer a browser session from an external browser. If the provider rejects WebView2, use another sign-in method already supported by your account, or use ChatGPT in your normal browser. The app does not change its user agent, bypass authentication checks, or automate login.

## Build and publish

Release build:

```powershell
dotnet build .\ChatGPTMulti.csproj -c Release
```

Framework-dependent Windows x64 publish:

```powershell
dotnet publish .\ChatGPTMulti.csproj -c Release -r win-x64 --self-contained false -o .\.artifacts\publish\framework-dependent
```

Self-contained Windows x64 publish (includes the .NET runtime):

```powershell
dotnet publish .\ChatGPTMulti.csproj -c Release -r win-x64 --self-contained true -o .\.artifacts\publish\win-x64
```

Run `ChatGPTMulti.exe` in the chosen output directory. Distribute the entire directory, including the WebView2 loader and managed assemblies. No installer, administrator privileges, or remote debugging port is needed.

## Local data and privacy

| Data | Location |
| --- | --- |
| Persistent browser profile | `%LOCALAPPDATA%\ChatGPTMulti\WebView2` |
| Window settings | `%APPDATA%\ChatGPTMulti\settings.json` |
| Application logs | `%LOCALAPPDATA%\ChatGPTMulti\Logs` |

WebView2 manages website cookies, browser storage and cache inside its profile. The wrapper does not read or export authentication cookies, tokens, passwords or conversation contents. Browser password autosave and general autofill are disabled. The application does not inject scripts into ChatGPT, scrape the DOM, call private endpoints, or expose native objects/web-message bridges to websites.

Settings contain window bounds, maximized state, split layout and ChatGPT page paths for each pane. Query strings, fragments and authentication paths are excluded to avoid saving login parameters. Conversation paths are still private metadata; keep your local settings private. Browser-managed caches may contain website data as in any normal browser.

Logs contain lifecycle events and numeric error/status details, without page URLs, page titles, exception messages or conversation content. Logs rotate at 2 MB and files older than 14 days are removed on a subsequent log write.

Corrupt settings fall back to a usable default window and show a notice. Failed settings writes show a notice where a window remains open. Failed navigation shows a retry banner. A browser-process crash may require closing all app windows and relaunching.

To reset window placement without signing out, exit all windows and rename `settings.json`. To clear this app's login, sign out through ChatGPT. Removing its WebView2 profile while the application is closed also clears the app's browser data; it does not affect your regular browser.

## Tests

The dependency-free test executable uses the actual WPF windows and WebView2 controls. Core tests serve a local HTML fixture through WebView2's request handler, with an isolated profile under `.artifacts`. They do not access your normal profile or require ChatGPT credentials. The fixture tests use JavaScript only in the test executable, not in the application.

```powershell
dotnet restore .\ChatGPTMulti.sln
powershell -ExecutionPolicy Bypass -File .\tests\run-tests.ps1
```

To additionally check real, unauthenticated ChatGPT navigation:

```powershell
powershell -ExecutionPolicy Bypass -File .\tests\run-tests.ps1 -Live
```

Tests open visible temporary desktop windows. They check settings round trips, malformed settings, unsafe saved URLs, monitor clamping, recoverable write errors, shortcuts, concurrent windows, the shared environment/profile, shared browser storage, duplication, popup opener/close behavior, and restoration/storage persistence in a second process. Split tests also cover native URL/text/HTML drag payloads, invalid drops, nested pane positions, draft preservation, pane disposal, pane limits, and full split-layout restoration. The live test depends on network access and the website accepting embedded navigation.

Verified locally on September 28, 2026 with .NET SDK 10.0.401 and WebView2 Runtime 153.0.4234.48:

- Release solution build: zero warnings and errors.
- Core fixture tests: 37 checks passed.
- Split-pane tests: 47 checks passed.
- Fresh-process split-layout tests: 11 checks passed.
- Fresh-process restoration tests: 8 checks passed, including persistent browser storage.
- Live unauthenticated ChatGPT navigation: 4 checks passed; the rendered home page was inspected.
- Release publish succeeded at `.artifacts/publish/portable/ChatGPTMulti.exe` using `dotnet publish .\ChatGPTMulti.csproj -c Release --no-restore -o .\.artifacts\publish\portable`.
- Normal `dotnet run --project .\ChatGPTMulti.csproj --no-build` startup initialized its persistent WebView2 profile and first window.

Account login, authenticated session persistence, physical sidebar dragging, keyboard input while the web page has focus, and physical multi-monitor/DPI behavior remain manual acceptance checks. The split tests exercise native drag-data formats and the drop-to-split operation, but do not simulate the mouse gesture. Desktop UI automation could not start in the verification environment (the Node runtime reported that its executable path was missing).

An isolated sidebar fixture is available for manually checking native link dragging without signing in:

```powershell
dotnet run --project .\tests\ChatGPTMulti.Tests.csproj -c Release -- drag-demo .\.artifacts\manual-drag-test
```

Manual acceptance checks:

1. Run the app and sign in using your normal account method.
2. Drag two different sidebar chats to the right and bottom green drop targets. Check that three chats are visible in one window and all are signed in.
3. Type an unsent draft in one pane, split another pane, drag a divider, then close the added pane. Check that the draft is preserved. Do not submit it just to test the app.
4. Exit all windows and relaunch. Check pane URLs, split proportions and login persistence.
5. Focus the web page and try the split shortcuts, Ctrl+N and Ctrl+Shift+N. Check that the active pane is used.
6. Move windows between monitors with different scaling, maximize one, then exit all windows and relaunch. Disconnect a monitor and confirm every restored window is reachable.
7. Disconnect the network, refresh, reconnect, and select Retry.

These account- and hardware-specific checks are not a substitute for the automated fixture tests.

## Project layout

```text
multigpt/
  App.xaml / App.xaml.cs         startup and single-instance routing
  MainWindow.xaml / .cs          split workspace, toolbar and shortcuts
  Controls/ChatPane.xaml / .cs   independent browser and sidebar drop targets
  Models/AppSettings.cs         serialized window and split state
  Services/                    shared environment, settings, bounds and logs
  tests/                       deterministic and live desktop smoke tests
  ChatGPTMulti.csproj / .sln    project and Visual Studio solution
```

Implementation references: Microsoft's [WebView2 profile storage](https://learn.microsoft.com/microsoft-edge/webview2/concepts/user-data-folder), [popup deferrals and threading](https://learn.microsoft.com/microsoft-edge/webview2/concepts/threading-model), and [WPF accelerator forwarding](https://learn.microsoft.com/dotnet/api/microsoft.web.webview2.wpf.webview2.onkeydown).
