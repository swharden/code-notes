# TIF/TIFF File Analysis in Csharp

https://github.com/swharden/Csharp-Data-Visualization/blob/15efb63ef64754dd410e1c7bc1e28ba15a6558b6/projects/18-01-10_fast_pixel_bitmap/readme.md

## TiffBitmapDecoder
* [tiffbitmapdecoder](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.tiffbitmapdecoder?view=netframework-4.7.2)
* [bitmapframe](https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.imaging.bitmapframe?view=netframework-4.7.2)

```cs
// add the "Presentation Core" assembly to access this
using System.Windows.Media;
using System.Windows.Media.Imaging;

string tifFilePath = splitDirView1.highlightedFile;
lblFileName.Text = System.IO.Path.GetFileName(tifFilePath);

richTextBox1.Clear();
log($"LOADING TIF: {tifFilePath}");

// open a file stream and keep it open until we're done reading the file
Stream stream = new FileStream(tifFilePath, FileMode.Open, FileAccess.Read, FileShare.Read);

// carefully open the file to see if it will decode
TiffBitmapDecoder decoder;
try
{
    decoder = new TiffBitmapDecoder(stream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
}
catch
{
    log($"TiffBitmapDecoder crashed");
    return;
}

// determine how many single images are in this TIF
int nFrames = decoder.Frames.Count;
log($"number of frames: {nFrames}");

// pull the first frame and inspect it
BitmapSource bitmapSource = decoder.Frames[0];
log($"Image depth: {bitmapSource.Format.BitsPerPixel}");
log($"image width: {bitmapSource.PixelWidth}");
log($"image height: {bitmapSource.PixelHeight}");
stream.Dispose();
```
