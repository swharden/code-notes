# Determine if Hugo is serving locally

This method can be used to enable test pages that do not appear in production builds

```
{{ if in .Site.BaseURL "localhost"}}
<!-- this only appears when Hugo server is running locally -->
{{end}}
```
