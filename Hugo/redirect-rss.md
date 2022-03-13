# Redirect `/feed/` to `/rss.xml`

### config.toml

This makes the RSS file `rss.xml` instead of the default `index.xml`

```toml
[outputFormats]
  [outputFormats.RSS]
    mediatype = "application/rss"
    baseName = "rss"
```

### static/feed/index.html

This redirects the folder-level URL to the XML file

```html
<html>

<head>
    <meta http-equiv="refresh" content="0; URL=../rss.xml" />
</head>

<body>
    <p>Redirecting to <a href="../rss.xml">../rss.xml</a> ...</p>
</body>

</html>
```
