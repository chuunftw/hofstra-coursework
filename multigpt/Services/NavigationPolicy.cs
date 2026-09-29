namespace ChatGPTMulti.Services;

public static class NavigationPolicy
{
    public const string Home = "https://chatgpt.com/";

    public static bool IsWebUrl(string? value) => Uri.TryCreate(value, UriKind.Absolute, out var uri)
        && uri.Scheme is "https" or "http" && string.IsNullOrEmpty(uri.UserInfo);

    private static bool HostMatches(string host, string domain) =>
        host.Equals(domain, StringComparison.OrdinalIgnoreCase)
        || host.EndsWith("." + domain, StringComparison.OrdinalIgnoreCase);

    public static bool IsChatGpt(string? value) => Uri.TryCreate(value, UriKind.Absolute, out var uri)
        && uri.Scheme == "https" && uri.IsDefaultPort && string.IsNullOrEmpty(uri.UserInfo)
        && HostMatches(uri.IdnHost, "chatgpt.com");

    public static bool IsAuthentication(string? value)
    {
        if (!Uri.TryCreate(value, UriKind.Absolute, out var uri) || uri.Scheme != "https") return false;
        string host = uri.IdnHost;
        return HostMatches(host, "openai.com") || HostMatches(host, "auth0.com")
            || host is "accounts.google.com" or "login.microsoftonline.com" or "login.live.com" or "appleid.apple.com"
            || (IsChatGpt(value) && IsSensitivePath(uri.AbsolutePath));
    }

    private static bool IsSensitivePath(string path) => new[] { "/auth", "/api", "/oauth", "/login", "/callback", "/cdn-cgi" }
        .Any(prefix => path.Equals(prefix, StringComparison.OrdinalIgnoreCase)
            || path.StartsWith(prefix + "/", StringComparison.OrdinalIgnoreCase));

    public static string PersistableUrl(string? value)
    {
        if (!IsChatGpt(value)) return Home;
        var uri = new Uri(value!);
        if (IsSensitivePath(uri.AbsolutePath)) return Home;
        // Authentication state can appear in query strings or fragments. Never serialize it.
        return uri.GetLeftPart(UriPartial.Path);
    }

    public static bool OpenExternally(string target, string current, bool userInitiated, bool redirect, bool popup) =>
        IsWebUrl(target) && !IsChatGpt(target) && !IsAuthentication(target)
        && !IsAuthentication(current) && userInitiated && !redirect && !popup;
}
