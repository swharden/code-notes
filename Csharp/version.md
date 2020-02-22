## Version Tracking with Assembly

```cs
Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
Console.WriteLine(version);
Console.WriteLine($"{version.Major}.{version.Minor}.{version.Build}");
```

```
<Version>1.0.2</Version>
<AssemblyVersion>1.0.2</AssemblyVersion>
<FileVersion>1.0.2</FileVersion>
```
