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
