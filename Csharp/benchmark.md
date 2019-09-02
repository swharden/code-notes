# Benchmarking in C#

I like making a class which starts timing in the initializer and stops the clock and displays the elapsed time in the destructor.

```cs
public class Benchmark : IDisposable
{
	System.Diagnostics.Stopwatch stopwatch;
	bool silent;

	public Benchmark(bool silent = false)
	{
		stopwatch = System.Diagnostics.Stopwatch.StartNew();
		this.silent = silent;
	}

	public double elapsedMilliseconds
	{
		get
		{
			return stopwatch.ElapsedTicks * 1000.0 / System.Diagnostics.Stopwatch.Frequency;
		}
	}

	public string GetMessage()
	{
		stopwatch.Stop();
		return string.Format("completed in {0:0.00} ms", elapsedMilliseconds);
	}

	public void Dispose()
	{
		stopwatch.Stop();
		if (!silent)
			Console.WriteLine(GetMessage());
	}
}
```

```cs
using (var benchmark = new Spectrogram.Benchmark())
{
    // do stuff
}
```
