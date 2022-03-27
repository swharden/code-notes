# Add a Table of Contents to a Hugo Page

### Create `layouts/shortcodes/toc.html`
```
{{ .Page.TableOfContents }}
```

### Add a TOC to a Markdown page
```
# Table of Contents
{{< toc >}}
```
