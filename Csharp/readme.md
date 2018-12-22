### Keyboard Shortcuts

* format document: `CTRL+K`, `CTRL+D`
* format selection: `CTRL+K`, `CTRL+F`
* comment: `CTRL+K`, `CTRL+C`
* uncomment: `CTRL+K`, `CTRL+U`
* full screen: `ALT+SHIFT+ENTER`

### Inline `if` statements
```cs
comboChannel.Enabled = (channelCount > 1) ? true : false;
```

### String to integer

If you are sure it will parse:
```cs
int.Parse(string)
```

If you are not sure it will parse:
```cs
int i;
bool success = int.TryParse(string, out i);
```
