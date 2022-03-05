# Convert SVG to Favicon.ico

This script creates transparent PNGs and a transparent `favicon.ico` with multiple sizes included

* Reference: [How to Favicon in 2022](https://evilmartians.com/chronicles/how-to-favicon-in-2021-six-files-that-fit-most-needs)

```bash
:: create large PNGs with transparent backgrounds
convert -background transparent favicon.svg -resize 512x512 favicon-512.png
convert -background transparent favicon.svg -resize 256x256 favicon-256.png
convert -background transparent favicon.svg -resize 192x192 favicon-192.png

:: resize the transparent PNG to individual sizes
convert favicon-256.png -resize 16x16 favicon-16.png
convert favicon-256.png -resize 32x32 favicon-32.png
convert favicon-256.png -resize 64x64 favicon-64.png
convert favicon-256.png -resize 128x128 favicon-128.png

:: create a small and simple 32px icon file
convert favicon-32.png -colors 256 favicon-32.ico

:: pack individual sizes into a single icon file
convert favicon-16.png favicon-32.png favicon-64.png favicon-128.png favicon-256.png -colors 256 favicon.ico

pause
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
