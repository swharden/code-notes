# Time Operations

## Timing things with high resolution
```C#
System.Diagnostics.Stopwatch stopwatch = System.Diagnostics.Stopwatch.StartNew();

stopwatch.Reset();
stopwatch.Start();
// do something
stopwatch.Stop();

double timeMS = stopwatch.ElapsedTicks * 1000.0 / System.Diagnostics.Stopwatch.Frequency;

System.Console.WriteLine(string.Format("loaded in {1:0.00} ms", timeMS));
```
