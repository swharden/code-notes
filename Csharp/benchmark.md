# Benchmarking in C#

I like making a class which starts timing in the initializer and stops the clock and displays the elapsed time in the destructor.

```cs
public class Benchmark : IDisposable
{
	Stopwatch stopwatch;
	bool silent;

	public Benchmark(bool silent = false)
	{
		stopwatch = Stopwatch.StartNew();
		this.silent = silent;
	}

	public double elapsedMilliseconds
	{
		get
		{
			return stopwatch.ElapsedTicks * 1000.0 / Stopwatch.Frequency;
		}
	}

	public void Dispose()
	{
		stopwatch.Stop();
		if (!silent)
			Console.WriteLine(string.Format("completed in {0:0.00} ms", elapsedMilliseconds));
	}
}
```

```cs
using (var benchmark = new Spectrogram.Benchmark())
{
    // do stuff
}
```
