This project benchmarks different ways to add numbers.

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