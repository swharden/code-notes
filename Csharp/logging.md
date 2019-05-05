# Logging

## Override Debug.WriteLine() with a Logging Version
This is my preferred method for debug logging. I create a custom trace listening class and use it to intercept `Debug.WriteLine()`. The custom class records messages for easy retrieval later.

```cs
// define this as a class-level object
public AbfBrowser.LoggingTraceListener debugListener; 
```

```cs
// put this in your initializer
debugListener = new AbfBrowser.LoggingTraceListener();
System.Diagnostics.Debug.Listeners.Add(debugListener);
```

```cs
// log like you regularly do
Debug.WriteLine("line one");
Debug.Indent();
Debug.WriteLine("line two");
```

```cs
// access historical messages like this
textbox1.Text = debugListener.GetLogAsString();
```

### LoggingTraceListener.cs
```cs
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbfBrowser
{

    public class LoggingTraceListener : TraceListener
    {
        private List<string> Log;
        public new readonly string Name;

        public LoggingTraceListener(string name = "unnamed LoggingTraceListener")
        {
            Name = name;
            Log = new List<string>();
        }

        public override void Write(string message)
        {
            throw new NotImplementedException();
        }

        public override void WriteLine(string message)
        {
            string timestamp = string.Format("[{0}] ", DateTime.Now.ToString());
            Log.Add($"{timestamp} | {Name} | {message}");
        }

        public string[] GetLogAsArray()
        {
            return Log.ToArray();
        }

        public string GetLogAsString(string joiner = "\r\n")
        {
            return string.Join(joiner, Log.ToArray());
        }
    }
}
```

## Console Messages

```cs
System.Console.WriteLine("just writes to console");
System.Diagnostics.Trace.WriteLine("trace listener catches these");
System.Diagnostics.Debug.WriteLine("trace listener catches these");
```

## Logger Class

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
