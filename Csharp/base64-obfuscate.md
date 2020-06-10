# Obfuscate text in C#

Converting it to base64 does the trick, and removing the `=` hides it's a base64 string (which pads with `=` to achieve length multiples of 4).

```cs
private string Obfuscate(string message)
{
    return Convert.ToBase64String(Encoding.UTF8.GetBytes(message)).Trim('=');
}

private string DeObfuscate(string obfuscated)
{
    while (obfuscated.Length % 4 != 0)
        obfuscated += "=";
    return Encoding.UTF8.GetString(Convert.FromBase64String(obfuscated));
}
```

```cs
Console.WriteLine(original); // foxtrot123
Console.WriteLine(obfuscated); // Zm94dHJvdDEyMw
Console.WriteLine(decoded); // foxtrot123
```

You can get clever and play with the order of the characters, invert capitalization, or even perform the base64 conversion multiple times doing different modifications each time.
