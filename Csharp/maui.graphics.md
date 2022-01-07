# Microsoft.Maui.Graphics
https://maui.graphics/

## Draw and Save as JPG

```cs
using SkiaBitmapExportContext context = new(400, 300, 1.0f);

ICanvas canvas = context.Canvas;
canvas.FillColor = Colors.Red;
canvas.FillRectangle(10, 20, 30, 40);

using FileStream fs = new("test123.jpg", FileMode.Create);
context.WriteToStream(fs);
```

## Windows Forms Animation

```cs
// Call this with a Timer to draw on a PictureBox
// This method works, but but gets slow when images are large (~10 Hz)
// I think it can get faster using an OpenGL Skia control

float width = pictureBox1.Width;
float height = pictureBox1.Height;
using SkiaBitmapExportContext context = new((int)width, (int)height, 1.0f);

ICanvas canvas = context.Canvas;

float fraction = DateTime.Now.Millisecond / 1000.0f;
canvas.FillColor = Colors.Red;
canvas.FillRectangle(0, 0, width * fraction, height);

using MemoryStream ms = new();
context.WriteToStream(ms); // this is the slow step
Image img = Bitmap.FromStream(ms);

Image original = pictureBox1.Image;
pictureBox1.Image = img;
original?.Dispose();
```

![image](https://user-images.githubusercontent.com/4165489/148491357-c50580da-74d6-46c5-9705-4ea411780b69.png)
