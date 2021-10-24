I use this code to work with 2D pixel data and images with non-standard (>8-bit) data.

```cs
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Media.Imaging;

namespace ImagingTests
{
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
            this.width = width;
            this.height = height;
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

        public void AutoContrast(double maxVal = 255)
        {
            double valMin = data.Min();
            double valMax = data.Max();
            double valRange = valMax - valMin;
            Console.WriteLine($"Contrasting from {valMin} to {valMax}");
            for (int i = 0; i < data.Length; i++)
                data[i] = (data[i] - valMin) / valRange * maxVal;
        }

        public void ClipMinMax(double min, double max)
        {
            Console.WriteLine($"Clipping from {min} to {max}");
            for (int i = 0; i < data.Length; i++)
            {
                if (data[i] < min)
                    data[i] = min;
                else if (data[i] > max)
                    data[i] = max;
                else if (double.IsNaN(data[i]))
                    data[i] = min;
            }
        }

        public void AutoBrightness(double maxVal = 255)
        {
            double valMax = data.Max();
            for (int i = 0; i < data.Length; i++)
                data[i] = data[i] / valMax * maxVal;
        }

        public void SubtractBackgroundPercentile(double percentile = 10.0)
        {
            double[] valuesInOrder = new double[data.Length];
            Array.Copy(data, valuesInOrder, data.Length);
            Array.Sort(valuesInOrder);
            int cutoffIndex = (int)(percentile / 100.0 * data.Length);
            double baselineValue = valuesInOrder[cutoffIndex];
            Console.WriteLine($"Subtracting lowest {percentile} percentile (value: {baselineValue})");
            for (int i = 0; i < data.Length; i++)
                data[i] = data[i] - baselineValue;
        }

        public Bitmap GetBitmap()
        {
            // create and fill a pixel array for the 8-bit final image
            byte[] pixelsOutput = new byte[pixelCount];
            for (int i = 0; i < pixelCount; i++)
            {
                if (data[i] < 0)
                    pixelsOutput[i] = 0;
                else if (data[i] > 255)
                    pixelsOutput[i] = 255;
                else
                    pixelsOutput[i] = (byte)data[i];

            }

            // trim-off extra bytes if width is not a multiple of 4 bytes
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
            var formatOutput = System.Drawing.Imaging.PixelFormat.Format8bppIndexed;
            Bitmap bmp = new Bitmap(width, height, formatOutput);

            // Create a grayscale palette, although other colors and LUTs could go here
            System.Drawing.Imaging.ColorPalette pal = bmp.Palette;
            for (int i = 0; i < 256; i++)
                pal.Entries[i] = System.Drawing.Color.FromArgb(255, i, i, i);
            bmp.Palette = pal;

            // copy the new pixel data into the data of our output bitmap
            var rect = new Rectangle(0, 0, width, height);
            System.Drawing.Imaging.BitmapData bmpData = bmp.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadOnly, formatOutput);
            System.Runtime.InteropServices.Marshal.Copy(pixelsOutput, 0, bmpData.Scan0, pixelsOutput.Length);
            bmp.UnlockBits(bmpData);

            return bmp;
        }
    }
}
```