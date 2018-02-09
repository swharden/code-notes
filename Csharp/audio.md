# Audio / Soundcard
Unless otherwise specified, audio access is provided by "NAudio". This can be installed with NuGet.

## List Audio Devices

```cs
cmb_audio_device.Items.Clear();

for (int waveInDevice = 0; waveInDevice < NAudio.Wave.WaveIn.DeviceCount; waveInDevice++)
{
    NAudio.Wave.WaveInCapabilities deviceInfo = NAudio.Wave.WaveIn.GetCapabilities(waveInDevice);
    cmb_audio_device.Items.Add(deviceInfo.ProductName);
}

if (cmb_audio_device.Items.Count > 0) cmb_audio_device.SelectedIndex = 0;
else MessageBox.Show("ERROR: no recording devices available");
```
