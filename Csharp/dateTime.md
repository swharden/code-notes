# Date and Time in C#

https://docs.microsoft.com/en-us/dotnet/standard/base-types/standard-date-and-time-format-strings

### ISO 8601 Format

```cs
string s1 = DateTime.Now.ToString("o", CultureInfo.InvariantCulture);
```

### Epoch Seconds (Linux Time)

```cs
double linuxTime = (DateTime.UtcNow - new DateTime(1970, 1, 1)).TotalSeconds;
```

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
string message = $"{elapsedSec * 1000:0.00} ms ({1 / elapsedSec:0.00} Hz)";
```
