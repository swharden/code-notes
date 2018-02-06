# Returning Multiple Values
_adapted from [this post](https://stackoverflow.com/questions/748062/how-can-i-return-multiple-values-from-a-function-in-c/30632338#30632338)_

## ref / out parameters

### using ref:
```c#
static void Main(string[] args)
{
    int a = 10;
    int b = 20;
    int add = 0;
    int multiply = 0;
    Add_Multiply(a, b, ref add, ref multiply);
    Console.WriteLine(add);
    Console.WriteLine(multiply);
}

private static void Add_Multiply(int a, int b, ref int add, ref int multiply)
{
    add = a + b;
    multiply = a * b;
}
```


### using out:

```c#
static void Main(string[] args)
{
    int a = 10;
    int b = 20;
    int add;
    int multiply;
    Add_Multiply(a, b, out add, out multiply);
    Console.WriteLine(add);
    Console.WriteLine(multiply);
}

private static void Add_Multiply(int a, int b, out int add, out int multiply)
{
    add = a + b;
    multiply = a * b;
}
```

## struct / class

### using struct:

```c#
struct Result
{
    public int add;
    public int multiply;
}
static void Main(string[] args)
{
    int a = 10;
    int b = 20;
    var result = Add_Multiply(a, b);
    Console.WriteLine(result.add);
    Console.WriteLine(result.multiply);
}

private static Result Add_Multiply(int a, int b)
{
    var result = new Result
    {
        add = a * b,
        multiply = a + b
    };
    return result;
}
```

### using class:

```c#
class Result
{
    public int add;
    public int multiply;
}
static void Main(string[] args)
{
    int a = 10;
    int b = 20;
    var result = Add_Multiply(a, b);
    Console.WriteLine(result.add);
    Console.WriteLine(result.multiply);
}

private static Result Add_Multiply(int a, int b)
{
    var result = new Result
    {
        add = a * b,
        multiply = a + b
    };
    return result;
}
```

## Tuple

### Tuple class

```c#
static void Main(string[] args)
{
    int a = 10;
    int b = 20;
    var result = Add_Multiply(a, b);
    Console.WriteLine(result.Item1);
    Console.WriteLine(result.Item2);
}

private static Tuple<int, int> Add_Multiply(int a, int b)
{
    var tuple = new Tuple<int, int>(a + b, a * b);
    return tuple;
}
```

### C# 7 Tuples
```c#
static void Main(string[] args)
{
    int a = 10;
    int b = 20;
    (int a_plus_b, int a_mult_b) = Add_Multiply(a, b);
    Console.WriteLine(a_plus_b);
    Console.WriteLine(a_mult_b);
}

private static (int a_plus_b, int a_mult_b) Add_Multiply(int a, int b)
{
    return(a + b, a * b);
}
```
