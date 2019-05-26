# Threading in C#

```cs
System.Threading.Thread t = new System.Threading.Thread(FunctionName);
t.Start();
while (t.IsAlive)
    Application.DoEvents();
```

```cs
readerThread = new System.Threading.Thread(new System.Threading.ParameterizedThreadStart(ReadForever));
readerThread.Start(adc1);

private void ReadForever(object adc1)
{
    double[] data = (double[])adc1;
}
```
