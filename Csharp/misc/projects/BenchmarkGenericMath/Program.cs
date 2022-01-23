using System;
using System.Security.Cryptography;
using System.Text;
using BenchmarkDotNet.Analysers;
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;

namespace BenchmarkGenericMath
{
    [SimpleJob(launchCount: 1, warmupCount: 1, targetCount: 2, invocationCount: 100, id: "simple job")]
    public class Benchmarker
    {
        const int POINT_COUNT = 10_000;
        float[] Values = Enumerable.Range(0, POINT_COUNT).Select(x => 1f).ToArray();

        [Benchmark]
        public double HardType()
        {
            return MathOps.SumHardType(Values);
        }

        [Benchmark]
        public double ToDouble()
        {
            return MathOps.SumToDouble(Values);
        }
    }

    public class Program
    {
        public static void Main(string[] args)
        {
            var summary = BenchmarkRunner.Run<Benchmarker>();
        }
    }

    public static class MathOps
    {
        public static double SumHardType(float[] values)
        {
            double sum = 0;
            for (int i = 0; i < values.Length; i++)
                sum += values[i];
            return sum;
        }

        public static double SumToDouble<T>(T[] values)
        {
            double sum = 0;
            for (int i = 0; i < values.Length; i++)
                sum += Convert.ToDouble(values[i]);
            return sum;
        }
    }
}