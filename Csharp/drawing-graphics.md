# Drawing Graphics

## Draw Graphics in a Picturebox
```cs
public Bitmap TestBitmap(Size size)
{
    Bitmap bmp = new Bitmap(size.Width, size.Height);

    Graphics gfx = Graphics.FromImage(bmp);
    gfx.Clear(Color.White);      

    Font font = new Font(FontFamily.GenericSansSerif, 12, FontStyle.Regular);
    SolidBrush brush = new SolidBrush(Color.Black);
    gfx.DrawString($"test", font, brush, new Point(2, 2));

    return bmp;
}

private void button1_Click(object sender, EventArgs e)
{
    pictureBox1.Image = TestBitmap(pictureBox1.Size);
}
```

## Draw Graphics on a Panel
```cs
private void button1_Click(object sender, EventArgs e)
{
    panel1.Invalidate(); // forces repaint
}

private void panel1_Paint(object sender, PaintEventArgs e)
{
    Graphics gfx = e.Graphics;
    SolidBrush brush = new SolidBrush(Color.Black);
    Pen pen = new Pen(brush);

    Rectangle rect = panel1.DisplayRectangle;

    Point[] points = new Point[4];
    points[0] = new Point(5, 5);
    points[1] = new Point(5, rect.Height-5);
    points[2] = new Point(rect.Width-5, rect.Height-5);
    points[3] = new Point(rect.Width-5, 5);
    gfx.DrawPolygon(pen, points);

    Font font = new Font(FontFamily.GenericMonospace, 8, FontStyle.Regular);
    Random rnd = new Random();
    double rand = rnd.NextDouble();
    gfx.DrawString($"proof of concept\n{rand}", font, brush, new Point(7, 7));
}
```

## Preventing Sharp Elbows
When DrawLines() has elbows they are triangular and sharp. This smooths them.
```C#
Pen pen = new Pen(lineBrush, lineWidth);
pen.StartCap = System.Drawing.Drawing2D.LineCap.Round;
pen.EndCap = System.Drawing.Drawing2D.LineCap.Round;
pen.LineJoin = System.Drawing.Drawing2D.LineJoin.Round;
```

## Hex-to-Color
```C#
private Color HexToColor(string hex)
{
    int r=0, g=0, b=0, a=255;
    hex = hex.Trim('#');
    if (hex.Length == 6 || hex.Length == 8)
    {
        r = Convert.ToInt32(hex.Substring(0, 2), 16);
        g = Convert.ToInt32(hex.Substring(2, 2), 16);
        b = Convert.ToInt32(hex.Substring(4, 2), 16);
    }
    if (hex.Length == 8)
    {
        a = Convert.ToInt32(hex.Substring(6, 2), 16);
    }
    return Color.FromArgb(a, r, g, b);
}

private Brush HexToBrush(string hex)
{
    return new SolidBrush(HexToColor(hex));
}
```

## Drawing Anti-Aliased Graphics
```C#
// lines
gfx.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
gfx.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.HighSpeed;

//text
gfx.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;
gfx.TextRenderingHint = System.Drawing.Text.TextRenderingHint.SingleBitPerPixel;
```

## Drawing Text with Shadows
Applied onto PictureBox1
```C#
Bitmap bmp = new Bitmap(pictureBox1.Width, pictureBox1.Height);
Graphics gfx = Graphics.FromImage(bmp);

gfx.Clear(this.BackColor);
gfx.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
gfx.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

Font fnt = new Font("Segoe UI", 36, FontStyle.Bold);
string str = "Shadow";

gfx.DrawString(str, fnt, Brushes.Gray, 3, 3);
gfx.DrawString(str, fnt, Brushes.Black, 0, 0);

pictureBox1.Image = bmp;
```

## Drawing Rotated Text
Oddly `Graphics.DrawString()` cannot draw text at an angle, so the solution is to rotate the entire canvas by the opposite angle, draw the string in the new location, then rotate the canvas back.

