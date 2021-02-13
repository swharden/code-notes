# Editing Registry with C#

## Start Application with Windows

```cs
const string RUN_PATH = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
const string RUN_VALUE_NAME = "Tmoji";

private string TmojiExePath() => 
    System.Reflection.Assembly.GetExecutingAssembly().Location;

private bool StartWithWindowsIsEnabled()
{
    var key = Microsoft.Win32.Registry.CurrentUser.OpenSubKey(RUN_PATH, true);
    if (key is null)
        return false;

    var val = key.GetValue(RUN_VALUE_NAME);
    if (val is null)
        return false;

    return val.ToString() == TmojiExePath();
}

private void StartWithWindows(bool enable)
{
    var key = Microsoft.Win32.Registry.CurrentUser.OpenSubKey(RUN_PATH, true);

    if (enable)
    {
        if (key is null)
            Microsoft.Win32.Registry.CurrentUser.CreateSubKey(RUN_PATH);

        key.SetValue(
            name: RUN_VALUE_NAME,
            value: TmojiExePath(),
            valueKind: Microsoft.Win32.RegistryValueKind.String);
    }
    else
    {
        key.DeleteValue("Tmoji", throwOnMissingValue: false);
    }
}
```
