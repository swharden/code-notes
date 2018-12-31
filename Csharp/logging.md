# Logging

You could use a third party library. Or this.

```cs
public class ScottLog
{
    private enum LogLevel { DEBUG, INFO, WARN, CRITICAL };
    public static bool silent = false;
    public static string logText = "";
    public string logName;
    private static long timeStart = 0;
    public static long timeLast = 0;
    public ScottLog(string logName)
    {
        this.logName = logName;
        if (timeStart == 0) timeStart = DateTime.Now.Ticks;
    }
    public string GetLogText() { return logText.Trim(); }
    public void Debug(string message) { Log(message, logName, LogLevel.DEBUG); }
    public void Info(string message) { Log(message, logName, LogLevel.INFO); }
    public void Warn(string message) { Log(message, logName, LogLevel.WARN); }
    public void Critical(string message) { Log(message, logName, LogLevel.CRITICAL); }
    private static void Log(string message, string logName, LogLevel logLevel)
    {
        string dateAndTime = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        string[] logLevelNames = { "DEBUG", "INFO", "WARN", "CRITICAL" };
        string logLevelName = logLevelNames[(int)logLevel];
        double timeFromStart = (double)(DateTime.Now.Ticks - timeStart) / TimeSpan.TicksPerMillisecond;
        string timeFromStartStr = string.Format("{0:0.00} ms", timeFromStart);
        double timeFromLast = (double)(DateTime.Now.Ticks - timeLast) / TimeSpan.TicksPerMillisecond;
        string timeFromlastStr = string.Format("{0:0.00} ms", timeFromLast);
        message = (message == "benchmark") ? $"completed in {timeFromlastStr}" : message;
        //string logLine = $"[{dateAndTime}] {logName} ({logLevelName}): {message}";
        string logLine = $"[{timeFromStartStr}] {logName} ({logLevelName}): {message}";
        logText = logText + logLine + "\n";
        if (!silent) System.Console.WriteLine(logLine);
        timeLast = DateTime.Now.Ticks;
    }
}
```
