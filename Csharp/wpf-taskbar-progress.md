# Show Progress on Taskbar Icon (WPF)

```cs
public MainWindow()
{
    InitializeComponent();
    TaskbarItemInfo = new();
}
```

```cs
void UpdateProgress(double fraction)
{
    TaskbarItemInfo.ProgressState = TaskbarItemProgressState.Normal;
    TaskbarItemInfo.ProgressValue = fraction;
}
```

https://docs.microsoft.com/en-us/dotnet/api/system.windows.shell.taskbariteminfo.progressstate?view=windowsdesktop-6.0

![image](https://user-images.githubusercontent.com/4165489/185797799-5866d035-50bd-40c7-b1bb-02354aa1eb55.png)
