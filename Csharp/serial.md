# Serial Communications

```cs
using System.IO.Ports;
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
