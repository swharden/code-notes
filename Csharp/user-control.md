# User Controls

## Execute code on load (only in an application, not in VS design mode)

```cs
bool isInFormsDesignerMode = (System.Diagnostics.Process.GetCurrentProcess().ProcessName == "devenv");
if (!isInFormsDesignerMode)
    timerInitialScan.Enabled = true;
```

``cs
private bool InsideVisualStudio { get { return (System.Diagnostics.Process.GetCurrentProcess().ProcessName == "devenv"); } }
``
