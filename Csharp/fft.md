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

## FFT from Double Array (NAudio)
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
