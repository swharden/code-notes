# 1D Array Math

An example demonstrating how to create something similar to a 1D ndarray in Python using indexing and operator overloading

```cs
public static class Program
{
    public static void Main()
    {
        double[] initialValues = { 2, 5, 9, 13 };
        MathArray1D data1 = new(initialValues);
        data1.Append(42);

        MathArray1D data2 = MathArray1D.Ones(data1.Length);
        MathArray1D data3 = data1 + data2;
        Console.WriteLine(data3);
    }
}
```

```cs
public class MathArray1D
{
    private readonly List<double> Values = new();
    public int Length => Values.Count;
    double this[int index]
    {
        get => Values[index];
        set => Values[index] = value;
    }

    public MathArray1D() { }

    public MathArray1D(double[] values) => Values.AddRange(values);

    override public string ToString()
    {
        if (Values.Count < 10)
        {
            string[] valueLabels = Values.Select(x => x.ToString()).ToArray();
            string valuesString = string.Join(", ", valueLabels);
            return $"[{valuesString}]";
        }
        else
        {
            string[] valueLabels1 = Values.Take(3).Select(x => x.ToString()).ToArray();
            string valuesString1 = string.Join(", ", valueLabels1);

            string[] valueLabels2 = Values.Skip(Values.Count - 3).Select(x => x.ToString()).ToArray();
            string valuesString2 = string.Join(", ", valueLabels2);

            return $"[{valuesString1}, ... {valuesString2}]";
        }
    }

    public void Append(double value) => Values.Add(value);

    public void Append(double[] values) => Values.AddRange(values);

    public void Clear() => Values.Clear();

    public static MathArray1D operator +(MathArray1D a, MathArray1D b)
    {
        ArgumentNullException.ThrowIfNull(a);
        ArgumentNullException.ThrowIfNull(b);
        if (a.Length != b.Length)
            throw new InvalidOperationException("this operation requires both math arrays to be the same size");

        double[] result = new double[a.Length];
        for (int i = 0; i < a.Length; i++)
            result[i] = a[i] + b[i];

        return new MathArray1D(result);
    }

    public static MathArray1D Fill(int count, double value)
    {
        double[] values = new double[count];
        for (int i = 0; i < count; i++)
            values[i] = value;
        return new MathArray1D(values);
    }

    public static MathArray1D Ones(int count) => Fill(count, 1);

    public static MathArray1D Zeros(int count) => Fill(count, 0);
}
```
