# Date Formatting in Hugo

## Separate Written and Updated Page Times

```
---
title: example page
date: 2022-03-08 7:38:00
lastmod: 2022-03-09 12:34:56
---
```

```html
<a href="{{ .Permalink }}" class="text-dark">
    {{ if not .Date.IsZero }}
    {{ .Date.Format "January 2, 2006" }}
    {{ end }}

    {{ if ne .Date .Lastmod }}
    (updated on {{ .Params.lastmod | dateFormat "Jan 2, 2006" }})
    {{ end }}
</a>
```
