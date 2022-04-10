# HTTP Requests with JavaScript

## Fetch

This is the modern way to use native JS to make HTTP requests

```js
fetch(`https://example.com`)
    .then(response => response.json())
    .then(data => console.log(data));
```
