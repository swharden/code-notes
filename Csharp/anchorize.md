# Safe filename characters

```cs
static string Anchorize(string text)
{
    string allowedSpecial = "_";
    char replacement = '-';
    StringBuilder sb = new();
    foreach (char c in text.Trim().ToLowerInvariant())
    {
        if (c == ' ')
        {
            sb.Append(replacement);
            continue;
        }

        bool isAlpha = c >= 'a' && c <= 'z';
        bool isNumeric = c >= '0' && c <= '9';
        bool allowed = isAlpha || isNumeric || allowedSpecial.Contains(c);
        if (allowed)
            sb.Append(c);
    }
    return sb.ToString();
}
```
