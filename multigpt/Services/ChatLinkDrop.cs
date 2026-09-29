using System.IO;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows;

namespace ChatGPTMulti.Services;

public static class ChatLinkDrop
{
    private const int MaximumLength = 64 * 1024;
    private static readonly string[] Formats =
        ["UniformResourceLocatorW", "UniformResourceLocator", "text/uri-list", DataFormats.UnicodeText, DataFormats.Text, DataFormats.Html];

    public static string? Read(IDataObject data)
    {
        try
        {
            foreach (string format in Formats)
            {
                if (!data.GetDataPresent(format, false)) continue;
                var value = data.GetData(format, false);
                string? text = value as string;
                if (value is MemoryStream stream && stream.Length <= MaximumLength)
                    text = (format == "UniformResourceLocatorW" ? Encoding.Unicode : Encoding.UTF8).GetString(stream.ToArray());
                if (text is null || text.Length > MaximumLength) continue;
                if (format == DataFormats.Html)
                {
                    var match = Regex.Match(text, "<a\\b[^>]*\\bhref\\s*=\\s*[\"'](?<url>[^\"']+)[\"']",
                        RegexOptions.IgnoreCase | RegexOptions.CultureInvariant, TimeSpan.FromMilliseconds(100));
                    text = match.Success ? WebUtility.HtmlDecode(match.Groups["url"].Value) : "";
                }
                foreach (var line in text.Split(['\r', '\n', '\0'], StringSplitOptions.RemoveEmptyEntries))
                {
                    string candidate = line.Trim();
                    if (IsConversation(candidate)) return new Uri(candidate).AbsoluteUri;
                }
            }
        }
        catch (Exception ex) when (ex is COMException or ExternalException or IOException or ArgumentException or RegexMatchTimeoutException)
        {
            // A drag source can disappear or supply an unsupported payload during a drag.
        }
        return null;
    }

    public static bool IsConversation(string? url)
    {
        if (!NavigationPolicy.IsChatGpt(url) || NavigationPolicy.IsAuthentication(url)) return false;
        var segments = new Uri(url!).AbsolutePath.Split('/', StringSplitOptions.RemoveEmptyEntries);
        return Enumerable.Range(0, Math.Max(0, segments.Length - 1)).Any(i => segments[i] is "c" or "share");
    }
}
