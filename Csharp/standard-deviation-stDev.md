# Standard Deviation in C#
I often find that a discrete standard deviation calculation function is much easier than relying on an external library (and the DLL/license that comes with it).

```cs
public static double GetMean(double[] values)
{
    return values.Sum() / values.Length;
}

public static double GetStDev(double[] values)
{
    double mean = GetMean(values);
    double sumVarianceSquared = 0;
    for (int i = 0; i < values.Length; i++)
    {
        double variance = Math.Abs(mean - values[i]);
        sumVarianceSquared += variance * variance;
    }
    double meanVarianceSquared = sumVarianceSquared / values.Length;
    return Math.Sqrt(meanVarianceSquared);
}
```

## Discrete Standard Deviation in Python
I compare this discrete calculator against [Numpy's std function](https://docs.scipy.org/doc/numpy/reference/generated/numpy.std.html)
```python
import numpy as np

def discreteStDev(values):
    mean = np.mean(values)
    variance = [np.abs(mean - x) for x in values]
    varianceSquared = [x*x for x in variance]
    return np.sqrt(np.mean(varianceSquared))

if __name__ == "__main__":
    values = np.arange(100)
    print(f"mean: {np.mean(values)}") # 49.5
    print(f"stdev: {np.std(values)}") # 28.86607004772212
    print(f"disct: {discreteStDev(values)}") # 28.86607004772212
```
