# Frontmatter Default

If this page has no title, this link will appear empty

```html
<a href="{{ .URL }}">
    {{ .Title }}
</a>
```

Placing a default title in the template is a solution

```html
<a href="{{ .URL }}">
    {{ .Title | default "no title" }}
</a>
```

_EDIT: This works in my section template but not on my page template..._
