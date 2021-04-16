# HTTP C# Examples

## Download a File

```cs
using WebClient client = new();
client.DownloadFile("http://somewhere.com/test.jpg", "test.jpg");
```
