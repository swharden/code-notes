# FTDI (USB/USART/etc) Programming

* [FT232R](http://www.ftdichip.com/Products/ICs/FT232R.htm) (USB<->USART)
* [FT232H](http://www.ftdichip.com/Products/ICs/FT232R.htm) (USB<->USART/SPI/I2C/etc)
* [FTDI API Programmer's Guide](
http://www.ftdichip.com/Support/Documents/ProgramGuides/D2XX_Programmer's_Guide(FT_000071).pdf)

## Installation (NuGet)
```cs
using FTD2XX_NET; // installed with NuGet
```

## Quickstart
```cs
FTDI ftdi = new FTDI();
FTDI.FT_STATUS ft_status = FTDI.FT_STATUS.FT_OK;
        
// this function looks up details about every FTDI device
void Scan_ftdi_devices()
{
    // start by resetting things (needed?)
    ftdi.ResetPort();

    // determine how many FTDI devices are there
    uint nDevices = 0;
    ft_status = ftdi.GetNumberOfDevices(ref nDevices);

    // get details for all devices
    FTDI.FT_DEVICE_INFO_NODE[] ftdiDeviceList = new FTDI.FT_DEVICE_INFO_NODE[nDevices];
    ft_status = ftdi.GetDeviceList(ftdiDeviceList);

    // show info for each device
    string msg = "";
    for (int i = 0; i < nDevices; i++)
    {
        msg += string.Format($"Device Number: {i}");
        msg += string.Format($"\nDescription: {ftdiDeviceList[i].Description}");
        msg += string.Format($"\nFlags: {ftdiDeviceList[i].Flags}");
        msg += string.Format($"\nftHandle: {ftdiDeviceList[i].ftHandle}");
        msg += string.Format($"\nID: {ftdiDeviceList[i].ID}");
        msg += string.Format($"\nLocId: {ftdiDeviceList[i].LocId}");
        msg += string.Format($"\nSerialNumber: {ftdiDeviceList[i].SerialNumber}");
        msg += string.Format($"\nType: {ftdiDeviceList[i].Type}");
        msg += "\n\n";
    }
    
    richTextBox1.Text = msg;
}

```

## Sending Data
```cs
void Send_serial_data(string serialNumber)
{
    ftdi.OpenBySerialNumber(serialNumber);

    if (ft_status != FTDI.FT_STATUS.FT_OK)
    {
        MessageBox.Show("FTDI status is not OK", "ERROR!!!");
        return;
    }

    ftdi.SetBaudRate(9600);
    ftdi.SetDataCharacteristics(
        FTDI.FT_DATA_BITS.FT_BITS_8, 
        FTDI.FT_STOP_BITS.FT_STOP_BITS_1, 
        FTDI.FT_PARITY.FT_PARITY_NONE
        );
    ftdi.SetTimeouts(2000, 0); // 2 second timeout

    UInt32 bytesWritten = 0;
    byte[] data = new byte[] { 1, 3, 7, 13, 21 };
    ft_status = ftdi.Write(data, data.Length, ref bytesWritten);
    ft_status = ftdi.Close();
    Console.WriteLine(ft_status);
}
```
