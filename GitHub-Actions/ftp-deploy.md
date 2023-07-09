# Deploy using FTP from GitHub Actions

## Rsync is better than FTP!

Rsync is much better and faster at deploying files to remote locations. It's smart enough to transfer only the files that are different.

https://swharden.com/blog/2022-03-20-github-actions-hugo/

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
        run: lftp -e "set ftp:ssl-allow no; put -O /destination/ ./source.txt" ${{ secrets.FTP_HOSTNAME }}
      - name: 📁 Upload Folder
        run: lftp -e "set ftp:ssl-allow no; mirror --parallel=100 -R ./source/ /destination/" ${{ secrets.FTP_HOSTNAME }}
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
