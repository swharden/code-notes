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
```cs
WebRequest request = WebRequest.Create(url);
request.Method = "HEAD";
var response = request.GetResponse();
DateTime modified = DateTime.Parse(response.Headers["Last-Modified"]);
DateTime now = DateTime.Parse(response.Headers["Date"]);
TimeSpan age = now - modified;
```
