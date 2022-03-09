# Syntax Highlighting with Hugo

* Style demos: https://xyproto.github.io/splash/docs/all.html
* Syntax highlighting: https://gohugo.io/content-management/syntax-highlighting/
* Syntax highlighting configuration: https://gohugo.io/getting-started/configuration-markup#highlight

## Set Style

### config.toml

```toml
[markup]
  [markup.highlight]
    anchorLineNos = false
    codeFences = true
    guessSyntax = false
    hl_Lines = ''
    lineAnchors = ''
    lineNoStart = 1
    lineNos = false
    lineNumbersInTable = true
    noClasses = true
    noHl = false
    style = 'abap'
    tabWidth = 4
```

## Customize Style

To customize a style:

1. Turn off the `noClasses` configuration flag

2. Use Hugo to generate a custom CSS file for syntax highlighting

```bash
hugo gen chromastyles --style=abap > static/syntax.css
```

3. Configure your layout to use the custom CSS file

```html
<link href="/syntax.css" rel="stylesheet">
```
