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
        env:
          HUGO_VERSION: 0.92.2
        run: |
          mkdir ~/hugo
          cd ~/hugo
          curl -L "https://github.com/gohugoio/hugo/releases/download/v${HUGO_VERSION}/hugo_${HUGO_VERSION}_Linux-64bit.tar.gz" --output hugo.tar.gz
          tar -xvzf hugo.tar.gz
          sudo mv hugo /usr/local/bin

      - name: 🛠️ Build
        run: hugo --source website --destination output --cleanDestinationDir --baseURL https://swharden.com/csdv/ --debug --minify

      - name: 🔑 Install SSH Key
        run: |
          install -m 600 -D /dev/null ~/.ssh/id_rsa
          echo "${{ secrets.REMOTE_SSH_KEY }}" > ~/.ssh/id_rsa
          echo "${{ secrets.KNOWN_HOSTS }}" > ~/.ssh/known_hosts

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
  -e 'ssh -p 18765 -i 2022-03-12-id_rsa_no-passphrase.private' \
  'website/output/' \
  u186-exgapiqqc7gg@swharden.com:/home/customer/www/swharden.com/public_html/csdv;
```
