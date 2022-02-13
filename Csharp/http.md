# HTTP C# Examples

## HttpClient

In modern .NET `HttpClient` is preferred over `WebClient`

```cs
private static JsonDocument RequestJson(string url) => RequestJsonAsync(url).Result;
```

```cs
private static async Task<JsonDocument> RequestJsonAsync(string url)
{
    using HttpClient client = new();
    using HttpResponseMessage response = await client.GetAsync(url);
    using HttpContent content = response.Content;
    string json = await content.ReadAsStringAsync();
    return JsonDocument.Parse(json);
}
```

```cs
public static async Task<(int, int, double)> GetResponseTimeAsync(string url)
{
    HttpClient client = new();
    Stopwatch sw = Stopwatch.StartNew();
    using HttpResponseMessage response = await client.GetAsync(url);
    sw.Stop();
    double msec = sw.Elapsed.TotalMilliseconds;
    using HttpContent content = response.Content;
    string contentText = await content.ReadAsStringAsync();
    int length = contentText.Length;
    int code = (int)response.StatusCode;
    return (code, length, msec);
}
```

## Download a File

> ⚠️ WARNING: `WebClient` is deprecated in favor of `HttpClient`

```cs
using WebClient client = new();

// download text
string txt = client.DownloadString("http://somewhere.com/test.txt");

// download a file
client.DownloadFile("http://somewhere.com/test.jpg", "test.jpg");
```

## Request Headers Only
```cs
WebRequest request = WebRequest.Create(url);
request.Method = "HEAD";
var response = request.GetResponse();
```

## Determine Age of Resource
You may be able to determine the age of a remote resource without having to download it. Not all HTTP servers return file modified info though (e.g., Dropbox)
```cs
WebRequest request = WebRequest.Create(url);
request.Method = "HEAD";
var response = request.GetResponse();
DateTime modified = DateTime.Parse(response.Headers["Last-Modified"]);
DateTime now = DateTime.Parse(response.Headers["Date"]);
TimeSpan age = now - modified;
```

## Determine Hash of Resource
The [HTTP ETag](https://en.wikipedia.org/wiki/HTTP_ETag) is a unique hash to a resource and changes if the remote resource changes. The algorythm used to create the hash is not specified though, and could vary across servers. You can get the ETag without downloading the resource itself.
```cs
WebRequest request = WebRequest.Create(grabber.ImageUrl);
request.Method = "HEAD";
var response = request.GetResponse();
string tag = response.Headers["ETag"] ?? "no tag";
```
