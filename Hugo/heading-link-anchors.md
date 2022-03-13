# Automatically Link Heading Anchors with Hugo

This code will automatically add a link to the anchor for each header on the page

```html
<article>
    {{- with .Content -}}
    <div itemid="articleBody">
      {{ . | replaceRE "(<h[1-9] id=\"([^\"]+)\".+)(</h[1-9]+>)" `${1}<a href="#${2}" class="hanchor" ariaLabel="Anchor"> 🔗&#xFE0E;</a> ${3}` | safeHTML }}
    </div>
    {{- end -}}
</article>
```
