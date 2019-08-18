# Benchmarking in C#

```cs
public class Benchmark : IDisposable
{
    System.Diagnostics.Stopwatch stopwatch;

    public Benchmark()
    {
        stopwatch = System.Diagnostics.Stopwatch.StartNew();
    }

    public void Dispose()
    {
        stopwatch.Stop();
        double elapsedMsec = stopwatch.ElapsedTicks * 1000.0 / System.Diagnostics.Stopwatch.Frequency;
        System.Console.WriteLine(string.Format("completed in {0:0.00} ms", elapsedMsec));
    }
}
```

```cs
using (var benchmark = new Spectrogram.Benchmark())
{
    // do stuff
}
```
