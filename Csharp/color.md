# Color

## C# Color from Hex String
```cs
parentNode.BackColor = System.Drawing.ColorTranslator.FromHtml("#003366");
```

## Converting HEX to RGBA (for CSS)
```cs
public static string ColorHexToRgba(string hex, double alpha = 1.0)
{
    // ColorHexToRgba("#FFFFFF", .5) returns "rgba(255, 255, 255, .5)"
    hex = hex.Replace("#", "");
    if (hex.Length == 3)
        hex = hex + hex;
    if (hex.Length != 6)
        throw new Exception("hex color code must be 6 characters");
    int rgb = Convert.ToInt32(hex, 16);
    byte r = (byte)(rgb >> 16);
    byte g = (byte)(rgb >> 8);
    byte b = (byte)(rgb >> 0);
    return $"rgba({r}, {g}, {b}, {alpha})";
}
```
