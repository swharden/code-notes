# Filtering

## Discrete 1D Gaussian Filter
```C#
/// <summary>
/// Return a filtered version of the input array (with the same number of points)
/// </summary>
public double[] GaussianFilter1d(double[] data, int degree = 5)
{
if (degree < 2)
    return data;

double[] smooth = new double[data.Length];

// create a gaussian windowing function
int windowSize = degree * 2 - 1;
double[] kernel = new double[windowSize];
for (int i = 0; i < windowSize; i++)
{
    int pos = i - degree + 1;
    double frac = i / (double)windowSize;
    double gauss = 1.0 / Math.Exp(Math.Pow(4 * frac, 2)); // TODO: why 4?
    kernel[i] = gauss * windowSize;
}

// normalize the kernel (so area is 1)
double weightSum = kernel.Sum();
for (int i = 0; i < windowSize; i++)
    kernel[i] = kernel[i] / weightSum;

// apply the window
for (int i = 0; i < smooth.Length; i++)
{
    if (i > kernel.Length && i < smooth.Length - kernel.Length)
    {
        double smoothedValue = 0;
        for (int j = 0; j < kernel.Length; j++)
        {
            smoothedValue += kernel[j] * data[i + j];
        }
        smooth[i] = smoothedValue;
    }
    else
    {
        smooth[i] = data[i];
    }
}

// blank-out values outside the smoothing range
int firstValidPoint = kernel.Length;
int lastValidPoint = smooth.Length - kernel.Length;

for (int i = 0; i < firstValidPoint; i++)
    smooth[i] = smooth[firstValidPoint];

for (int i = lastValidPoint; i < smooth.Length; i++)
    smooth[i] = smooth[lastValidPoint];

return smooth;
}
```
