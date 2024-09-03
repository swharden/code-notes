# Copy Text to the Clipboard with JavaScript

## Secure Copy (requires HTTPS)

```js
function secureCopyToClipboard(text) {
    navigator.clipboard.writeText(text);
}
```

## Insecure Copy (always works)
```js
function insecureCopyToClipboard(text) {
    const textArea = document.createElement("textarea");
    textArea.value = text;
    document.body.appendChild(textArea);
    textArea.focus();
    textArea.select();
    document.body.removeChild(textArea);
}
```
