namespace BlazorApp5.Shared;

public class FolderContents
{
    public string Path { get; set; } = string.Empty;
    public string[] FileNames { get; set; } = Array.Empty<string>();
    public string[] FolderNames { get; set; } = Array.Empty<string>();

    public static FolderContents Scan(string folderPath)
    {
        folderPath = System.IO.Path.GetFullPath(folderPath);
        return new FolderContents()
        {
            Path = folderPath,
            FileNames = System.IO.Directory.GetFiles(folderPath).Select(x => System.IO.Path.GetFileName(x)).ToArray(),
            FolderNames = System.IO.Directory.GetDirectories(folderPath).Select(x => System.IO.Path.GetFileName(x)).ToArray(),
        };
    }
}
