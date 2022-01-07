# Microsoft.Maui.Graphics
https://maui.graphics/

## Windows Forms Animation (Skia + OpenGL)

* Drag/Drop a SKGLControl onto your Form
* Have a timer routinely invalidate the control

```cs
private void skglControl1_PaintSurface(object sender, SkiaSharp.Views.Desktop.SKPaintGLSurfaceEventArgs e)
{
    ICanvas canvas = new SkiaCanvas() { Canvas = e.Surface.Canvas };
    float fraction = DateTime.Now.Millisecond / 1000.0f;
    canvas.FillColor = Colors.White;
    canvas.FillRectangle(0, 0, Width, Height);
    canvas.FillColor = Colors.Red;
    canvas.FillRectangle(0, 0, Width * fraction, Height);
}
```

## Draw and Save as JPG

```cs
using SkiaBitmapExportContext context = new(400, 300, 1.0f);

ICanvas canvas = context.Canvas;
canvas.FillColor = Colors.Red;
canvas.FillRectangle(10, 20, 30, 40);

using FileStream fs = new("test123.jpg", FileMode.Create);
context.WriteToStream(fs);
```

## Windows Forms Animation (Skia + Bitmap Buffer)

* Drag/Drop a PictureBox onto your Form
* Have a timer routinely call this method

```cs
float width = pictureBox1.Width;
float height = pictureBox1.Height;
using SkiaBitmapExportContext context = new((int)width, (int)height, 1.0f);

ICanvas canvas = context.Canvas;

float fraction = DateTime.Now.Millisecond / 1000.0f;
canvas.FillColor = Colors.Red;
canvas.FillRectangle(0, 0, width * fraction, height);

using MemoryStream ms = new();
context.WriteToStream(ms); // this gets really slow when the image is large
Image img = Bitmap.FromStream(ms);

Image original = pictureBox1.Image;
pictureBox1.Image = img;
original?.Dispose();
```
