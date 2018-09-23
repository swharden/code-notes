# Image Files

## Open Any Image (fails at nonstandard bit depths)
```cs
Bitmap bmp = new Bitmap(filePath); // that's it!
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
