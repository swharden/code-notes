# User Controls

## Execute code on load (only in an application, not in VS design mode)

```cs
if (LicenseManager.UsageMode == LicenseUsageMode.Designtime)
{
    // in Visual Studio
}
else
{
    // in the wild
}
```

```cs
bool isInFormsDesignerMode = (System.Diagnostics.Process.GetCurrentProcess().ProcessName == "devenv");
```
