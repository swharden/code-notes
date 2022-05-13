# Filesystem Navigation with Blazor

This setup allows me to show a file list for any folder and clicking folder names dives into that folder.

### Page: FileSystemBrowser.razor

```razor
@page "/fs"
@using BlazorApp5.Shared
@inject HttpClient Http
@inject NavigationManager NavigationManager

<PageTitle>Filesystem Browser</PageTitle>

<h1>Filesystem Browser</h1>

@if (Contents is null)
{
    <p><em>Loading...</em></p>
}
else if (Contents.IsError)
{
    <div class="alert alert-danger" role="alert">
        <h4 class="alert-heading">Error</h4>
        <p>@Contents.ErrorMessage?.Split("\n").First()</p>
        <hr>
        <pre>@Contents.ErrorMessage</pre>
    </div>
}
else
{
    <FolderPathLinks BaseUrl=@LinkBase Path=@Contents.Path></FolderPathLinks>

    <h3>Folders</h3>
    <ul>
        @foreach (string folderName in Contents.FolderNames)
        {
            <li>
                <NavLink href=@GetLink(folderName, true)>
                    @folderName
                </NavLink>
            </li>
        }
    </ul>

    <h3>Files</h3>
    <ul>
        @foreach (string fileName in Contents.FileNames)
        {
            <li>@fileName</li>
        }
    </ul>
}

@code {

    [Parameter]
    [SupplyParameterFromQuery(Name = "path")]
    public string? Path { get; set; }

    private FolderContents? Contents;

    private string LinkBase => NavigationManager.GetUriWithQueryParameter("path", string.Empty);

    protected override async Task OnParametersSetAsync()
    {
        Contents = await Http.GetFromJsonAsync<FolderContents>("Folder?path=" + Path);
    }

    private string GetLink(string newPath, bool relative = false)
    {
        if (relative)
            newPath = System.IO.Path.Combine(Contents!.Path, newPath);

        // forward slashes are used for routing so they can't be used in query parameters
        return LinkBase + newPath.Replace("/", "\\");
    }
}
```

### Component: FolderPathLinks.razor

```razor
<div class="font-monospace">
    @foreach ((string folderName, string folderPath) in Parts)
    {
        <a href=@GetLink(folderPath) class="">@folderName</a>

        <span class="" style="opacity: .5">/</span>
    }
</div>

@code {
    [Parameter]
    public string BaseUrl { get; set; } = string.Empty;

    [Parameter]
    public string Path { get; set; } = string.Empty;

    private (string, string)[] Parts = Array.Empty<(string, string)>();

    protected override void OnParametersSet()
    {
        string remainingPath = System.IO.Path.GetFullPath(Path.Replace("\\", "/")).TrimStart('/');
        List<(string, string)> parts = new();
        while (!string.IsNullOrWhiteSpace(remainingPath))
        {
            string folderName = System.IO.Path.GetFileName(remainingPath);
            if (string.IsNullOrWhiteSpace(folderName))
                break;
            parts.Insert(0, (folderName, remainingPath));
            remainingPath = System.IO.Path.GetDirectoryName(remainingPath) ?? string.Empty;
        }

        Parts = parts.ToArray();
    }

    private string GetLink(string folderPath)
    {
        return BaseUrl + folderPath.Replace("/", "\\");
    }
}
```

### Controller: FolderController.cs

```cs
using BlazorApp5.Shared;
using Microsoft.AspNetCore.Mvc;

namespace BlazorApp5.Server.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class FolderController : ControllerBase
    {
        private readonly ILogger<WeatherForecastController> _logger;

        public FolderController(ILogger<WeatherForecastController> logger)
        {
            _logger = logger;
        }

        [HttpGet]
        public FolderContents Get(string? path)
        {
            path = path ?? "C:/";
            Console.WriteLine($"requesting contents of: {path}");
            return FolderContents.Scan(path);
        }
    }
}
```

### Shared Class: FolderContents.cs

```cs
namespace BlazorApp5.Shared;

public class FolderContents
{
    public string Path { get; set; } = string.Empty;
    public string? ErrorMessage { get; set; } = null;
    public bool IsError => !string.IsNullOrWhiteSpace(ErrorMessage);
    public string[] FileNames { get; set; } = Array.Empty<string>();
    public string[] FolderNames { get; set; } = Array.Empty<string>();

    public static FolderContents Scan(string folderPath)
    {
        folderPath = System.IO.Path.GetFullPath(folderPath);

        try
        {
            return new FolderContents()
            {
                Path = folderPath,
                FileNames = Directory.GetFiles(folderPath).Select(x => System.IO.Path.GetFileName(x)).ToArray(),
                FolderNames = Directory.GetDirectories(folderPath).Select(x => System.IO.Path.GetFileName(x)).ToArray(),
            };
        }
        catch (Exception ex)
        {
            return new FolderContents()
            {
                Path = folderPath,
                ErrorMessage = ex.ToString(),
            };
        }

    }
}
```
