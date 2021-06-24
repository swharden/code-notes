# MD5 Hash with C#

## MD5 Hash of Byte Array
```cs
public static string MD5(byte[] bytes)
{
    var md5 = System.Security.Cryptography.MD5.Create();
    return string.Join("", md5.ComputeHash(bytes).Select(x => x.ToString("x2")).ToArray());
}
```

## MD5 Hash of File

```cs
string GetMD5Hash(string filePath)
{
    var md5 = System.Security.Cryptography.MD5.Create();
    using var stream = File.OpenRead(filePath);
    return string.Join("", md5.ComputeHash(stream).Select(x => x.ToString("x2")));
}
```

## Get MD5 File Hash from Windows Command Line

```bash
C:\>certutil -hashfile myFile.bmp MD5
MD5 hash of myFile.bmp:
08ded0757f32ed733f958526693cad66
```
