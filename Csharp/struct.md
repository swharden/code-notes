# Struct Examples in C#

```cs
class Program
{
    struct Simple
    {
        public int Position;
        public bool Exists;
        public double LastValue;
    };

    static void Main()
    {
        Simple s;
        s.Position = 1;
        s.Exists = false;
        s.LastValue = 5.5;

        Console.WriteLine(s.Position);
    }
}
```
