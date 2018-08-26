# Logging

You could use a third party library. Or this.

```cs

public class LogLevel
{
    public const int DEBUG = 0;
    public const int INFO = 1;
    public const int WARN = 2;
    public const int CRITICAL = 3;
}

public class Logger
{
    public int logLevel;
    public bool silent = false;
    public string logText = "";
    public Logger(int logLevel = LogLevel.DEBUG)
    {
        this.logLevel = logLevel;
    }

    public void Debug(string message){Log(message, LogLevel.DEBUG);}
    public void Info(string message){Log(message, LogLevel.INFO);}
    public void Warn(string message){Log(message, LogLevel.WARN);}
    public void Critical(string message){Log(message, LogLevel.CRITICAL);}

    private void Log(string message, int logLevel)
    {
        if (logLevel > LogLevel.CRITICAL)
            logLevel = LogLevel.CRITICAL;
        if (logLevel < LogLevel.DEBUG)
            logLevel = LogLevel.DEBUG;

        string timestamp = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        string[] logLevelNames = { "DEBUG", "INFO", "WARN", "CRITICAL" };
        string logLevelName = logLevelNames[logLevel];
        string logLine = $"[{timestamp}] ({logLevelName}): {message}";
        logText = logText + logLine + "\n";
        if (!this.silent)
            System.Console.WriteLine(logLine);
    }
}
```
