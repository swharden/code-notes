# TIF/TIFF File Analysis in Csharp

```cs
// add the "Presentation Core" assembly to access this
using System.Windows.Media;
using System.Windows.Media.Imaging;
```

## TiffBitmapDecoder
* [tiffbitmapdecoder](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.tiffbitmapdecoder?view=netframework-4.7.2)
* [bitmapframe](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.bitmapframe?view=netframework-4.7.2)

```cs
string tifFilePath = splitDirView1.highlightedFile;
lblFileName.Text = System.IO.Path.GetFileName(tifFilePath);

Console.WriteLine($"\nLOADING TIF: {tifFilePath}");

TiffBitmapDecoder decoder;
BitmapSource bitmapSource;
try
{
    Stream stream;
    stream = new FileStream(tifFilePath, FileMode.Open, FileAccess.Read, FileShare.Read);
    decoder = new TiffBitmapDecoder(stream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
    bitmapSource = decoder.Frames[0];
    stream.Dispose();
}
catch
{
    Console.WriteLine($"crash while loading TIF");
    return;
}

for (int i = 0; i < decoder.Frames.Count; i++)
{
    Console.WriteLine($"Slice {i} shape ({bitmapSource.PixelWidth},{bitmapSource.PixelHeight})");
}
```
