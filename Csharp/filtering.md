# Filtering

## Low-Pass Gaussian
```C#

private double[] LowPassGauss(double[] pcm, int sigma=100)
{
    int windowSize = (int)(sigma * 2 - 1);
    if (pcm.Length <= windowSize || sigma <= 0) return pcm;

    // create the bell curve (kernel)
    double[] kernel = new double[windowSize];
    for (int i = 0; i < windowSize; i++)
    {
        double j = i - sigma + 1;
        double frac = j / windowSize;
        double val = 1 / (Math.Exp(Math.Pow((4 * (frac)), 2)));
        kernel[i] = val;
    }

    double[] smoothed = new double[pcm.Length - kernel.Length];
    for (int i=0; i<pcm.Length-kernel.Length; i++)
    {
        double sum = 0;
        for (int j=0; j<kernel.Length; j++)
        {
            sum += pcm[i + j]*kernel[j];
        }
        smoothed[i] = sum / kernel.Length;
    }
    return smoothed;
}
```

## Recreated (doh!)
```cs
public double[] GaussianFilter1d(double[] data, int degree = 10)
{
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

    // applt the window
    for (int i = 0; i < smooth.Length; i++)
    {
        smooth[i] = data[i];
        if (i > kernel.Length && i < smooth.Length - kernel.Length)
        {
            double smoothedValue = 0;
            for (int j = 0; j<kernel.Length; j++)
            {
                smoothedValue += kernel[j] * data[i + j];
            }
            smooth[i] = smoothedValue;
        }
    }

    return smooth;
}
```
