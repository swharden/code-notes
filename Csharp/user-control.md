# User Controls

## Execute code on load (only in an application, not in VS design mode)

```cs
bool designMode = (LicenseManager.UsageMode == LicenseUsageMode.Designtime);
if (!designMode){
  // stuff
}
```
