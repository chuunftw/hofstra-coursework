using System.Security.Cryptography;
using System.Text;

namespace ChatGPTMulti.Services;

internal sealed class SingleInstance : IDisposable
{
    private readonly Mutex _mutex;
    private readonly EventWaitHandle _newWindow;
    private RegisteredWaitHandle? _wait;
    public bool IsPrimary { get; }

    public SingleInstance(string profilePath)
    {
        string id = Convert.ToHexString(SHA256.HashData(Encoding.UTF8.GetBytes(profilePath.ToUpperInvariant())))[..24];
        _mutex = new Mutex(false, "Local\\ChatGPTMulti-" + id);
        _newWindow = new EventWaitHandle(false, EventResetMode.AutoReset, "Local\\ChatGPTMulti-NewWindow-" + id);
        try { IsPrimary = _mutex.WaitOne(0); }
        catch (AbandonedMutexException) { IsPrimary = true; }
    }

    public void RequestWindow() => _newWindow.Set();
    public void Listen(Action callback) => _wait = ThreadPool.RegisterWaitForSingleObject(
        _newWindow, (_, _) => callback(), null, Timeout.Infinite, false);

    public void Dispose()
    {
        _wait?.Unregister(null);
        _newWindow.Dispose();
        if (IsPrimary) _mutex.ReleaseMutex();
        _mutex.Dispose();
    }
}
