# Read MP3 Files with C#

```cs
public static float[] ReadMp3(string mp3FilePath, int? sampleLimit = null)
{
    string actualPath = FindFile(mp3FilePath);
    var reader = new NAudio.Wave.Mp3FileReader(actualPath);
    int bytesToRead = (int)reader.Length;
    if (sampleLimit != null)
        bytesToRead = Math.Min(bytesToRead, (int)sampleLimit * 2);
    byte[] bytes = new byte[bytesToRead];
    reader.Read(bytes, 0, bytesToRead);
    float[] pcm = FloatsFromBytesINT16(bytes);
    return pcm;
}
```

```cs
public static float[] FloatsFromBytesINT16(byte[] bytes, int skipFirstBytes = 0)
{
    float[] pcm = new float[(bytes.Length - skipFirstBytes) / 2];
    for (int i = skipFirstBytes; i < bytes.Length - 2; i += 2)
    {
        if (i / 2 >= pcm.Length)
            break;
        pcm[i / 2] = BitConverter.ToInt16(bytes, i);
    }
    return pcm;
}
```
