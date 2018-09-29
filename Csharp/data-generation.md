# Data Generation

## Noisy Sine Wave
This is one of my favorite functions for testing data plotting and analysis in many programming languages:
```cs
/// <summary>
/// create a bunch of data points and fill them with a noisy sine wave
/// </summary>
double[] NoisySine(int nPoints = 1000, double cycles = 3)
{
    Random rnd = new Random();
    double[] data = new double[nPoints];
    for (int i = 0; i < data.Length; i++)
    {
        double frac = (double)i / nPoints;
        double value = Math.Sin(frac * 2 * Math.PI * cycles);

        double noise = rnd.NextDouble() * 2 - 1;
        noise /= 10;

        data[i] = value + noise;
    }
    return data;
}
```
