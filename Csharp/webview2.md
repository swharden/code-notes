# Web View 2

Get the NuGet package: https://www.nuget.org/packages/Microsoft.Web.WebView2

```cs
public Form3()
{
    InitializeComponent();
    Load += Form3_Load;
}

private async void Form3_Load(object? sender, EventArgs e)
{
    await webView21.EnsureCoreWebView2Async();
    webView21.NavigateToString("<html><body>test123</body></html>");
}
```

## Sensing Clicks

```cs
// in your startup sequence
webView21.WebMessageReceived += WebView21_WebMessageReceived;
```

```cs
private void WebView21_WebMessageReceived(object? sender, Microsoft.Web.WebView2.Core.CoreWebView2WebMessageReceivedEventArgs e)
{
    Text = e.WebMessageAsJson.Trim('"');
}
```

```js
// in your JavaScript
window.chrome.webview.postMessage('test123');
```
