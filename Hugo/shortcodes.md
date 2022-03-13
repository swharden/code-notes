# Useful Hugo Shortcodes

### Show page build date

```html
<div>
    Built with Hugo {{ .Site.Hugo.Version }}
    on {{ time now | time.Format ":date_long" }} 
    at {{ time now "America/New_York" | time.Format ":time_short" }} EST
</div>
```

### Link to Source Code

This code adds a link to to this `index.md` on GitHub.

The `Clean` step converts backslashes to forward slashes (correcting for Windows builds)

```html
<a href="https://github.com/swharden/repo/blob/main/website/content{{ path.Clean .File.Path }}">
    View Source
</a>
```
