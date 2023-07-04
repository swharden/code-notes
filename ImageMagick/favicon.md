# Convert SVG to Favicon.ico

This script creates transparent PNGs and a transparent `favicon.ico` with multiple sizes included

* Reference: [How to Favicon in 2022](https://evilmartians.com/chronicles/how-to-favicon-in-2021-six-files-that-fit-most-needs)

```bash
convert -background none favicon.svg -define icon:auto-resize=64,48,32,16 favicon.ico
```

## Favicon Cheat Sheet

* `/favicon.ico` 32px (or multi-size)
* `/favicon.svg`
* `/favicon-180.png`
* `/favicon-192.png`
* `/favicon-512.png`
* `/manifest.webmanifest`

The web manifest file contains:

```json
{
  "icons": [
    { "src": "/favicon-192.png", "type": "image/png", "sizes": "192x192" },
    { "src": "/favicon-512.png", "type": "image/png", "sizes": "512x512" }
  ]
}
```

```html
<link rel="icon" href="/favicon.ico" sizes="any"><!-- 32×32 -->
<link rel="icon" href="/favicon.svg" type="image/svg+xml">
<link rel="apple-touch-icon" href="/favicon-180.png"><!-- 180×180 -->
<link rel="manifest" href="/manifest.webmanifest">
```
