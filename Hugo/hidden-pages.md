# Hidden Pages in Hugo

Some pages I don't want paginated or indexed by search. I define this using custom frontmatter:

```md
---
title: Sample Hidden Page
hidden: true
noindex: true
---
```

Pagination logic:
```html
{{ $pages := where site.RegularPages ".Params.hidden" "!=" true }}

{{ with $pages.Next . }}
<div>Next: <a href="{{ .Next.Permalink }}">{{ .Next.Title }}</a></div>
{{ end }}

{{ with $pages.Prev . }}
<div>Previous: <a href="{{ .Prev.Permalink }}">{{ .Prev.Title }}</a></div>
{{ end }}
```

Head logic:
```html
{{ if .Params.noindex }}
<meta name="robots" content="noindex">
{{ end }}
```
