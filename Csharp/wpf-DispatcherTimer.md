# WPF DispatcherTimer

```cs
DispatcherTimer updateDataTimer = new DispatcherTimer();
updateDataTimer.Interval = TimeSpan.FromMilliseconds(1);
updateDataTimer.Tick += UpdateData;
updateDataTimer.Start();
```

```cs
void UpdateData(object sender, EventArgs e)
{
  // do stuff
}
```
