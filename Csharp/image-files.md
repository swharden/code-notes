# Image Files

## Open Any Image
```cs
Bitmap bmp = new Bitmap(filePath);
```

## Open Any Image without locking it on the filesystem
```cs
private Bitmap LoadBitmapWithoutLockingFile(string filePath)
{
    byte[] bytes = File.ReadAllBytes(filePath);
    using MemoryStream memoryStream = new(bytes);
    return new Bitmap(memoryStream);
}
```

## Convert Bitmap To/From Byte Arrays
```cs

/// <summary>
/// return a bitmap (of any image format) as a byte array of its data values
/// </summary>
public byte[] BitmapToBytes(Bitmap bmp)
{
    int bytesPerPixel = Image.GetPixelFormatSize(bmp.PixelFormat) / 8;
    //byte[] bytes = new byte[bmp.Width * bmp.Height * bytesPerPixel];
    Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
    BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadOnly, bmp.PixelFormat);
    byte[] bytes = new byte[bmpData.Stride * bmp.Height * bytesPerPixel];
    Marshal.Copy(bmpData.Scan0, bytes, 0, bytes.Length);
    bmp.UnlockBits(bmpData);
    return bytes;
}
```

```cs
/// <summary>
/// create a bitmap given a byte array of raw data
/// </summary>
public Bitmap BitmapFromBytes(byte[] bytes, Size size, PixelFormat format = PixelFormat.Format8bppIndexed)
{
    Bitmap bmp = new Bitmap(size.Width, size.Height, format);
    Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
    BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite, bmp.PixelFormat);
    Marshal.Copy(bytes, 0, bmpData.Scan0, bytes.Length);
    bmp.UnlockBits(bmpData);
    return bmp;
}
```

## Get 1 channel of an RGB Image
```cs
public Bitmap ExtractChannelToGrayscale(Bitmap bmpSource, int channel = 0, bool grayscale = false)
{
    // copy our source image to a byte array (8-bits/pixel, 3 channel RGB)
    byte[] bytesRGB = BitmapToBytes(bmpSource);
    int nPixels = bytesRGB.Length / 3;

    // create a byte array for out grayscale image (16-bits/pixel, 1 channel)
    byte[] bytesGray = new byte[nPixels];

    for (int pixel = 0; pixel < nPixels; pixel++)
    {
        bytesGray[pixel] = bytesRGB[3 * pixel + (2 - channel)];
    }

    // make a 16-bit grayscale image the same size as the source
    Bitmap bmpGray = BitmapFromBytes(bytesGray, bmpSource.Width, bmpSource.Height);

    if (grayscale)
        BitmapApplyPalette(bmpGray, "gray");
    else if (channel == 0)
        BitmapApplyPalette(bmpGray, "red");
    else if (channel == 1)
        BitmapApplyPalette(bmpGray, "green");
    else if (channel == 2)
        BitmapApplyPalette(bmpGray, "blue");

    return bmpGray;
}
```

## Apply Color Palettes (LUTs) to 8-Bit Indexed Bitmaps
```cs
/// <summary>
/// Apply red, green, blue, magenta, or gray LUT to an 8-bit indexed bitmap
/// </summary>
public void BitmapApplyPalette(Bitmap bmp, string color = "gray")
{
    ColorPalette pal = bmp.Palette;
    for (int i = 0; i < 256; i++)
    {
        if (color == "red")
            pal.Entries[i] = System.Drawing.Color.FromArgb(255, i, 0, 0);
        else if (color == "green")
            pal.Entries[i] = System.Drawing.Color.FromArgb(255, 0, i, 0);
        else if (color == "blue")
            pal.Entries[i] = System.Drawing.Color.FromArgb(255, 0, 0, i);
        else if (color == "magenta")
            pal.Entries[i] = System.Drawing.Color.FromArgb(255, i, 0, i);
        else if (color == "gray")
            pal.Entries[i] = System.Drawing.Color.FromArgb(255, i, i, i);
        else
            Console.WriteLine($"Unknown color pallette code: {color}");
    }
    bmp.Palette = pal;
}
```

## Use Marshal Copy to remove 1 channel of an RGBA image
```cs
public Bitmap ExtractChannel(Bitmap bmpSource, int channel = 0)
{
    Bitmap bmp = new Bitmap(bmpSource);

    int bytesPerPixel = Image.GetPixelFormatSize(bmp.PixelFormat) / 8;

    // copy the image into a byte array
    byte[] bytes = new byte[bmp.Width * bmp.Height * bytesPerPixel];
    Rectangle rect = new Rectangle(0, 0, bmp.Width, bmp.Height);
    BitmapData bmpData = bmp.LockBits(rect, ImageLockMode.ReadWrite, bmp.PixelFormat);
    Marshal.Copy(bmpData.Scan0, bytes, 0, bytes.Length);

    // modify the values as needed
    for (int i = 0; i < bytes.Length; i++)
    {
        int thisChannel = i % 4;
        if (thisChannel == 3)
            continue;
        if (thisChannel != (2 - channel))
            bytes[i] = 0;
    }

    // copy the byte array back into the image
    Marshal.Copy(bytes, 0, bmpData.Scan0, bytes.Length);
    bmp.UnlockBits(bmpData);

    return bmp;
}
```

## Monitoring graphical output of console applications
I often write console apps which generate graphics, but it's inconvenient to double-click them to view them every time they are overwritten. I found I can do this in a web browser! Auto-refreshing every 1 second saves the day.

```c#
Bitmap bmp = new Bitmap(800,600);
Graphics gfx = Graphics.FromImage(bmp);
gfx.Clear(Color.Red);
bmp.Save("test.bmp");
```

**Pro tip: Javascript reduces flickering:**
```html
<html>
<BODY onload="setTimeout('document.location.reload();', 1000);">
<img src="test.bmp">
</body>
</html>
```

**Java-free method:**
```html
<html>
<head>
<meta http-equiv="refresh" content="1" >
</head>
<body>
<img src="test.bmp">
</body>
</html>
```

## Saving Graphics Bitmaps as JPG or PNG
```
bmp.Save("test.bmp"); // defaults to bmp
bmp.Save("test.jpg", System.Drawing.Imaging.ImageFormat.Jpeg);
bmp.Save("test.png", System.Drawing.Imaging.ImageFormat.Png);
```
