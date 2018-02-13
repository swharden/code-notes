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
private double[] FFT_from_PCM(double[] pcm, bool logScale=false)
{

    // use the largest FFT size we can given the data
    int fft_size = 2;
    while (fft_size * 2 <= pcm.Length) fft_size *= 2;

    // prepare the complex data which will be FFT'd
    NAudio.Dsp.Complex[] fft_buffer = new NAudio.Dsp.Complex[fft_size];
    for (int i = 0; i < fft_size; i++)
    {
        fft_buffer[i].X = (float)(pcm[i] * NAudio.Dsp.FastFourierTransform.HammingWindow(i, fft_size));
        fft_buffer[i].Y = 0;
    }

    // perform the FFT
    NAudio.Dsp.FastFourierTransform.FFT(true, (int)Math.Log(fft_size, 2.0), fft_buffer);

    // a list with FFT values
    List<double> fft = new List<double>();
    for (int i = 0; i < fft_size; i++)
    {
        // should this be sqrt(X^2+Y^2)?
        double val;
        val = (double)fft_buffer[i].X + (double)fft_buffer[i].Y;
        val = Math.Abs(val);
        if (logScale) val = Math.Log(val);
        fft.Add(val);
    }

    return fft.ToArray();
}
```
