using System.IO;

namespace ChatGPTMulti.Services;

public sealed class AppLog(string directory)
{
    private readonly object _gate = new();

    public void Write(string message, Exception? error = null)
    {
        // Exception messages, stack traces, URLs and page titles may contain private data.
        string detail = error is null ? "" : $" [{error.GetType().Name}, 0x{error.HResult:X8}]";
        lock (_gate)
        {
            try
            {
                Directory.CreateDirectory(directory);
                string path = Path.Combine(directory, $"app-{DateTime.UtcNow:yyyy-MM-dd}.log");
                if (File.Exists(path) && new FileInfo(path).Length > 2 * 1024 * 1024)
                    File.Move(path, path + ".previous", true);
                File.AppendAllText(path, $"{DateTime.UtcNow:O} {message}{detail}{Environment.NewLine}");
                foreach (var file in new DirectoryInfo(directory).EnumerateFiles("app-*.log*")
                             .Where(f => f.LastWriteTimeUtc < DateTime.UtcNow.AddDays(-14)))
                    file.Delete();
            }
            catch (Exception ex) when (ex is IOException or UnauthorizedAccessException)
            {
                // Logging must not prevent a window from opening or closing.
            }
        }
    }
}
