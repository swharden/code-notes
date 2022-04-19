# Deploy using FTP from GitHub Actions

## Natively

```yaml
name: 🚀 FTP Deploy
on: push
jobs:
  ftp-deploy:
    runs-on: ubuntu-latest
    name: Upload
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v2
      - name: 📦 Get lftp
        run: sudo apt install lftp
      - name: 🔑 Load Secrets
        run: echo "machine ${{ secrets.FTP_HOSTNAME }} login ${{ secrets.FTP_USERNAME }} password ${{ secrets.FTP_PASSWORD }}" > $HOME/.netrc
      - name: 📄 Upload File
        run: lftp -e "set ftp:ssl-allow no; put -O / ./README.md" ${{ secrets.FTP_HOSTNAME }}
      - name: 📁 Upload Folder
        run: lftp -e "set ftp:ssl-allow no; mirror --parallel=100 -R ./ffmpeg /ffmpeg" ${{ secrets.FTP_HOSTNAME }}
```

Or without storing a secrets file:

```yaml
run: lftp -e "commands" -u ${{ secrets.FTP_USERNAME }},${{ secrets.FTP_PASSWORD }} ${{ secrets.FTP_HOSTNAME }}
```

## With a Dependency Action

⚠️ DO NOT DO THIS! ⚠️

It has some fancy features like using a JSON file to store state server-side and only uploaded changed files, but rsync is better for that, and this action has potential of compromise and leaking your secrets!

```yaml
name: Build and Deploy

on:
  workflow_dispatch:
  push:
    branches:
      - main

jobs:
  deploy:
    name: Build and Deploy
    runs-on: ubuntu-latest
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v2

      - name: ✨ Setup Hugo
        uses: peaceiris/actions-hugo@v2
        with:
          hugo-version: "0.92.2"

      - name: 🛠️ Build
        run: hugo --minify --verbose --debug
        working-directory: ./website

      - name: 🚀 Deploy
        uses: SamKirkland/FTP-Deploy-Action@a9644610a0efe63542b1887c9317ce8628f56521 # ⚠️ hash for release 4.2.0
        with:
          local-dir: ./website/public/
          server-dir: /maui.graphics/public_html/
          protocol: ftps
          server: maui.graphics
          username: ${{ secrets.FTP_USERNAME }}
          password: ${{ secrets.FTP_PASSWORD }}
          log-level: minimal

      - name: 🧹 Clear Cache
        run: curl --user deploy:${{ secrets.CACHE_PASSWORD }} https://maui.graphics/admin/clear-cache.php
```

### Clear Cached Pages on SiteGround

#### .htaccess
```
SetEnvIf Authorization .+ HTTP_AUTHORIZATION=$0
```

#### clear-cache.php
```php
<?php

// This page won't work if it's cached
header("Cache-Control: no-cache");

// NOTE: see .htaccess to enable PHP_AUTH_PW
if (empty($_SERVER['PHP_AUTH_PW'])) {
    echo "ERROR: Password Required";
} else if ($_SERVER['PHP_AUTH_PW'] == 'mYsEcReTpAsSwOrD') {
	exec('curl -s -k -X PURGE -L https://maui.graphics/*');
	echo("Purge: Successful");
} else {
    echo "ERROR: Incorrect Password";
}
```
