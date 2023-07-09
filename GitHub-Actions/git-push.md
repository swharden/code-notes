# How to `git push` in a GitHub Action

Note: The `GH_TOKEN` is a personal access token (generated from your account settings page) that has repo-level access

```yaml
jobs:
  deploy:
    name: Update Changelog
    runs-on: ubuntu-latest
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v3

      # do the things that modify the source files...

      - name: ✅ Commit Changes
        run: |
          git config --global user.name 'Scott W Harden (via GitHub Actions)'
          git config --global user.email 'swharden@gmail.com'
          git commit -am "Changelog: Automated Update"
          git push
```
