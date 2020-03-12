## Version Tracking with Assembly

```cs
// use the built-in Version class
Version version = Version("1.2.3");
Console.WriteLine($"{version.Major}.{version.Minor}.{version.Build}");
```

```cs
// get the version of this application
Version version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
Console.WriteLine($"{version.Major}.{version.Minor}.{version.Build}");
```

```cs
// get the version of something else
Version ver = typeof(Form1).Assembly.GetName().Version;
lblVersion.Text = ver.ToString();
```

```
<Version>1.0.2</Version>
<AssemblyVersion>1.0.2</AssemblyVersion>
<FileVersion>1.0.2</FileVersion>
```
