# Minimal C# HTTP Server

```cs
using System.Net;
using System.Text;

using var listener = new HttpListener();
listener.Prefixes.Add("http://localhost:8001/");

listener.Start();

Console.WriteLine("Listening on port 8001...");

while (true)
{
    HttpListenerContext context = listener.GetContext();
    HttpListenerRequest req = context.Request;

    Console.WriteLine($"Received request for {req.Url}");

    using HttpListenerResponse resp = context.Response;
    resp.Headers.Set("Content-Type", "text/plain");

    string data = "Hello there!";
    byte[] buffer = Encoding.UTF8.GetBytes(data);
    resp.ContentLength64 = buffer.Length;

    using Stream ros = resp.OutputStream;
    ros.Write(buffer, 0, buffer.Length);
}
```
