# TIF Class
This is a work in progress. It is designed to handle tifs which contain odd bit depths (e.g., 12-bit data in a 16-bit TIF) which look dark when loaded with other libraries.

## Usage
```cs
ImageData im = new ImageData(imagePath16bit);
im.AutoContrast();
pictureBox1.BackgroundImage = im.GetBitmap();
```

## Code
```cs
public class ImageData
{
    public double[] data;
    public int width;
    public int height;
    public int pixelCount { get { return width * height; } }

    public ImageData(string filePath)
    {
        LoadDataFromFile(filePath);
    }

    public ImageData(double[] data, int width, int height)
    {
        this.data = data;
    }

    private void LoadDataFromFile(string filePath, int frameNumber = 0)
    {

        // open a file stream and keep it open until we're done reading the file
        System.IO.Stream stream = new System.IO.FileStream(filePath, System.IO.FileMode.Open,
            System.IO.FileAccess.Read, System.IO.FileShare.Read);

        // carefully open the file to see if it will decode
        TiffBitmapDecoder decoder;
        try
        {
            decoder = new TiffBitmapDecoder(stream, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
        }
        catch
        {
            Console.WriteLine("TiffBitmapDecoder crashed");
            stream.Dispose();
            data = null;
            return;
        }

        // access information about the image
        int imageFrames = decoder.Frames.Count;
        BitmapSource bitmapSource = decoder.Frames[frameNumber];
        int sourceImageDepth = bitmapSource.Format.BitsPerPixel;
        int bytesPerPixel = sourceImageDepth / 8;
        Size imageSize = new Size(bitmapSource.PixelWidth, bitmapSource.PixelHeight);
        width = imageSize.Width;
        height = imageSize.Height;

        // fill a byte array with source data bytes from the file
        int imageByteCount = pixelCount * bytesPerPixel;
        byte[] bytesSource = new byte[imageByteCount];
        bitmapSource.CopyPixels(bytesSource, imageSize.Width * bytesPerPixel, 0);

        // close the original file
        stream.Dispose();

        // convert the byte array to an array of values (works on any bit depth)
        data = new double[pixelCount];
        for (int i = 0; i < data.Length; i++)
            for (int byteNumber = 0; byteNumber < bytesPerPixel; byteNumber++)
                data[i] += bytesSource[i * bytesPerPixel + byteNumber] << (byteNumber * 8);
    }

    public void AutoContrast(int maxVal = 255)
    {
        double valMin = data.Min();
        double valMax = data.Max();
        double valRange = valMax - valMin;
        for (int i = 0; i < data.Length; i++)
            data[i] = (data[i] - valMin) / valRange * maxVal;
    }

    public Bitmap GetBitmap()
    {
        // create and fill a pixel array for the 8-bit final image
        byte[] pixelsOutput = new byte[pixelCount];
        for (int i = 0; i < pixelCount; i++)
            pixelsOutput[i] = (byte)data[i];

        // input bytes are padded such that stide is a multiple of 4 bytes, so trim it off
        int strideByteMultiple = 4;
        int strideOverhang = width % strideByteMultiple;
        if (strideOverhang > 0)
        {
            int strideBytesNeededPerRow = strideByteMultiple - (strideOverhang);
            byte[] pixelsOutputOriginal = new byte[pixelCount];
            Array.Copy(pixelsOutput, pixelsOutputOriginal, pixelCount);
            pixelsOutput = new byte[pixelCount + strideBytesNeededPerRow * height];
            int newStrideWidth = width + strideBytesNeededPerRow;
            for (int row = 0; row < height; row++)
                for (int col = 0; col < width; col++)
                    pixelsOutput[row * newStrideWidth + col] = pixelsOutputOriginal[row * width + col];
        }

        // create the output bitmap (8-bit indexed color)
        var format = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
        Bitmap bmp = new Bitmap(width, height, format);

        // Create a grayscale palette, although other colors and LUTs could go here
        System.Drawing.Imaging.ColorPalette pal = bmp.Palette;
        for (int i = 0; i < 256; i++)
            pal.Entries[i] = System.Drawing.Color.FromArgb(255, i, i, i);
        bmp.Palette = pal;

        // copy the new pixel data into the data of our output bitmap
        var rect = new Rectangle(0, 0, width, height);
        System.Drawing.Imaging.BitmapData bmpData = bmp.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadOnly, format);
        Marshal.Copy(pixelsOutput, 0, bmpData.Scan0, pixelsOutput.Length);
        bmp.UnlockBits(bmpData);

        return bmp;
    }
```