```C#
gfx.TranslateTransform(gfx.VisibleClipBounds.Size.Width, 0);
gfx.RotateTransform(-90);
gfx.DrawString(yLabel, fontAxis, brush, new Point(-posCy, -bmp.Width+2), sfCenter);
gfx.ResetTransform();
```

## Drawing Speed Comparisons
The next sections compare `SetPixel` against direct byte manipulation using lock/unlock.

### Example using `Bitmap.SetPixel` (~100ms)
```c
Bitmap buffer = new Bitmap(width, height);
Color NewPixel = Color.FromArgb(255, 123, 213, 059);
buffer.SetPixel(x, y, NewPixel); // modify the pixel (RGBA) with a Color
pictureBox1.Image = buffer;
```

### Example using `Bitmap.Lockbits` (~5ms)
This example containes extra code to show how to _read_ and also _write_ to a buffered bitmap by modifying a byte array.
```c
Bitmap buffer = new Bitmap(width, height);
BitmapData bitmapData = buffer.LockBits(new Rectangle(0, 0, buffer.Width, buffer.Height), 
                                        ImageLockMode.ReadWrite, buffer.PixelFormat);
int bytesPerPixel = Bitmap.GetPixelFormatSize(buffer.PixelFormat) / 8;
int byteCount = bitmapData.Stride * buffer.Height;
byte[] pixels = new byte[byteCount];
IntPtr ptrFirstPixel = bitmapData.Scan0;
Marshal.Copy(ptrFirstPixel, pixels, 0, pixels.Length);
pixels[someBytePosition] = 123; // set a single R, G, B, or A value as a byte
Marshal.Copy(pixels, 0, ptrFirstPixel, pixels.Length);
buffer.UnlockBits(bitmapData);
pictureBox1.Image = buffer;
```

### Example turning raw values into a bitmap (simple/fast)
This example shows how to make an 8-bit bitmap color-mapped to an indexed color pallette. By looking at this example you can figure out how to change the color pallette...

```c
// create a bitmap we will work with
Bitmap bitmap = new Bitmap(pictureBox1.Width, pictureBox1.Height, PixelFormat.Format8bppIndexed);

// modify the indexed palette to make it grayscale
ColorPalette pal = bitmap.Palette;
for (int i = 0; i < 256; i++)
    pal.Entries[i] = Color.FromArgb(255, i, i, i);
bitmap.Palette = pal;

// prepare to access data via the bitmapdata object
BitmapData bitmapData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), 
                                        ImageLockMode.ReadOnly, bitmap.PixelFormat);

// create a byte array to reflect each pixel in the image
byte[] pixels = new byte[bitmapData.Stride * bitmap.Height];

// fill pixels with random data
for (int i=0; i < pixels.Length; i++)
    pixels[i] = (byte) rand.Next(255);

// turn the byte array back into a bitmap
Marshal.Copy(pixels, 0, bitmapData.Scan0, pixels.Length);
bitmap.UnlockBits(bitmapData);            

// apply the bitmap to the picturebox
pictureBox1.Image = bitmap;
```

### Applying a 2d list to a roll-able bitmap
This example has been added to the project, but important code is here:

##### Creating data
```c
private static List<List<double>> data; // a list of column pixel values

private List<double> Generate_list_random(int itemCount) {
    List<double> list = new List<double>(itemCount);
    for (int i=0; i< itemCount; i++)
    {
        list.Add(rand.NextDouble());
    }
    return list;
}

private void Data_init()
{
    int data_samples = pictureBox1.Width;
    int data_size = pictureBox1.Height;

    data = new List<List<double>>();
    for (int i=0; i<data_samples; i++)
    {
        data.Add(Generate_list_random(data_size));
    }

    System.Console.WriteLine("generated random data");

}

```

##### Rolling the data
```c
private void Bitmap_roll()
{
    data.Insert(data.Count, data[0]);
    data.RemoveAt(0);
}
```

