/*
 * RESULTS:

    Generating 10,000,000 random numbers...

    Testing SumDoubleArray 100 times...
    Mean of 10,224.428 µs per sum

    Testing SumGenericToDouble 100 times...
    Mean of 9,943.770 µs per sum

    Testing SumGenericMath 100 times...
    Mean of 9,894.799 µs per sum

*/

namespace BenchmarkGenericMath;

public static class Program
{
    const int POINT_COUNT = 10_000_000;
    const int REPS_PER_FUNCTION = 100;
    readonly static Random Rand = new(0);

    public static void Main()
    {
        Console.WriteLine($"Generating {POINT_COUNT:N0} random numbers...");
        double[] values = Enumerable.Range(0, POINT_COUNT).Select(x => Rand.NextDouble()).ToArray();
        System.Diagnostics.Stopwatch sw = new();

        Func<double[], double>[] testFunctions = { SumDoubleArray, SumGenericToDouble, SumGenericMath };

        foreach (var func in testFunctions)
        {
            Console.WriteLine();
            Console.WriteLine($"Testing {func.Method.Name} {REPS_PER_FUNCTION:N0} times...");
            sw.Restart();
            for (int i = 0; i < REPS_PER_FUNCTION; i++)
                func(values);
            sw.Stop();
            Console.WriteLine($"Mean of {sw.Elapsed.TotalMilliseconds / REPS_PER_FUNCTION * 1000:N3} µs per sum");
        }
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