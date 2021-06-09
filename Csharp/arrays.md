# Arrays

## Array.Copy

This method copies _elements_ from one array to another.

The input and output arrays must have the same data type.

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

## Buffer.BlockCopy

This method copies _bytes_ from one array to another.

This is useful when transforming a byte array to an array of multi-byte elements.

```cs
int[] vals1 = { 1111, 2222, 1234 };
Console.WriteLine("vals1: " + string.Join(", ", vals1.Select(x=>x.ToString())));

byte[] bytes = new byte[sizeof(int) * vals1.Length];
Buffer.BlockCopy(vals1, 0, bytes, 0, bytes.Length);
Console.WriteLine("bytes: " + string.Join(", ", bytes.Select(x=>x.ToString())));

int[] vals2 = new int[bytes.Length / sizeof(int)];
Buffer.BlockCopy(bytes, 0, vals2, 0, bytes.Length);
Console.WriteLine("vals2: " + string.Join(", ", vals2.Select(x=>x.ToString())));
```

```
vals1: 1111, 2222, 1234
bytes: 87, 4, 0, 0, 174, 8, 0, 0, 210, 4, 0, 0
vals2: 1111, 2222, 1234
```
