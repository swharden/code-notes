# Read WAV files with C#

```cs
private double[] ReadWavFile(string wavFilePath)
{
    // quick and drity WAV file reader (16-bit signed format)
    byte[] bytes = System.IO.File.ReadAllBytes(wavFilePath);
    double[] pcm = new double[bytes.Length / 2];
    int firstDataByte = 44;
    for (int i = firstDataByte; i < bytes.Length - 2; i += 2)
        pcm[i] = BitConverter.ToInt16(bytes, i);
    return pcm;
}
```
