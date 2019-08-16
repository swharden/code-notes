# FFT
The [numerics math.NET libraries](https://numerics.mathdotnet.com) seem so much better than naudio, especially for iFFT

## FFT Low Pass Filter (Math.NET)
```cs
private double[] LowPassFilter(double[] pcm, double cutOffFrequency = 60, double sampleRate = 44100)
{
    // it really should be a power of 2
    int fft_size = pcm.Length;

    // create a complex data object we will use to shuffle data around
    MathNet.Numerics.Complex32[] complex = new MathNet.Numerics.Complex32[fft_size];

    // load original PCM data into the complex array
    for (int i = 0; i < fft_size; i++)
    {
        float val = (float)pcm[i]; // times hamming?
        complex[i] = new MathNet.Numerics.Complex32(val,0);
    }

    // perform the forward FFT
    MathNet.Numerics.IntegralTransforms.Fourier.Forward(complex);

    // blank-out the high frequency stuff
    for (int i = 0; i < fft_size/2; i++)
    {
        double freq = (double)(i * sampleRate * 2) / fft_size;
        if (i == fft_size / 2 - 1) System.Console.WriteLine(freq);
        if (freq < cutOffFrequency) continue;
        complex[i] = new MathNet.Numerics.Complex32(0, 0);
        complex[fft_size-i-1] = new MathNet.Numerics.Complex32(0, 0);
    }

    // perform the inverse FFT
    MathNet.Numerics.IntegralTransforms.Fourier.Inverse(complex);

    // extract the real component into the original PCM array and return it
    for (int i = 0; i < fft_size; i++) pcm[i] = complex[i].Real;

    return pcm;
}
```

## Update FFT from PCM
Assumes a class-level `dataPcm` and `dataFft` double arrays are present.
```cs
private void updateFFT()
{
    if (dataPcm == null)
        return;

    int fftPoints = 2;
    while (fftPoints * 2 <= dataPcm.Length)
        fftPoints *= 2;

    NAudio.Dsp.Complex[] fftFull = new NAudio.Dsp.Complex[fftPoints];
    for (int i = 0; i < fftPoints; i++)
        fftFull[i].X = (float)(dataPcm[i] * NAudio.Dsp.FastFourierTransform.HammingWindow(i, fftPoints));

    NAudio.Dsp.FastFourierTransform.FFT(true, (int)Math.Log(fftPoints, 2.0), fftFull);

    if (dataFft == null)
        dataFft = new double[fftPoints / 2];
    for (int i = 0; i < fftPoints / 2; i++)
    {
        double fftLeft = Math.Abs(fftFull[i].X + fftFull[i].Y);
        double fftRight = Math.Abs(fftFull[fftPoints - i - 1].X + fftFull[fftPoints - i - 1].Y);
        dataFft[i] = fftLeft + fftRight;
    }
}
```


## FFT from Double Array (NAudio) - COPIES DATA = SLOW
```cs
private double[] FFT_from_PCM(double[] pcm)
{

    // use the largest FFT size we can given the data (must be a power of 2)
    int fftPoints = 2;
    while (fftPoints * 2 <= pcm.Length)
        fftPoints *= 2;

    // prepare the complex data which will be FFT'd (using a window function)
    NAudio.Dsp.Complex[] fftFull = new NAudio.Dsp.Complex[fftPoints];
    for (int i = 0; i < fftPoints; i++)
        fftFull[i].X = (float)(pcm[i] * NAudio.Dsp.FastFourierTransform.HammingWindow(i, fftPoints));

    // perform the FFT
    NAudio.Dsp.FastFourierTransform.FFT(true, (int)Math.Log(fftPoints, 2.0), fftFull);

    // average (sum) the mirror image frequency powers
    double[] fft = new double[fftPoints/2];
    for (int i = 0; i < fftPoints/2; i++)
    {
        double fftLeft = Math.Abs(fftFull[i].X + fftFull[i].Y);
        double fftRight = Math.Abs(fftFull[fftPoints-i-1].X + fftFull[fftPoints-i-1].Y);
        fft[i] = fftLeft+ fftRight;
    }

    return fft;
}
```


## With NAudio (light)
[example project: spectrograph](/projects/18-01-11_microphone_spectrograph)

```c#
using NAudio.Wave; // for sound card access
using NAudio.Dsp; // for FastFourierTransform
```

```c#
// prepare the complex data which will be FFT'd
Complex[] fft_buffer = new Complex[fft_size];
for (int i=0; i < fft_size; i++)
{
    fft_buffer[i].X = (float)(unanalyzed_values[i] * FastFourierTransform.HammingWindow(i, fft_size));
    fft_buffer[i].Y = 0;
}

// perform the FFT
FastFourierTransform.FFT(true, (int)Math.Log(fft_size, 2.0), fft_buffer);

// a list with FFT values
List<double> new_data = new List<double>();
for (int i = 0; i < spec_data[spec_data.Count - 1].Count; i++)
{
    // should this be sqrt(X^2+Y^2)?
    double val;
    val = (double)fft_buffer[i].X + (double)fft_buffer[i].Y;
    val = Math.Abs(val);
    if (checkBox1.Checked) val = Math.Log(val);
    new_data.Add(val);
}
```

## With Accord (heavy)
Here is a minimal-case example how to convert an array of doubles into the frequency domain using a [Fast Fourier transformation](https://en.wikipedia.org/wiki/Fast_Fourier_transform) in C# (Visual Studio Community 2017). It uses the [Accord .NET library](http://accord-framework.net). Add a reference to the Assembly Framework `System.Numerics`. Use NuGet to install `Accord.Audio`. [example project: microphone FFT](/projects/17-07-16_microphone)
```C#
using System.Numerics;

public double[] FFT(double[] data)
{
    int nPoints = data.Length; // whatever we measure must be a power of 2
    for (int i = 0; i < data.Length; i++) data[i] = Math.Sin(i); // fill it with some data
    double[] fft = new double[nPoints]; // this is where we will store the output (fft)
    Complex[] fftComplex = new Complex[nPoints]; // the FFT function requires complex format
    for (int i = 0; i < data.Length; i++)
        fftComplex[i] = new Complex(data[i], 0.0); // make it complex format
    Accord.Math.FourierTransform.FFT(fftComplex, Accord.Math.FourierTransform.Direction.Forward);
    for (int i = 0; i < data.Length; i++)
        fft[i] = fftComplex[i].Magnitude; // back to double
    return fft;
    //todo: this could be much faster by reusing variables
}
```
