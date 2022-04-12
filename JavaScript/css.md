# Working with CSS in JavaScript

## Add a text css block
```js
let style = document.createElement('style');
style.innerHTML = `
    body {
        background-color: magenta;
    }
    `;
document.head.appendChild(style);
```

## Add external CSS file dynamically
```js
let link = document.createElement("link");
link.href = "style.css";
link.type = "text/css";
link.rel = "stylesheet";
link.media = "screen,print";
document.head.appendChild(link);
```
