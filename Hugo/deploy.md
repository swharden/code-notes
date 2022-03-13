# How to Deploy a Hugo Site

## rsync via GitHub Actions

```sh
ssh-keyscan -p 18765 swharden.com
```

```yaml
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v2

      - name: ✨ Setup Hugo
        uses: peaceiris/actions-hugo@c03b5dbed22245418539b65eb9a3b1d5fdd9a0a6 # v2.5.0
        with:
          hugo-version: "0.92.2"

      - name: 🛠️ Build
        run: hugo --source website --destination output --cleanDestinationDir --baseURL https://swharden.com/csdv/ --debug --minify

      - name: 🔑 Configure SSH
        uses: shimataro/ssh-key-action@3c9b0fc6f2d223b8450b02a0445f526350fc73e0 # v2.3.1
        with:
          key: ${{ secrets.REMOTE_SSH_KEY }}
          name: id_rsa
          known_hosts: ${{ secrets.KNOWN_HOSTS }}

      - name: 🚀 Deploy
        run: rsync --archive --delete --stats -e 'ssh -p 18765' 'website/output/' ${{ secrets.REMOTE_DEST }}
```

reference: https://www.yellowduck.be/posts/deploy-hugo-site-with-github-actions/

## rsync Locally

The advantage of `rsync` over other methods is that it's smart enough to only upload _modified_ files. This doesn't matter for small sites, but it's super helpful for large ones.

This command deploys a folder over SSH using `rsync` on Ubuntu through WSL. File permissions in the WSL environment are why this command must be run using `sudo`.

```bash
sudo rsync \
  --archive \
  --progress \
  --delete \
  --stats \
  -e 'ssh -p 18765 -i /mnt/c/Users/scott/Documents/important/certs/2022-03-12-id_rsa_no-passphrase.private' \
  '/mnt/c/Users/scott/Documents/GitHub/Csharp-Data-Visualization/website/output/' \
  u186-exgapiqqc7gg@swharden.com:/home/customer/www/swharden.com/public_html/csdv;
```
