To pause a C# console application after it ends but before it closes:

```cs
static void Main(string[] args)
{
    Console.WriteLine("EventMetricTest()");
    //EventMetricTest();

    Console.WriteLine("\npress ENTER to exit...");
    Console.ReadLine();
}

```
