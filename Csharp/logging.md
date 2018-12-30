# Logging

You could use a third party library. Or this.

```cs
public enum LogLevel { DEBUG, INFO, WARN, CRITICAL };
public class ScottLog
{
    public static bool silent = false;
    public static string logText = "";
    public string logName;
    public ScottLog(string logName) { this.logName = logName; }
    public string GetLogText() { return logText.Trim(); }
    public void Debug(string message) { Log(message, logName, LogLevel.DEBUG); }
    public void Info(string message) { Log(message, logName, LogLevel.INFO); }
    public void Warn(string message) { Log(message, logName, LogLevel.WARN); }
    public void Critical(string message) { Log(message, logName, LogLevel.CRITICAL); }
    private static void Log(string message, string logName, LogLevel logLevel)
    {
        string timestamp = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        string[] logLevelNames = { "DEBUG", "INFO", "WARN", "CRITICAL" };
        string logLevelName = logLevelNames[(int)logLevel];
        string logLine = $"[{timestamp}] {logName} ({logLevelName}): {message}";
        logText = logText + logLine + "\n";
        if (!silent)
            System.Console.WriteLine(logLine);
    }
}
```