##### Applying the 2d list data to bitmap
```c
private void Bitmap_from_data()
{
    // create a bitmap we will work with
    Bitmap bitmap = new Bitmap(data.Count, data[0].Count, PixelFormat.Format8bppIndexed);

    // modify the indexed palette to make it grayscale
    ColorPalette pal = bitmap.Palette;
    for (int i = 0; i < 256; i++)
        pal.Entries[i] = Color.FromArgb(255, i, i, i);
    bitmap.Palette = pal;

    // prepare to access data via the bitmapdata object
    BitmapData bitmapData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height),
                                            ImageLockMode.ReadOnly, bitmap.PixelFormat);

    // create a byte array to reflect each pixel in the image
    byte[] pixels = new byte[bitmapData.Stride * bitmap.Height];

    // fill pixel array with data
    for (int col=0; col<data.Count; col++)
    {
        for (int row=0; row<data[col].Count; row++)
        {
            int bytePosition = row * bitmapData.Stride + col;
            pixels[bytePosition] = (byte)(255 * data[col][row]);
        }
    }

    // turn the byte array back into a bitmap
    Marshal.Copy(pixels, 0, bitmapData.Scan0, pixels.Length);
    bitmap.UnlockBits(bitmapData);

    // apply the bitmap to the picturebox
    pictureBox1.Image = bitmap;

}
```

## Random Color
```C#
public Color randomColor{get{return Color.FromArgb(255, gen.rand.Next(256), gen.rand.Next(256), gen.rand.Next(256));}}
```

## Quick and Dirty Histogram Bitmap
```cs
public Bitmap Histogram(Size size, double[] values)
{
    Bitmap bmp = new Bitmap(size.Width, size.Height);

    Graphics gfx = Graphics.FromImage(bmp);
    gfx.Clear(Color.White);

    // bin the data into 1px columns
    double dataMin = values.Min();
    double dataMax = values.Max();
    double dataSpan = dataMax - dataMin;
    int nBins = size.Width;
    double[] counts = new double[nBins];
    double binSize = dataSpan / (nBins - 1);
    for (int i = 0; i < values.Length; i++)
    {
        int bin = (int)((values[i] - dataMin) / binSize);
        if (bin >= counts.Length)
            bin = counts.Length - 1;
        if (bin < 0)
            bin = 0;
        counts[bin] = counts[bin] + 1;
    }

    // determine what to normalize it to visually
    double peakVal = counts.Max();
    double heightMult = size.Height / peakVal;

    // plot the binned data
    Pen pen = new Pen(new SolidBrush(Color.Black));
    for (int i = 0; i < nBins; i++)
    {
        int heightPx = (int)(counts[i] * heightMult);
        Point pt1 = new Point(i, size.Height - 0);
        Point pt2 = new Point(i, size.Height - heightPx);
        gfx.DrawLine(pen, pt1, pt2);
    }

    return bmp;
}
```

## Rotate a Bitmap
```cs
public static Bitmap Rotate(Bitmap bmpIn, float angle = 90)
{
    // TODO: this could be faster with byte manipulation since it's 90 degrees

    if (bmpIn == null)
        return null;

    Bitmap bmp = new Bitmap(bmpIn);
    Bitmap bmpRotated = new Bitmap(bmp.Height, bmp.Width);

    Graphics gfx = Graphics.FromImage(bmpRotated);
    gfx.RotateTransform(angle);
    gfx.DrawImage(bmp, new Point(0, -bmp.Height));

    return bmpRotated;
}
```

## Measure a String without a Graphics
```cs
Graphics gfx = Graphics.FromHwnd(IntPtr.Zero);
FontFamily fmly = new FontFamily("impact");
FontStyle style = (bold) ? FontStyle.Bold : FontStyle.Regular;
Font fnt = new Font(fmly, fontSize, style);
SizeF textSize = gfx.MeasureString(text, fnt);
```
