# TIF/TIFF File Analysis in Csharp

https://github.com/swharden/Csharp-Data-Visualization/blob/15efb63ef64754dd410e1c7bc1e28ba15a6558b6/projects/18-01-10_fast_pixel_bitmap/readme.md

## Guess Bit-Depth from Data
```cs
public int GuessDepth(double whitestPixelValue)
{
    int depth = 1;
    while (Math.Pow(2, depth) < whitestPixelValue)
        depth++;
    return depth;
}
```

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

### Arbitrary Bit Depths
```cs
/// <summary>
/// Generate an 8-bit grayscale image suitable for display.
/// Returned data may be degraded due to quantization error.
/// </summary>
public Bitmap GetBitmapForDisplay(int frameNumber = 0)
{
    // ensure a TIF is loaded
    if (decoder == null) return null;

    // select the frame (channel or slice) we want
    if (frameNumber >= decoder.Frames.Count) return null;

    // prepare variables which will be useful later
    int sourceImageDepth = bitmapSource.Format.BitsPerPixel;
    int bytesPerPixel = sourceImageDepth / 8;
    int width = bitmapSource.PixelWidth;
    int height = bitmapSource.PixelHeight;
    int stride = width * bytesPerPixel;
    int imageByteCount = height * width * bytesPerPixel;
    int pixelCount = width * height;

    // fill our byte array with source data
    byte[] bytesSource = new byte[imageByteCount];
    bitmapSource.CopyPixels(bytesSource, stride, 0);

    // Fill an int array with data from the byte array according to bytesPerPixel
    int[] valuesSource = new int[pixelCount];
    for (int i = 0; i < valuesSource.Length; i++)
    {
        int bytePosition = i * bytesPerPixel;
        for (int byteNumber = 0; byteNumber < bytesPerPixel; byteNumber++)
        {
            valuesSource[i] += bytesSource[bytePosition + byteNumber] << (byteNumber * 8);
        }
    }

    // determine the range of intensity data
    int pixelValueMax = valuesSource.Max();
    int pixelValueMin = valuesSource.Min();
    log.Debug($"pixel value max: {pixelValueMax}");
    log.Debug($"pixel value min: {pixelValueMin}");

    // predict what bit depth we have based upon pixelValueMax
    int dataDepth = 1;
    while (Math.Pow(2, dataDepth) < pixelValueMax)
        dataDepth++;                
    log.Debug($"detected data depth: {dataDepth}-bit");

    // determine if we will use the original bit depth or our guessed bit depth
    bool use_detected_camera_depth = true; // should this be an argument?
    if (!use_detected_camera_depth)
        dataDepth = sourceImageDepth;

    // create and fill a pixel array for the 8-bit final image
    byte[] pixelsOutput = new byte[height * width];
    for (int i = 0; i < pixelsOutput.Length; i++)
    {
        // start by loading the pixel value of the source
        int pixelValue = valuesSource[i];

        // upshift it to the nearest byte (if using a nonstandard depth)
        pixelValue = pixelValue << (sourceImageDepth - dataDepth);

        // downshift it as needed to ensure the MSB is in the lowest 8 bytes
        pixelValue = pixelValue >> (sourceImageDepth-8);

        // conversion to 8-bit should be now nondestructive
        pixelsOutput[i] = (byte)(pixelValue);
    }

    // create the output bitmap (8-bit indexed color)
    var format = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
    Bitmap bmp = new Bitmap(width, height, format);

    // Create a grayscale palette, although other colors and LUTs could go here
    ColorPalette pal = bmp.Palette;
    for (int i = 0; i < 256; i++)
        pal.Entries[i] = System.Drawing.Color.FromArgb(255, i, i, i);
    bmp.Palette = pal;

    // copy the new pixel data into the data of our output bitmap
    var rect = new Rectangle(0, 0, width, height);
    BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadOnly, format);
    Marshal.Copy(pixelsOutput, 0, bmpData.Scan0, pixelsOutput.Length);
    bmp.UnlockBits(bmpData);

    return bmp;
}
```
