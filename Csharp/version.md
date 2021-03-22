## Version Tracking with Assembly

### Create and Parse Versions
```cs
Version version = Version("1.2.3");
Console.WriteLine($"{version.Major}.{version.Minor}.{version.Build}");
```

### Get Version of This Project
```cs
Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
Console.WriteLine($"{version.Major}.{version.Minor}.{version.Build}");
```

### Get Version of Another Project
```cs
var version = typeof(WsprSharp.WsprTransmission).Assembly.GetName().Version;
Text = $"WSPR Inspector v{version.Major}.{version.Minor}";
```
