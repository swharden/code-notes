# Date and Time in C#

https://docs.microsoft.com/en-us/dotnet/standard/base-types/standard-date-and-time-format-strings

### ISO 8601 Format

```cs
string s1 = DateTime.Now.ToString("o", CultureInfo.InvariantCulture);
```

### Epoch Seconds (Linux Time)

```cs
long epochTicks = new DateTime(1970, 1, 1).Ticks;
long unixTime = ((DateTime.UtcNow.Ticks - epochTicks) / TimeSpan.TicksPerSecond);
```
