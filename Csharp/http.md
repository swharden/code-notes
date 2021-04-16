# HTTP C# Examples

## Download a File

```cs
using WebClient client = new();
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
