using System.IO;

namespace ChatGPTMulti.Services;

public sealed record AppPaths(string ProfileDirectory, string SettingsFile, string LogDirectory)
{
    public static AppPaths Default => new(
        Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "ChatGPTMulti", "WebView2"),
        Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "ChatGPTMulti", "settings.json"),
        Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "ChatGPTMulti", "Logs"));
}
