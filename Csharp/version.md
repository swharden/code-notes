# Versioning in C#

## AssemblyVersion

In .NET Framework projects add this to Program.cs
```cs
using System.Reflection;
[assembly: AssemblyVersion("1.5.0.0")]
```

Reference it like this:
```cs
string version = $"Version {Application.ProductVersion}";
```

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
