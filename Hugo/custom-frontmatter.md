# Custom Frontmatter Parameters with Hugo

```md
---
noindex: true
---
```

```html
{{ if .Params.noindex }}
<meta name="robots" content="noindex">
{{ end }}
```
