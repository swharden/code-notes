# Launching things

## Open a folder in Explorer
```cs
// just open an explorer window into a folder
System.Diagnostics.Process.Start("explorer.exe", pathLinescan);

// or get fancy and pre-select a file or folder
System.Diagnostics.Process.Start("explorer.exe", $"/select, \"{pathLinescan}\"");
```

## Open the control panel to a certain page
```cs
var controlPanelPath = System.IO.Path.Combine(Environment.SystemDirectory, "control.exe");
System.Diagnostics.Process.Start(controlPanelPath, "mmsys.cpl");
```

## Launch the default web browser
```cs
System.Diagnostics.Process.Start("http://google.com");
```
