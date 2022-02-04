namespace BenchmarkGenericMath;

public static class Program
{
    public static void Main()
    {
        const int POINT_COUNT = 100_000;
        Random rand = new(0);
        double[] values = Enumerable.Range(0, POINT_COUNT).Select(x => rand.NextDouble()).ToArray();

        Console.WriteLine(SumDoubleArray(values));
        Console.WriteLine(SumGenericToDouble(values));
        Console.WriteLine(SumGenericMath(values));
    }

    public static double SumDoubleArray(double[] values)
    {
        double sum = 0;

        for (int i = 0; i < values.Length; i++)
            sum += values[i];

        return sum;
    }

    public static double SumGenericToDouble<T>(T[] values)
    {
        double sum = 0;

        for (int i = 0; i < values.Length; i++)
            sum += Convert.ToDouble(values[i]);

        return sum;
    }

    public static double SumGenericMath<T>(T[] values) where T : INumber<T>
    {
        T sum = T.Zero;

        for (int i = 0; i < values.Length; i++)
            sum += values[i];

        return Convert.ToDouble(sum);
    }
}