# File Operations

## Reading/Writing Text Files

```c#
System.IO.File.WriteAllText(saveAs, html);
string xml = System.IO.File.ReadAllText(pathLinescanXML);
string[] xmlLines = System.IO.File.ReadAllLines(pathLinescanXML);
```

## Get File Size
```cs
sizeMB = new System.IO.FileInfo(path).Length/1e6;
```

## Join (Combine) Dirname and Basename
```cs
string cellsFilePath = System.IO.Path.Combine(folder, cellsFileName);
```

## Reading Binary Files
```cs
BinaryReader br = new BinaryReader(File.Open(abfFilePath, FileMode.Open));
br.BaseStream.Seek(0, SeekOrigin.Begin);
byte[] firstFew = br.ReadBytes(4);
string firstFewStr = System.Text.Encoding.Default.GetString(firstFew);
```

## List Files or Folders
```cs
string[] pathsFiles = System.IO.Directory.GetFiles(pathFolder, "*.tif");
string[] pathsFolders = System.IO.Directory.GetDirectories(pathFolder);
```

## List Directories Ordered by Creation Date
```cs
var di = new System.IO.DirectoryInfo(PathOutputFolder);
var folderNames = di.EnumerateDirectories()
                    .OrderBy(d => d.CreationTime)
                    .Select(d => d.Name)
                    .ToList();
folderNames.Reverse();
for (int i=0; i<folderNames.Count; i++)
    folderNames[i] = System.IO.Path.GetFileName(folderNames[i]);
```
