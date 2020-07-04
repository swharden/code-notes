# Detecting Designer Mode
```cs
bool isDesignerMode = DesignerProperties.GetIsInDesignMode(this);
```
```cs
bool designMode = LicenseManager.UsageMode == LicenseUsageMode.Designtime;
```

# Detecting Debug Mode
```cs
if (Debugger.IsAttached) {}
```
