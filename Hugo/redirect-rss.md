# Show RSS in `/feed/` with Hugo

Hugo's default URL for the RSS file is `/index.xml` but I prefer to have this in `/feed/`. I accomplish this by making the output file `/feed/index.xml` then use a custom `.htaccess` file to serve it as the index. 

### config.toml

```toml
[outputFormats]
  [outputFormats.RSS]
    mediatype = "application/rss"
    path = "feed"
    baseName = "index"
```

### `/static/feed/.htaccess`

```
Options +Indexes
DirectoryIndex index.xml
```

### Alternative: Redirect

For users not using Apache (or `.htaccess`) an alternative appropach is to create `/static/feed/index.html` that forwards to the permanent location of the feed XML file:

```html
<html>

<head>
    <meta http-equiv="refresh" content="0; URL=../index.xml" />
</head>

<body>
    <p>Redirecting to <a href="../rss.xml">../index.xml</a> ...</p>
</body>

</html>
```
