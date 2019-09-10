# Skia (SkiaSharp)

SkiaSharp is a cross-platform 2D graphics API for .NET platforms based on Google's Skia Graphics Library. I tried it out thinking it might be faster than drawing bitmap buffers for ScottPlot. It wasn't faster. Fullscreen drawing of 1000 lines is about 3 Hz, but it was easy to use and the graphics looked nice. Install `SkiaSharp.Views.Forms` with NuGet.

```cs
Random rand = new Random();
SKImageInfo imageInfo;
SKSurface surface;
SKCanvas canvas;
SKPaint paint;
        
public void PlotResize()
{
    imageInfo = new SKImageInfo(pictureBox1.Width, pictureBox1.Height);
    surface = SKSurface.Create(imageInfo);
    canvas = surface.Canvas;
    paint = new SKPaint();
}
```

```cs
public void PlotDemo()
{
    System.Diagnostics.Stopwatch stopwatch = System.Diagnostics.Stopwatch.StartNew();
    canvas.Clear();
    paint.Color = SKColors.Black;
    paint.StrokeWidth = 1;
    paint.IsAntialias = true;
    paint.Style = SKPaintStyle.Stroke;
    for (int i = 0; i < 1000; i++)
    {
        int x1 = (int)(rand.NextDouble() * pictureBox1.Width);
        int x2 = (int)(rand.NextDouble() * pictureBox1.Width);
        int y1 = (int)(rand.NextDouble() * pictureBox1.Height);
        int y2 = (int)(rand.NextDouble() * pictureBox1.Height);
        canvas.DrawLine(x1, y1, x2, y2, paint);
    }

    // apply the canvas to a picturebox as a Bitmap
    using (SKImage image = surface.Snapshot())
    using (SKData data = image.Encode())
    using (System.IO.MemoryStream mStream = new System.IO.MemoryStream(data.ToArray()))
    {
        Bitmap bm = new Bitmap(mStream, false);
        pictureBox1.Image = bm;
    }

    double elapsedMsec = stopwatch.ElapsedTicks * 1000.0 / System.Diagnostics.Stopwatch.Frequency;
    double freqHz = 1000.0 / elapsedMsec;
    this.Text = string.Format("SkiaSharp Test - {0:0.00} ms / frame ({1:0.00 Hz})", elapsedMsec, freqHz);

}
```
