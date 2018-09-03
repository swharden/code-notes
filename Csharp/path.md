# Paths and Filenames

## Absolute File Path
```cs
System.IO.Path.GetFullPath(folder);
```

## Determine if file/folder exists
```cs
if (System.IO.Directory.Exists(someFolder)) {}
if (System.IO.File.Exists(someFile)) {}
```

## Get File Extension
```c#
string extension = System.IO.Path.GetExtension(filename);
string everythingElse = System.IO.Path.GetFileNameWithoutExtension(filename);
```

## List Files in a Directory

```cs
string[] folders = Directory.GetDirectories(folderPath);
string[] files = Directory.GetFiles(folderPath);
string[] filesPng = Directory.GetFiles(folderPath, "*.png");
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

