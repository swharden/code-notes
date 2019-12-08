### Latest .NET Framework
https://www.microsoft.com/net/download/dotnet-framework-runtime

### Get Timestamp
```cs
public static string GetTimestamp()
{
    return DateTime.Now.ToString("HH':'mm':'ss.fff");
}
```

```cs
public static string GetDateTimestamp()
{
    return DateTime.Now.ToString("yyyy'-'MM'-'dd'T'HH':'mm':'ss.fff");
}
```

### Stopwatches Help Time Things
```cs
Stopwatch stopwatch = Stopwatch.StartNew();
/* do stuff */
double elapsedSec = (double)stopwatch.ElapsedTicks / Stopwatch.Frequency;
string message = string.Format("completed in {0:0.00} ms ({1:0.00} Hz)", elapsedSec * 1000.0, 1 / elapsedSec);
```

### Keyboard Shortcuts

* format document: `CTRL+K`, `CTRL+D`
* format selection: `CTRL+K`, `CTRL+F`
* comment: `CTRL+K`, `CTRL+C`
* uncomment: `CTRL+K`, `CTRL+U`
* full screen: `ALT+SHIFT+ENTER`

### Inline `if` statements
```cs
comboChannel.Enabled = (channelCount > 1) ? true : false;
```

### Inline null-check (null coalescing operator)
```cs
// manual way
if (lineStyle == null)
  this.lineStyle = new Styles.Line();
else
  this.lineStyle = lineStyle;

// inline if statement
this.lineStyle = (lineStyle == null) ? new Styles.Line() : lineStyle;

// null coalescing operator
this.lineStyle = lineStyle ?? new Styles.Line();
```

### String to integer

If you are sure it will parse:
```cs
int.Parse(string)
```

If you are not sure it will parse:
```cs
int i;
bool success = int.TryParse(string, out i);
```

### Generate a Random Color
```cs
Color randomColor = Color.FromArgb(255, rand.Next(256), rand.Next(256), rand.Next(256));
```
