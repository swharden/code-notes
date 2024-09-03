# Fast Moving Window Smoothing

### Forward Smoothing (lagging)

```cs
static double[] Smooth(double[] ys, int pointCount = 5)
{
    double[] smooth = new double[ys.Length];

    double runningSum = 0;
    int pointsInSum = 0;
    for (int i = 0; i < smooth.Length; i++)
    {
        runningSum += ys[i];

        if (pointsInSum < pointCount)
        {
            pointsInSum++;
            smooth[i] += runningSum / pointsInSum;
            continue;
        }

        runningSum -= ys[i - pointCount];
        smooth[i] += runningSum / pointCount;
    }

    return smooth;
}
```

![image](https://github.com/user-attachments/assets/0b6903dd-2d48-4b4f-b5c0-dce17b657973)

### Bidirectional Smoothing

```cs
static double[] Smooth(double[] ys, int pointCount = 5)
{
    double[] smooth = new double[ys.Length];

    // smooth from left to right
    double runningSum = 0;
    int pointsInSum = 0;
    for (int i = 0; i < smooth.Length; i++)
    {
        runningSum += ys[i];

        if (pointsInSum < pointCount)
        {
            pointsInSum++;
            smooth[i] += runningSum / pointsInSum;
            continue;
        }

        runningSum -= ys[i - pointCount];
        smooth[i] += runningSum / pointCount;
    }

    // smooth from right to left
    runningSum = 0;
    pointsInSum = 0;
    for (int i = smooth.Length - 1; i >= 0; i--)
    {
        runningSum += ys[i];

        if (pointsInSum < pointCount)
        {
            pointsInSum++;
            smooth[i] += runningSum / pointsInSum;
            continue;
        }

        runningSum -= ys[i + pointCount];
        smooth[i] += runningSum / pointCount;
    }

    // average the two directions
    for (int i = 0; i < smooth.Length; i++)
    {
        smooth[i] /= 2;
    }

    return smooth;
}
```

![image](https://github.com/user-attachments/assets/33e501af-57a0-49ce-b10b-cb6615f8fc83)

### Plot Setup
```cs
double[] xs = ScottPlot.Generate.Consecutive(50);
double[] ys = ScottPlot.Generate.RandomWalk(xs.Length);

ScottPlot.Plot plot = new();
plot.Add.ScatterPoints(xs, ys);
var line = plot.Add.ScatterLine(xs, Smooth(ys));
line.LineWidth = 2;
plot.SavePng("plot.png", 400, 300).LaunchInBrowser();
```
