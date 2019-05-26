# Audio / Soundcard
Unless otherwise specified, audio access is provided by "NAudio". This can be installed with NuGet.

## List Audio Devices

```cs
private void ScanSoundCards()
{
    cbDevice.Items.Clear();
    for (int i = 0; i < NAudio.Wave.WaveIn.DeviceCount; i++)
        cbDevice.Items.Add(NAudio.Wave.WaveIn.GetCapabilities(i).ProductName);
    if (cbDevice.Items.Count > 0)
        cbDevice.SelectedIndex = 0;
    else
        MessageBox.Show("ERROR: no recording devices available");
}
```

## Recording Audio data with NAudio
```cs
private NAudio.Wave.WaveInEvent wvin;

private void OnDataAvailable(object sender, NAudio.Wave.WaveInEventArgs args)
{
    int bytesPerSample = wvin.WaveFormat.BitsPerSample / 8;
    int samplesRecorded = args.BytesRecorded / bytesPerSample;
    Int16[] lastBuffer = new Int16[samplesRecorded];
    for (int i = 0; i < samplesRecorded; i++)
        lastBuffer[i] = BitConverter.ToInt16(args.Buffer, i * bytesPerSample);
    int lastBufferAmplitude = lastBuffer.Max() - lastBuffer.Min();
    Console.WriteLine(lastBufferAmplitude);
}

private void AudioMonitorInitialize(int DeviceIndex, int sampleRate = 8000, int bitRate = 16, 
    int channels = 1, int bufferMilliseconds = 100, bool start = true)
{
    if (wvin == null)
    {
        wvin = new NAudio.Wave.WaveInEvent();
        wvin.DeviceNumber = DeviceIndex;
        wvin.WaveFormat = new NAudio.Wave.WaveFormat(sampleRate, bitRate, channels);
        wvin.DataAvailable += OnDataAvailable;
        wvin.BufferMilliseconds = bufferMilliseconds;
        if (start)
            wvin.StartRecording();
    }
}

private void BtnStart_Click(object sender, EventArgs e)
{
    AudioMonitorInitialize(cbDevice.SelectedIndex);
}

private void BtnStop_Click(object sender, EventArgs e)
{
    if (wvin!= null)
    {
        wvin.StopRecording();
        wvin = null;
    }
}
```

## Linearize a Circular Buffer
```cs
public double[] GetLinearPcmData()
{
    int indexSplit = nextBufferToFill * bufferSampleCount;
    double[] data = new double[pcmDataCircular.Length];
    for (int i = 0; i < indexSplit; i++)
        data[pcmDataCircular.Length - indexSplit + i] = pcmDataCircular[i];
    for (int i = 0; i < data.Length - indexSplit; i++)
        data[i] = pcmDataCircular[i + indexSplit];
    return data;
}
```
