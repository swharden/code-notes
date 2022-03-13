# Prevent CSS Caching with Hugo

Browsers tend to cache CSS files which makes development difficult.

This code adds a random query string generated on every build based on the time.

```html
<link rel="stylesheet" href="/csdv/css/page.css?{{ md5 (now|time) }}">
```

Result:
```html
<link rel="stylesheet" href="/csdv/css/page.css?7a92c861ccf06ed4fd80f8c234f2309c">
```
