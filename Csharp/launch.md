# Launching things

## Open the control panel to a certain page
```cs
var controlPanelPath = System.IO.Path.Combine(Environment.SystemDirectory, "control.exe");
System.Diagnostics.Process.Start(controlPanelPath, "mmsys.cpl");
```

## Launch the default web browser
```cs
System.Diagnostics.Process.Start("http://google.com");
```
