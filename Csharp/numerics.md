# MathNet.Numerics
Install with NuGet. Check out all this stuff: https://numerics.mathdotnet.com/api/MathNet.Numerics.Statistics/Statistics.htm

```cs
using MathNet.Numerics.Statistics;
```

```cs
mean = Statistics.Mean(values);
stdev = Statistics.StandardDeviation(values);
stdErr = stdev / Math.Sqrt(values.Length);
```
