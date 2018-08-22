# Paths and Filenames

## Determine if file/folder exists
```cs
using System.IO; // provides File and Directory objects

if (Directory.Exists(someFolder)) {}
if (File.Exists(someFile)) {}
```

## Get File Extension
```c#
string extension = System.IO.Path.GetExtension(filename);
string everythingElse = System.IO.Path.GetFileNameWithoutExtension(filename);
```

## List Directories
```C#
string[] filePaths = System.IO.Directory.GetFiles("./", "*.png", System.IO.SearchOption.TopDirectoryOnly);
```

## Generating HTML for Image Folder
```C#
public static void HTMLgen(string saveAs="output.html", bool launch=true)
{
  string[] filePaths = System.IO.Directory.GetFiles("./", "*.png", System.IO.SearchOption.TopDirectoryOnly);
  string html = "<html><body>";
  html += "<h1>ScottPlot Test Sequence</h1><hr>";
  foreach (string filePath in filePaths) html += $"<img src='{filePath}'><br>";
  html += "</body></html>";
  System.IO.File.WriteAllText(saveAs, html);
  System.Diagnostics.Process.Start("explorer", saveAs);
}
```

## Reading/Writing Text Files

```c#
System.IO.File.WriteAllText(saveAs, html);
```
