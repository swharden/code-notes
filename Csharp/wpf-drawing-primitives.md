# Drawing Primitives with WPF

## Pie

![image](https://user-images.githubusercontent.com/4165489/202911136-d31e9ca9-250d-4102-b956-ca79b610f3a2.png)

```cs
double width = ChartCanvas.ActualWidth;
double height = ChartCanvas.ActualHeight;
double r = Math.Min(width, height) / 2 * .8;
Point center = new(width / 2, height / 2);
Size size = new(width, height);

(string[] names, Color[] colors) = GetEnabledItems();
double[] values = Enumerable.Range(0, names.Length).Select(x => Random.Shared.NextDouble()).ToArray();
double valueSum = values.Sum();
double[] angles = values.Select(x => x / valueSum * 360).ToArray();
double[] radians = values.Select(x => x / valueSum * 2 * Math.PI).ToArray();

ChartCanvas.Children.Clear();

double startRadians = 0;
for (int i = 0; i < names.Length; i++)
{
    System.Diagnostics.Debug.WriteLine(colors[i]);

    Point arcStart = new(
        x: center.X + r * Math.Cos(startRadians),
        y: center.Y + r * Math.Sin(startRadians));

    Point arcEnd = new(
        x: center.X + r * Math.Cos(startRadians + radians[i]),
        y: center.Y + r * Math.Sin(startRadians + radians[i]));

    startRadians += radians[i];

    Size outerArcSize = new(r, r);
    Size innerArcSize = new(r / 2, r / 2);

    StreamGeometry sg = new();
    using StreamGeometryContext context = sg.Open();
    context.BeginFigure(center, true, true);
    context.LineTo(arcStart, true, true);
    context.ArcTo(arcEnd, outerArcSize, 0, angles[i] > 180, SweepDirection.Clockwise, true, true);
    context.LineTo(center, true, true);

    System.Windows.Shapes.Path myPath = new()
    {
        Data = sg,
        Stroke = Brushes.Black,
        Fill = new SolidColorBrush(colors[i]),
        StrokeThickness = 1,
        HorizontalAlignment = HorizontalAlignment.Left,
        VerticalAlignment = VerticalAlignment.Center,
    };

    ChartCanvas.Children.Add(myPath);
}
```

## ArcSegment

```cs
ArcSegment arcSeg = new()
{
    Point = center,
    Size = size,
    IsLargeArc = angles[i] > 180,
    SweepDirection = SweepDirection.Clockwise,
    RotationAngle = angles[i],
};

startAngle += angles[i];

PathSegmentCollection myPathSegmentCollection = new() { arcSeg };
PathFigure pthFigure = new()
{
    StartPoint = new Point(0, 100),
    Segments = myPathSegmentCollection,
};
PathFigureCollection pthFigureCollection = new() { pthFigure };
PathGeometry pthGeometry = new() { Figures = pthFigureCollection };
Path arcPath = new()
{
    Stroke = new SolidColorBrush(Colors.Black),
    StrokeThickness = 1,
    Data = pthGeometry,
    Fill = new SolidColorBrush(Colors.Yellow)
};

ChartCanvas.Children.Add(arcPath);
```

## Old

I tried drawing lines, polygons, and polyliens using WPF just to see what the performance was. It's awful. I get about 1Hz update speed when drawing 1K lines in a fullscreen canvas.

```XAML
<Window x:Class="WpfLineTest.MainWindow"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
        xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
        xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
        xmlns:local="clr-namespace:WpfLineTest"
        mc:Ignorable="d"
        Title="MainWindow" Height="341.912" Width="515.618">
    <Grid>
        <CheckBox Name="cbContinuous" Content="Continuous" Canvas.Left="427" Canvas.Top="38" HorizontalAlignment="Right" Margin="0,35,0,0" Width="84" Checked="CbContinuous_Checked"/>
        <Button Content="Redraw" HorizontalAlignment="Right" Margin="0,10,10,0" VerticalAlignment="Top" Width="74" Click="Button_Click"/>
        <Canvas Name="myCanvas">
        </Canvas>
    </Grid>
</Window>
```

```cs
public partial class MainWindow : Window
{
    Random rand = new Random();
    DispatcherTimer dispatcherTimer;

    public MainWindow()
    {
        InitializeComponent();

        dispatcherTimer = new DispatcherTimer();
        dispatcherTimer.Tick += DrawRandomLines;
        dispatcherTimer.Interval = new TimeSpan(0, 0, 0, 0, 100);
    }

    private void Button_Click(object sender, RoutedEventArgs e)
    {
        DrawRandomLines(null, null);
    }

    private Line GetRandomLine()
    {
        Line line = new Line();
        line.StrokeThickness = 1;
        line.Stroke = Brushes.Black;
        line.X1 = rand.NextDouble() * myCanvas.ActualWidth;
        line.X2 = rand.NextDouble() * myCanvas.ActualWidth;
        line.Y1 = rand.NextDouble() * myCanvas.ActualHeight;
        line.Y2 = rand.NextDouble() * myCanvas.ActualHeight;
        return line;
    }

    private Polyline GetRandomPolyline(int points)
    {
        Polyline poly = new Polyline();
        poly.StrokeThickness = 1;
        poly.Stroke = Brushes.Black;
        poly.Points = new PointCollection();
        for (int i=0; i<points; i++)
        {
            double x = rand.NextDouble() * myCanvas.ActualWidth;
            double y = rand.NextDouble() * myCanvas.ActualHeight;
            poly.Points.Add(new Point(x, y));
        }
        return poly;
    }

    private void DrawRandomLines(object sender, EventArgs e)
    {
        myCanvas.Children.Clear();
        int lineCount = 1000;


        System.Diagnostics.Stopwatch stopwatch = System.Diagnostics.Stopwatch.StartNew();

        // demonstrate how to add random LINES
        //for (int i = 0; i < 1000; i++)
            //myCanvas.Children.Add(GetRandomLine());

        // demonstrate how to add random POLYGON
        myCanvas.Children.Add(GetRandomPolyline(lineCount));

        double elapsedMsec = stopwatch.ElapsedTicks * 1000.0 / System.Diagnostics.Stopwatch.Frequency;
        double rateHz = 1000.0 / elapsedMsec;

        myCanvas.UpdateLayout();

        TextBlock tbStatus = new TextBlock();
        tbStatus.Text = string.Format("rendered {0} lines in {1:0.00} ms ({2:0.00} Hz)", lineCount, elapsedMsec, rateHz);
        tbStatus.Foreground = Brushes.Blue;
        tbStatus.Background = Brushes.White;
        myCanvas.Children.Add(tbStatus);
    }

    private void CbContinuous_Checked(object sender, RoutedEventArgs e)
    {
        if (cbContinuous.IsChecked == true)
            dispatcherTimer.Start();
        else
            dispatcherTimer.Stop();
    }
}
```
