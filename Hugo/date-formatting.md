# Date Formatting in Hugo

## Separate Written and Updated Page Times

```
---
title: example page
date: 2022-03-08 7:38:00
updated: 2022-03-09 12:34:56
---

sample content
```

```html
<div>
    Written: {{ .Date.Format "January 2, 2006" }}
</div>

{{ if isset .Params "updated" }}
<div>
    Updated: {{ .Params.updated | dateFormat "Monday, Jan 2, 2006" }}
</div>
{{ end }}
```
