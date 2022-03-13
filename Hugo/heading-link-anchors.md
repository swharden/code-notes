# Automatically Link Heading Anchors with Hugo

This code will automatically add a link to the anchor for each header on the page

```html
<article>
    {{- with .Content -}}
    {{ . | replaceRE "(<h[1-9] id=\"([^\"]+)\".+)(</h[1-9]+>)"
        `<a href="#${2}" class="hanchor" ariaLabel="Anchor">${1}</a> ${3}` | safeHTML }}
        {{- end -}}
</article>
```
