# WebBrowser Control

## Assigning Content
```cs
string html="<html><body>hello world</body></html>";
webBrowser2.DocumentText = key;
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
