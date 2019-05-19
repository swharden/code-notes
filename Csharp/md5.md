# MD5 File Hashing
```cs
var md5 = System.Security.Cryptography.MD5.Create();
string[] imageFilePaths = System.IO.Directory.GetFiles($"./", "*.png");
foreach (string filePath in imageFilePaths)
{
    string hashString = "";
    using (var stream = System.IO.File.OpenRead(filePath))
    {
        byte[] hashBytes = md5.ComputeHash(stream);
        for (int i = 0; i < hashBytes.Length; i++)
            hashString += hashBytes[i].ToString("X2");
    }
    Console.WriteLine($"{hashString} {System.IO.Path.GetFileName(filePath)}");
}
```

Output:
```
FB6E91ED7B3A82002E3DE07395CCB698 01_Scatter_Sin.png
826A036491DAA617499D4CEAF562BC86 02_Scatter_Sin_Styled.png
7D4245E66993097B62DA1004F24DFCBF 03_Scatter_XY.png
455055FF41ED8C7CDB0753F0B1208E4C 04_Scatter_XY_Lines_Only.png
ACCCAEE3BD1279389A60F8DC36BB7277 05_Scatter_XY_Points_Only.png
C5B0652A24CAAC2EDDDB2D6408511AF2 06_Scatter_XY_Styling.png
5E38ED33B32B0BD79A0E900331F35D94 07_Point.png
FE4FB28182BC179B7E08B4F804EEDA8B 08_Text.png
5DC04B0CA9E40D82C5114BC91730658E 20_Small_Plot.png
466876D94F76C33F3E95F220FE946CB8 21_Title_and_Axis_Labels.png
75813E0A2F2BE3FD18F88B4B51BE669E 22_Custom_Colors.png
50656DCC277FF318569D27A597A71934 23_Frameless.png
```
