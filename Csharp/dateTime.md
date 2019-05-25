# Date and Time in C#
```cs
Console.WriteLine(DateTime.Now.Second);
```

```cs
double epochSeconds = (double)DateTime.Now.Ticks / TimeSpan.TicksPerSecond;
```
