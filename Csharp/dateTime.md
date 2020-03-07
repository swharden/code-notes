# Date and Time in C#

https://docs.microsoft.com/en-us/dotnet/standard/base-types/standard-date-and-time-format-strings

```cs
string msg = $"generated on {DateTime.Now.ToString("D")} at {DateTime.Now.ToString("t")}";
```

```cs
double sec = Console.WriteLine(DateTime.Now.Second);
```

```cs
double epoch = double epochSeconds = (double)DateTime.Now.Ticks / TimeSpan.TicksPerSecond;
```
