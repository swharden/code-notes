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

### Handling Incoming Data
```cs
ser = new SerialPort(com, baud);
ser.Open();
ser.ReadLine();
ser.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
```

```cs
static List<string> lines = new List<string>();
        
private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
{
    try
    {
        SerialPort sp = (SerialPort)sender;
        string line = (sp.ReadExisting() + sp.ReadLine()).Trim();
        lines.Add(line);
    }
    catch (System.IO.IOException exc)
    {
        Console.WriteLine("IOException in serial data handler");
        Console.WriteLine(exc);
    }
}
```
