# Serial Communications

The .NET library seems to be much faster and lighter than the FTDI library for basic stuff.

```cs
using System.IO.Ports;
ser = new SerialPort("COM3", 115200);
ser.Open();
Console.WriteLine(ser.ReadLine());
```

## List COM Ports
```cs
void UpdateSerialPorts()
{
    cb_serialPorts.Items.Clear();
    string[] ports = SerialPort.GetPortNames();
    foreach (string port in ports)
    {
        cb_serialPorts.Items.Add(port);
    }
}
```
