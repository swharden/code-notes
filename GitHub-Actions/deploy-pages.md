# Use GitHub Actions to Deploy a Site to GitHub Pages

```yaml
name: GitHub Pages

on:
  workflow_dispatch: # only run manually

permissions:
  contents: read
  pages: write
  id-token: write

concurrency:
  group: "pages"
  cancel-in-progress: true

jobs:
  deploy:
    runs-on: ubuntu-latest
    environment:
      name: Deploy
      url: ${{ steps.deployment.outputs.page_url }}
    steps:
      - name: Checkout
        uses: actions/checkout@v3
      - name: Setup Pages
        uses: actions/configure-pages@v2
      - name: Upload artifact
        uses: actions/upload-pages-artifact@v1
        with:
          path: './www'
      - name: Deploy to GitHub Pages
        id: deployment
        uses: actions/deploy-pages@v1
```
