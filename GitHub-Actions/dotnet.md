# Building and Testing .NET Projects in GitHub Actions

## Basic Workflow

```yaml
name: CI

on:
  workflow_dispatch:
  push:
    branches:
      - main
  pull_request:
    types: [opened, synchronize, reopened]

jobs:
  test:
    name: Build
    runs-on: windows-latest
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v2
      - name: ✨ Setup .NET 6
        uses: actions/setup-dotnet@v1
        with:
          dotnet-version: 6.0.x
      - name: 🚚 Restore
        run: dotnet restore src
      - name: 🛠️ Build
        run: dotnet build src --no-restore
      - name: 🧪 Test
        run: dotnet test src --no-build
```

## Multiple Operating Systems

* Use a matrix strategy

```yaml
name: Multi-Platform Tests

on:
  workflow_dispatch:
  push:
    paths:
      - "src/**"
  pull_request:
    types: [opened, synchronize, reopened]

env:
  TEST_PROJECT_FOLDER: "src/MyTestProject"

jobs:
  test:
    strategy:
      fail-fast: false
      matrix:
        include:
          - os: ubuntu-latest
            osName: Linux
          - os: windows-latest
            osName: Windows
          - os: macos-latest
            osName: MacOS
    runs-on: ${{ matrix.os }}
    name: 🧪 Test on ${{ matrix.osName }}
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v2
      - name: ✨ Setup .NET 6.0
        uses: actions/setup-dotnet@v1
        with:
          dotnet-version: "6.0.x"
      - name: 🚚 Restore
        run: dotnet restore ${{ env.TEST_PROJECT_FOLDER }}
      - name: 🛠️ Build
        run: dotnet build ${{ env.TEST_PROJECT_FOLDER }} --configuration Release --no-restore
      - name: 🧪 Test
        run: dotnet test ${{ env.TEST_PROJECT_FOLDER }} --configuration Release --no-restore --verbosity normal
```

## Mixed Framework/Core Projects

* Be sure to setup both `MSBuild` and `dotnet`

```yaml
  build:
    runs-on: windows-latest
    name: 🛠️ Build Entire Solution
    steps:
      - name: 🛒 Checkout
        uses: actions/checkout@v2
      - name: 🐢 Set up MSBuild
        uses: microsoft/setup-msbuild@v1.1
      - name: ✨ Set up .NET 6.0
        uses: actions/setup-dotnet@v1
        with:
          dotnet-version: "6.0.x"
          include-prerelease: true
      - name: 🚚 Restore
        working-directory: src
        run: dotnet restore
      - name: 🐌 MSBuild
        working-directory: src
        run: msbuild -property:Configuration=Release -verbosity:minimal
```
