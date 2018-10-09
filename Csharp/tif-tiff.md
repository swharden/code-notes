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

/// <summary>
/// This function takes a TIFF frame of any bit depth and returns a proper 8-bit bitmap
/// </summary>
private Bitmap LoadImageTiff(string path, int frameNumber = 0)
{
    //bmpPreview = new Bitmap(path);

    // open a file stream and keep it open until we're done reading the file
    Stream stream = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read);

    // carefully open the file to see if it will decode
    TiffBitmapDecoder decoder;
    try
    {
        decoder = new TiffBitmapDecoder(stream,
            BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
    }
    catch
    {
        Console.WriteLine("TiffBitmapDecoder crashed");
        stream.Dispose();
        return null;
    }

    // access information about the image
    int imageFrames = decoder.Frames.Count;
    BitmapSource bitmapSource = decoder.Frames[frameNumber];
    int sourceImageDepth = bitmapSource.Format.BitsPerPixel;
    int bytesPerPixel = sourceImageDepth / 8;
    Size imageSize = new Size(bitmapSource.PixelWidth, bitmapSource.PixelHeight);
    int pixelCount = imageSize.Width * imageSize.Height;

    // fill a byte array with source data bytes from the file
    int imageByteCount = pixelCount * bytesPerPixel;
    byte[] bytesSource = new byte[imageByteCount];
    bitmapSource.CopyPixels(bytesSource, imageSize.Width * bytesPerPixel, 0);

    // we can now close the original file
    stream.Dispose();

    // now convert the byte array to an int array (with 1 int per pixel)
    int[] valuesSource = new int[pixelCount];
    for (int i = 0; i < valuesSource.Length; i++)
    {
        // this loop is great because it works on any number of bytes per pixel
        int bytePosition = i * bytesPerPixel;
        for (int byteNumber = 0; byteNumber < bytesPerPixel; byteNumber++)
        {
            valuesSource[i] += bytesSource[bytePosition + byteNumber] << (byteNumber * 8);
        }
    }

    // determine the range of intensity data
    int pixelValueMax = valuesSource.Max();
    int pixelValueMin = valuesSource.Min();

    // predict what bit depth we have based upon pixelValueMax
    int dataDepth = 1;
    while (Math.Pow(2, dataDepth) < pixelValueMax)
        dataDepth++;

    // determine if we will use the original bit depth or our guessed bit depth
    bool use_detected_camera_depth = true; // should this be an argument?
    if (!use_detected_camera_depth)
        dataDepth = sourceImageDepth;

    // create and fill a pixel array for the 8-bit final image
    byte[] pixelsOutput = new byte[pixelCount];
    for (int i = 0; i < pixelsOutput.Length; i++)
    {
        // start by loading the pixel value of the source
        int pixelValue = valuesSource[i];

        // upshift it to the nearest byte (if using a nonstandard depth)
        pixelValue = pixelValue << (sourceImageDepth - dataDepth);

        // downshift it as needed to ensure the MSB is in the lowest 8 bytes
        pixelValue = pixelValue >> (sourceImageDepth - 8);

        // conversion to 8-bit should be now nondestructive
        pixelsOutput[i] = (byte)(pixelValue);
    }

    // input bytes are padded such that stide is a multiple of 4 bytes, so trim it off
    int strideByteMultiple = 4;
    int strideOverhang = imageSize.Width % strideByteMultiple;
    Log($"Width-stride overhang: {strideOverhang} bytes");
    if (strideOverhang > 0)
    {
        int strideBytesNeededPerRow = strideByteMultiple - (strideOverhang);
        Log($"Trimming {strideBytesNeededPerRow} extra bytes from the end of each row");
        byte[] pixelsOutputOriginal = new byte[pixelCount];
        Array.Copy(pixelsOutput, pixelsOutputOriginal, pixelCount);
        pixelsOutput = new byte[pixelCount + strideBytesNeededPerRow * imageSize.Height];
        int newStrideWidth = imageSize.Width + strideBytesNeededPerRow;
        for (int row = 0; row < imageSize.Height; row++)
            for (int col = 0; col < imageSize.Width; col++)
                pixelsOutput[row * newStrideWidth + col] = pixelsOutputOriginal[row * imageSize.Width + col];
    }
            
    // create the output bitmap (8-bit indexed color)
    var format = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
    Bitmap bmp = new Bitmap(imageSize.Width, imageSize.Height, format);

    // Create a grayscale palette, although other colors and LUTs could go here
    ColorPalette pal = bmp.Palette;
    for (int i = 0; i < 256; i++)
        pal.Entries[i] = System.Drawing.Color.FromArgb(255, i, i, i);
    bmp.Palette = pal;

    // copy the new pixel data into the data of our output bitmap
    var rect = new Rectangle(0, 0, imageSize.Width, imageSize.Height);
    BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadOnly, format);
    Marshal.Copy(pixelsOutput, 0, bmpData.Scan0, pixelsOutput.Length);
    bmp.UnlockBits(bmpData);

    return bmp;
}
```
