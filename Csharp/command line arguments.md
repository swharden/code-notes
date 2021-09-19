# Command Line Arguments

* Use an Argument Parsing Package: [command-line-parser.md](command-line-parser.md)

```cs
static void Main(string[] args)
{    
    // simulate command line arguments while debugging
    if (Debugger.IsAttached)
        args = new string[] { "debugArg1", "debugArg2", "debugArg3" };
}
```
