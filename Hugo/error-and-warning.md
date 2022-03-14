# Error and Warning Messages in Hugo

A template can produce a warning or crash the build on certain conditions

### Warning

```
{{ if not .Title }}
{{ warnf "Missing title: %q" .Path }}
{{ end }}
```

```
Re-run Hugo with the flag --panicOnWarning to get a better error message.
WARN 2022/03/14 08:38:03 Missing title: "system.drawing\\animate-starfield\\index.md"
WARN 2022/03/14 08:38:03 Missing title: "system.drawing\\animate-winforms\\index.md"
WARN 2022/03/14 08:38:03 Missing title: "system.drawing\\animate-wpf\\index.md"
```

### Error

```
{{ if not .Title }}
{{ errorf "Missing title: %q" .Path }}
{{ end }}
```

![image](https://user-images.githubusercontent.com/4165489/158173671-78861fbb-9f66-4ebb-8d0b-9cea3f063229.png)
