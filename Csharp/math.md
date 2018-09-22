# Math

## Generate Gaussian-Weighted Random Numbers
```cs
public double[] RandomGaussianArray(int count)
{
    double[] data = new double[count];
    Random rand = new Random();
    for (int i = 0; i < count; i++)
    {
        double u1 = 1.0 - rand.NextDouble();
        double u2 = 1.0 - rand.NextDouble();
        double randStdNormal = Math.Sqrt(-2.0 * Math.Log(u1)) * Math.Sin(2.0 * Math.PI * u2);
        data[i] = randStdNormal;
    }
    return data;
}
```
