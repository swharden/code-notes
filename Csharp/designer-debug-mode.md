# Detecting Designer Mode

[Component.DesignMode Property](https://learn.microsoft.com/en-us/dotnet/api/system.componentmodel.component.designmode?view=net-7.0)

```cs
[System.ComponentModel.Browsable(false)]
protected bool DesignMode { get; }
```

```cs
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
