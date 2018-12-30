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
        double timeElapsed = (double)(DateTime.Now.Ticks - timeStart) / TimeSpan.TicksPerMillisecond;
        string timeElapsedStr = string.Format("{0:0.00} ms", timeElapsed);
        //string logLine = $"[{dateAndTime}] {logName} ({logLevelName}): {message}";
        string logLine = $"[{timeElapsedStr}] {logName} ({logLevelName}): {message}";
        logText = logText + logLine + "\n";
        if (!silent) System.Console.WriteLine(logLine);
    }
}
```
