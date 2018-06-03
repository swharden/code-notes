# Command Line Arguments

```cs
static void Main(string[] args)
{
    for (var x = 0; x < args.Count(); x++)
    {
        switch (args[x].Trim().ToLower())
        {
            case "/h":
                doHelp = true;
                break;
        }
    }
}
```
