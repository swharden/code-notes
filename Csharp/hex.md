# Hexademical Conversion with C#

```cs
static void Main(string[] args)
{
    uint[] numbers = { 0, 9, 99, 999, 999999, 999999999 };
    foreach (uint number in numbers)
    {
        Console.WriteLine("");
        Console.WriteLine($"string: [{number:x}]");
        Console.WriteLine($"manual: [{IntToHex(number)}]");
    }
}

static string IntToHex(uint x, bool zeroPad = false)
{
    byte[] chars = new byte[8];

    for (int i = 0; i < 8; i++)
    {
        byte digit = (byte)(x % 16);
        x /= 16;

        if (digit <= 9)
            chars[7 - i] = (byte)(digit + '0');
        else
            chars[7 - i] = (byte)(digit - 10 + 'a');

        if (x == 0 && !zeroPad)
            break;
    }

    return System.Text.Encoding.ASCII.GetString(chars);
}
```
