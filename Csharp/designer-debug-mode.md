# Detecting Designer Mode

```cs
// this is the recommended way
bool isDesignMode = Process.GetCurrentProcess().ProcessName == "devenv";
```

```cs
bool isDesignMode = DesignerProperties.GetIsInDesignMode(this);
```
```cs
bool isDesignMode = LicenseManager.UsageMode == LicenseUsageMode.Designtime;
```

# Detecting Debug Mode
```cs
if (Debugger.IsAttached) {}
```
