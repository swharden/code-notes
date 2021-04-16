# Parallel Programming

## Parallel.ForEach

```cs
Parallel.ForEach(myList, item =>
{
    Console.WriteLine(item);
});
```

```cs
// define the number of threads
Parallel.ForEach(
    source: myList,
    parallelOptions: new ParallelOptions { MaxDegreeOfParallelism = 3 },
    body: item =>
{
    Console.WriteLine(item);
});
```
