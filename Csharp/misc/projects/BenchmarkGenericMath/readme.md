This project benchmarks different ways to add numbers.

## Latest Test

```
Generating 10,000,000 random numbers...

Testing SumDoubleArray 100 times...
Mean of 9,966.125 µs per sum

Testing SumGenericToDouble 100 times...
Mean of 31,254.693 µs per sum

Testing SumGenericMath 100 times...
Mean of 9,913.450 µs per sum
```

**CONCLUSION:** Generic math is fast just like working with typed arrays.

I can't use a test package because that requires a special build for `EnablePreviewFeatures` in my csproj

## Older Notes

Generic math isn't available yet in .NET 6, but when it releases I'll add it.

```
|   Method |      Mean | Error |    StdDev |
|--------- |----------:|------:|----------:|
| HardType |  8.754 us |    NA | 0.0148 us |
| ToDouble | 27.337 us |    NA | 1.6935 us |
```

```cs
public static double SumHardType(float[] values)
{
	double sum = 0;
	for (int i = 0; i < values.Length; i++)
		sum += values[i];
	return sum;
}
```

```cs
public static double SumToDouble<T>(T[] values)
{
	double sum = 0;
	for (int i = 0; i < values.Length; i++)
		sum += Convert.ToDouble(values[i]);
	return sum;
}
```

## Conclusions

* Having to call `Convert.ToDouble()` makes the code >3x slower