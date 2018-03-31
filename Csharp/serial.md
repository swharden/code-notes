# Serial Communications

```cs
using System.IO.Ports;
```

* http://codesamplez.com/programming/serial-port-communication-c-sharp

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
