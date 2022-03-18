## GZip Compression in C#

```cs
using System.IO.Compression;
```

```cs
string filePath = "sample.gz";
using FileStream compressedFileStream = File.Open(filePath, FileMode.Open);
using GZipStream decompressor = new(compressedFileStream, CompressionMode.Decompress);

string filePathOut = "sample.txt";
using FileStream outputFileStream = File.Create(filePathOut);
decompressor.CopyTo(outputFileStream);
Console.WriteLine(filePathOut);
```
