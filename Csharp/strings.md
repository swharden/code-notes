# Strings
### Strip non-ASCII characters from a string
```cs
Encoding.ASCII.GetString(Encoding.ASCII.GetBytes(s))
```

### Web-Safe URL string
```cs
/// <summary>
/// Return the input string modified to contain only numbers, lowercase letters, hyphens, and underscores.
/// </summary>
private string WebSafe(string text) =>
    new(text
        .ToLowerInvariant()
        .ToCharArray()
        .Select(c => char.IsLetterOrDigit(c) ? c : '-')
        .ToArray());
```

### Place variables in strings with `$` and `{}`

```C#
string message = "awesome";
int thoughts = 123;
System.Console.WriteLine($"Scott is {message} and has {Math.Pow(thoughts, 2)} thoughts");
```
OUTPUT: `Scott is awesome and has 15129 thoughts`

### Ignore `\` in strings with `@`
```C#
string path = @"C:\path\to\file.txt";
```

Note that `string path1 = "C:\path\to\file.txt"` won't even compile: _Unrecognized escape sequence_

### String Formatting of Numbers
* http://www.csharp-examples.net/string-format-double/
* http://www.daveoncsharp.com/2009/09/formatting-decimals-in-csharp/
* https://docs.microsoft.com/en-us/dotnet/standard/base-types/standard-numeric-format-strings

```c#
msg += string.Format("Axis render time: {0:0.000} ms\n", time_redraw_axis_ms);
```

```c#
// just two decimal places
String.Format("{0:0.00}", 123.4567);      // "123.46"
String.Format("{0:0.00}", 123.4);         // "123.40"
String.Format("{0:0.00}", 123.0);         // "123.00"
String.Format("{0:n}", 1234);             // 1,234.00
string.Format("{0:n0}", 9876);            // 9,876

// or this
i.ToString("0000"); - pad with zeros
i.ToString("D4"); - pad with zeros

// or double up
string.Format(String.Format("{0:0000000000.0000}", 123)); // 0000000123.0000
```

### String contains substring
```cs
if (s.contains("substr")) {/* stuff */}
```

### Integer to Binary string
```cs
lblBinaryByte1.Text = Convert.ToString((int)nudByte1.Value, 2).PadLeft(8, '0'); 
```
