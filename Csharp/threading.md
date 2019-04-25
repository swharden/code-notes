# Threading in C#

```cs
System.Threading.Thread t = new System.Threading.Thread(FunctionName);
t.Start();
while (t.IsAlive)
    Application.DoEvents();
```
