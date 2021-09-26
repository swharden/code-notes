# How to Walk a Directory Tree

This example is more complex but does a better job preventing exceptions in edge cases:
https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/file-system/how-to-iterate-through-a-directory-tree

```cs
/// <summary>
/// Recursively scan a directory tree and build an array containing paths to
/// all files found with filenames matching the given pattern.
/// </summary>
private static string[] FindFiles(DirectoryInfo root, string searchPattern = "*.cs")
{
    var mdFilePaths = new List<string>();

    string[] files = Directory.GetFiles(root.FullName, searchPattern);
    mdFilePaths.AddRange(files);

    foreach (DirectoryInfo dir in root.GetDirectories())
        mdFilePaths.AddRange(FindFiles(dir));

    return mdFilePaths.ToArray();
}
```
