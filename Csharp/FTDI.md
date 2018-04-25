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
