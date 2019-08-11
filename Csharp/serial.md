# Serial Communications

The .NET library seems to be much faster and lighter than the FTDI library for basic stuff. For FTDI usage see [FTDI.md](FTDI.md)

### Summary

```cs
using System.IO.Ports;
```

```cs
ser = new SerialPort("COM3", 115200);
ser.Open();
Console.WriteLine(ser.ReadLine());
```

```cs
string[] serialPortNames = SerialPort.GetPortNames();
```
