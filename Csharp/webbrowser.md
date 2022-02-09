# WebBrowser Control

## Launch the default web browser
```cs
System.Diagnostics.Process.Start("explorer", "https://github.com/swharden/StupidTimer");
```

```cs
// WARNING: THIS DOES NOT WORK IN .NET CORE!
System.Diagnostics.Process.Start("http://google.com");
```

## Assign Content to a WebBrowser control
```cs
private void BrowserClear()
{
    string html =
        "<html><head><style>" +
        "body {font-family: consolas; font-size: .8em; background-color: controlColorHex; margin-top: 5px;}" +
        ".title {font-weight: bold; text-decoration: underline;}" +
        ".pass {font-weight: bold; color: green;}" +
        ".fail {font-weight: bold; color: red; background-color: yellow; border: 1px solid black; padding: 0px 5px 0px 5px;}" +
        "</style></head><body>" +
        "<div class='title'>SOFTWARE TEST SUITE</div>" +
        "</body></html>";

    string controlColorHex = ColorTranslator.ToHtml(Color.FromArgb(SystemColors.Control.ToArgb()));
    html = html.Replace("controlColorHex", controlColorHex);

    webBrowser1.Navigate("about:blank");
    webBrowser1.Refresh();
    webBrowser1.Document.OpenNew(true);
    webBrowser1.Document.Write(html);
}
```

```cs
private void BrowserAppend(string message, bool newLine = true, bool specialFormat = true)
{
    if (specialFormat)
    {
        message = message.Replace("PASS", "<span class='pass'>PASS</span>");
        message = message.Replace("FAIL", "<span class='fail'>FAIL</span>");
    }

    int insertPosition;
    if (newLine)
    {
        message = $"<div>{message}</div>";
        insertPosition = webBrowser1.DocumentText.LastIndexOf("</body>");
    }
    else
    {
        insertPosition = webBrowser1.DocumentText.LastIndexOf("</div>");
    }                

    webBrowser1.DocumentText = webBrowser1.DocumentText.Insert(insertPosition, message);
    Application.DoEvents();
}
```

## Clicking Links
omg this is the most rediculous crap

```cs
public void LinkClick(object sender, EventArgs e)
{
    string url = webBrowser2.Document.ActiveElement.GetAttribute("href");
    System.Console.WriteLine("CLICKED " + url);
}

private void webBrowser2_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
{
    foreach (HtmlElement link in webBrowser2.Document.Links)
    {
        System.Console.WriteLine("LINKING");
        link.AttachEventHandler("onclick", new EventHandler(LinkClick));
    }
}
```
