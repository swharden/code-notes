# File Operations

## Reading/Writing Text Files

```c#
System.IO.File.WriteAllText(saveAs, html);
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
