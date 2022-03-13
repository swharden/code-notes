# Show RSS in `/feed/` with Hugo

Hugo's default URL for the RSS file is `/index.xml` but I prefer to have this in `/feed/`. I accomplish this by making the output file `/feed/index.xml` then use a custom `.htaccess` file to serve it as the index.

### config.toml

This configures Hugo to generate the RSS file as `/feed/index.xml`

```toml
[outputFormats]
  [outputFormats.RSS]
    mediatype = "application/rss"
    path = "feed"
    baseName = "index"
```

### /static/feed/.htaccess

This configures Apache to serve the XML file as the index

```
Options +Indexes
DirectoryIndex index.xml
```

### /static/feed/index.html

Creating an `index.html` allows a fallback if Apache (or .htaccess) is not supported

```html
<html>

<head>
    <meta http-equiv="refresh" content="0; URL=index.xml" />
</head>

<body>
    <p>Redirecting to <a href="index.xml">index.xml</a> ...</p>
</body>

</html>
```
