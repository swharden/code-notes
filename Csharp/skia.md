# SkiaSharp Notes

### Save as a JPEG
```cs
using (System.IO.Stream fileStream = System.IO.File.OpenWrite(filePath))
{
    SKImage snap = surface.Snapshot();
    SKData encoded = snap.Encode(SKEncodedImageFormat.Jpeg, quality);
    encoded.SaveTo(fileStream);
}
```
