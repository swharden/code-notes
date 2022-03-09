# Syntax Highlighting with Hugo

* Style demos: https://xyproto.github.io/splash/docs/all.html
* Syntax highlighting: https://gohugo.io/content-management/syntax-highlighting/
* Syntax highlighting configuration: https://gohugo.io/getting-started/configuration-markup#highlight

## Use Standard Syntax Highlighting Style

_This method uses CSS styles built-in to Hugo_

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

## Customize Syntax Highlighting Style

_This method uses a CSS file to set syntax highlighting styles so you can customize it manually as desired_

1. Turn off the `noClasses` configuration flag

2. Use Hugo to generate a custom CSS file for syntax highlighting

```bash
hugo gen chromastyles --style=dracula > static/syntax.css
```

3. Configure your layout to use the custom CSS file

```html
<link href="/syntax.css" rel="stylesheet">
```
