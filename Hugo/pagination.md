# Pagination in Hugo

### Previous/Next Links

I like restricting links to those only in the same section

```html
{{ if .PrevInSection }}
<div>Next: <a href="{{ .PrevInSection.Permalink }}">{{ .PrevInSection.Title }}</a></div>
{{ end }}

{{ if .NextInSection }}
<div>Previous: <a href="{{ .NextInSection.Permalink }}">{{ .NextInSection.Title }}</a></div>
{{ end }}

{{ with .Site.GetPage "section" .Section }}
<div>Section: <a href='{{ .Permalink }}'>{{ .Title }}</a></div>
{{ end }}
```
