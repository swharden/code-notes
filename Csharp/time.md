# Time Operations

## Get Formatted Time
```C#
DateTime.Now.ToString("MM/dd/yyyy") //05/29/2015
DateTime.Now.ToString("dddd, dd MMMM yyyy") //Friday, 29 May 2015
DateTime.Now.ToString("dddd, dd MMMM yyyy") //Friday, 29 May 2015 05:50
DateTime.Now.ToString("dddd, dd MMMM yyyy") //Friday, 29 May 2015 05:50 AM
DateTime.Now.ToString("dddd, dd MMMM yyyy") //Friday, 29 May 2015 5:50
DateTime.Now.ToString("dddd, dd MMMM yyyy") //Friday, 29 May 2015 5:50 AM
DateTime.Now.ToString("dddd, dd MMMM yyyy HH:mm:ss") //Friday, 29 May 2015 05:50:06
DateTime.Now.ToString("MM/dd/yyyy HH:mm") //05/29/2015 05:50
DateTime.Now.ToString("MM/dd/yyyy hh:mm tt") //05/29/2015 05:50 AM
DateTime.Now.ToString("MM/dd/yyyy H:mm") //05/29/2015 5:50
DateTime.Now.ToString("MM/dd/yyyy h:mm tt") //05/29/2015 5:50 AM
DateTime.Now.ToString("MM/dd/yyyy HH:mm:ss") //05/29/2015 05:50:06
DateTime.Now.ToString("MMMM dd") //May 29
DateTime.Now.ToString("yyyy’-‘MM’-‘dd’T’HH’:’mm’:’ss.fffffffK") //2015-05-16T05:50:06.7199222-04:00
DateTime.Now.ToString("ddd, dd MMM yyy HH’:’mm’:’ss ‘GMT’") //Fri, 16 May 2015 05:50:06 GMT
DateTime.Now.ToString("yyyy’-‘MM’-‘dd’T’HH’:’mm’:’ss") //2015-05-16T05:50:06
DateTime.Now.ToString("HH:mm") //05:50
DateTime.Now.ToString("hh:mm tt") //05:50 AM
DateTime.Now.ToString("H:mm") //5:50
DateTime.Now.ToString("h:mm tt") //5:50 AM
DateTime.Now.ToString("HH:mm:ss") //05:50:06
DateTime.Now.ToString("yyyy MMMM") //2015 May
```

## Get System Time (milliseconds)
```C#
double t = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
```

## Timing things with high resolution
```C#
System.Diagnostics.Stopwatch stopwatch = System.Diagnostics.Stopwatch.StartNew();

stopwatch.Reset();
stopwatch.Start();
// do something
stopwatch.Stop();

double timeMS = stopwatch.ElapsedTicks * 1000.0 / System.Diagnostics.Stopwatch.Frequency;

System.Console.WriteLine(string.Format("loaded in {1:0.00} ms", timeMS));
```

## Pause or Sleep
```cs
System.Threading.Thread.Sleep(5000); // sleep for 5 sec
```
