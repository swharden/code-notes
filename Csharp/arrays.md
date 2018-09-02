# Arrays

## joining arrays

```cs
string[] folderPaths;
folderPaths = System.IO.Directory.GetDirectories(pathFolder);
string[] filePaths;
filePaths = System.IO.Directory.GetFiles(pathFolder, "*.*");

paths = new string[filePaths.Length + folderPaths.Length];

// join like this
Array.Copy(folderPaths, paths, folderPaths.Length);
Array.Copy(filePaths, 0, paths, folderPaths.Length, filePaths.Length);

// or like this
paths = folderPaths.Union(filePaths).ToArray();
```
