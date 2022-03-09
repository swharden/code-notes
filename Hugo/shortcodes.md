# Useful Hugo Shortcodes

### Show page build date

```html
Built on {{ now | time.Format ":date_long" }} at {{ now | time.Format ":time_short" }}
```

### Link to Source Code

This code adds a link to to this `index.md` on GitHub

```html
<a href="https://github.com/swharden/repo/blob/main/website/content{{ .RelPermalink }}{{ .File.LogicalName }}">
    View Source
</a>
```
