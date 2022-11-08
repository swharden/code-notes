# Simple HTTP Request in Blazor WebAssembly

```razor
@page "/"
@inject HttpClient Http;
@using System.Text.Json

<button @onclick=RequestNow>request</button>

@code {
    async void RequestNow()
    {
        Uri uri = new("http://192.168.1.9/projects/locate.php");
        HttpResponseMessage msg = await Http.GetAsync(uri);
        string s = msg.Content.ReadAsStringAsync().Result;
    }
}
```

## Configure CORS _on the server_

```php
header('Access-Control-Allow-Origin: *');
header('Content-Type: application/json');
echo json_encode($things, JSON_PRETTY_PRINT);
```

If the server doesn't allow remote requests you'll get an error like:

```
Unhandled Exception:
System.Net.Http.HttpRequestException: TypeError: Failed to fetch
 ---> System.Runtime.InteropServices.JavaScript.JSException: TypeError: Failed to fetch
   at System.Net.Http.BrowserHttpHandler.SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
   --- End of inner exception stack trace ---
   at System.Net.Http.BrowserHttpHandler.SendAsync(HttpRequestMessage request, CancellationToken cancellationToken)
   at System.Net.Http.HttpClient.<SendAsync>g__Core|83_0(HttpRequestMessage request, HttpCompletionOption completionOption, CancellationTokenSource cts, Boolean disposeCts, CancellationTokenSource pendingRequestsCts, CancellationToken originalCancellationToken)
   at ProjectLocator.Pages.Index.RequestNow() in C:\Users\swharden\source\repos\ProjectLocator\ProjectLocator\Pages\Index.razor:line 15
   at System.Threading.Tasks.Task.<>c.<ThrowAsync>b__128_1(Object state)
   at System.Threading.QueueUserWorkItemCallbackDefaultContext.Execute()
   at System.Threading.ThreadPoolWorkQueue.Dispatch()
   at System.Threading.ThreadPool.Callback()
ThreadPool Callback threw an unhandled exception of type System.Net.Http.HttpRequestException
```
