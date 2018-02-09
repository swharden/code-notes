# FFT

## FFT from Double Array
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
