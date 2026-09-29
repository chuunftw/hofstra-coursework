using System.IO;
using Microsoft.Web.WebView2.Core;

namespace ChatGPTMulti.Services;

public sealed class WebViewManager(AppPaths paths, AppLog log)
{
    private Task<CoreWebView2Environment>? _environment;
    public Task<CoreWebView2Environment> GetEnvironmentAsync() => _environment ??= CreateAsync();

    private async Task<CoreWebView2Environment> CreateAsync()
    {
        Directory.CreateDirectory(paths.ProfileDirectory);
        var environment = await CoreWebView2Environment.CreateAsync(null, paths.ProfileDirectory);
        log.Write("Shared WebView2 environment initialized.");
        return environment;
    }
}
