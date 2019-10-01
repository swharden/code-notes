# User Controls

## Execute code on load (only in an application, not in VS design mode)

```cs
// USE THIS FOR WPF
if (LicenseManager.UsageMode == LicenseUsageMode.Designtime)
{
    // in Visual Studio
}
else
{
    // in the wild
}
```

## Actually, this seems to work better

```cs
// USE THIS FOR WINFORMS
bool isInFormsDesignerMode = (System.Diagnostics.Process.GetCurrentProcess().ProcessName == "devenv");
```

```cs
if (Process.GetCurrentProcess().ProcessName == "devenv")
```
