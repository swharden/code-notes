# Image Files

## Open Any Image (fails at nonstandard bit depths)
```cs
Bitmap bmp = new Bitmap(filePath); // that's it!
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
