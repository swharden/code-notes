# Timers

```cs
using System.Timers;
```

```cs
public Timer timer;
```

```cs
timer = new Timer(10);
timer.Elapsed += new ElapsedEventHandler(TimerTick);
timer.Start();
```

```cs
private void TimerTick(object source, ElapsedEventArgs e)
{
  // stuff
}
```
