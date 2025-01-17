# Locate the Repository Folder

I use this method to identify the root folder of the source code repository regardless of what foler we are in (inside the repository) when an application is launched. This is useful for locating files in the repository reglardless if we are building and running in debug mode inside Visaual Studio or whether we are using `dotnet run` from a different folder.

```cs
// Return the root folder of the repository we are currently in
static string GetRepositoryFolder(string filename = "LICENSE")
{
    string? path = Path.GetFullPath("./");
    while (path is not null)
    {
        if (File.Exists(Path.Combine(path, filename)))
            return path;
        path = Path.GetDirectoryName(path);
    }
    throw new DirectoryNotFoundException();
}
```
