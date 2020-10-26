# Launching things

## Start a new process (cross platform)
```cs
ProcessStartInfo psi = new ProcessStartInfo("pathToFile.exe") { UseShellExecute = true };
Process.Start(psi);
```

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
private void LaunchBrowser(string url)
{
	// A cross-platform .NET-Core-safe function to launch a URL in the browser
	Console.WriteLine($"Launching: {url}");
	try
	{
		Process.Start(url);
	}
	catch
	{
		if (System.Runtime.InteropServices.RuntimeInformation.IsOSPlatform(System.Runtime.InteropServices.OSPlatform.Windows))
			Process.Start(new ProcessStartInfo("cmd", $"/c start {url}") { CreateNoWindow = true });
		else if (System.Runtime.InteropServices.RuntimeInformation.IsOSPlatform(System.Runtime.InteropServices.OSPlatform.Linux))
			Process.Start("xdg-open", url);
		else if (System.Runtime.InteropServices.RuntimeInformation.IsOSPlatform(System.Runtime.InteropServices.OSPlatform.OSX))
			Process.Start("open", url);
		else
			throw;
	}
}
```
