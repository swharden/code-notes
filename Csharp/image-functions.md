# Image Functions
Standalone copy/pastable functions I find useful

## Load TIF pixels as an int array (bit-depth-agnostic)
```cs
private int[] LoadImageTiff(string path)
{

    // open a file stream and keep it open until we're done reading the file
    System.IO.Stream stream = new System.IO.FileStream(path, System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.Read);

    TiffBitmapDecoder decoder = new TiffBitmapDecoder(stream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);

    // access information about the image
    int imageFrames = decoder.Frames.Count;
    BitmapSource bitmapSource = decoder.Frames[0];
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

    // TODO: input bytes are padded such that stride is a multiple of 4 bytes, so trim that off

    return valuesSource;
}
```
