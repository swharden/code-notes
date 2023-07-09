# Trigger a GitHub Action Remotely

How to get one GitHub Actions workflow to trigger another workflow in a different repository.

## Sending Action

Note: The `GH_TOKEN` is a personal access token (generated from your account settings page) that has repo-level access

```yaml
name: Update Changelog Webpage

on:
  workflow_dispatch:
  push:
    branches:
      - main
    paths:
      - CHANGELOG.md

jobs:
  update:
    runs-on: ubuntu-latest
    name: Trigger Remote Workflow
    steps:
      - name: 🚀 Trigger Remote Workflow
        run: |
          curl -L \
            -X POST \
            -H "Accept: application/json" \
            -H "Authorization: Bearer ${{ secrets.GH_TOKEN }}" \
            -d "{\"ref\":\"main\"}" \
            https://api.github.com/repos/ScottPlot/ScottPlot.NET/actions/workflows/changelog.yaml/dispatches
```

## Receiving Action
```yaml
name: Changelog

on:
  workflow_dispatch:

jobs:
  deploy:
    name: Update Changelog
    runs-on: ubuntu-latest
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v3
    # do your things here
```

## Resources: 
* [Create a workflow dispatch event](https://docs.github.com/en/rest/actions/workflows?apiVersion=2022-11-28#create-a-workflow-dispatch-event)
