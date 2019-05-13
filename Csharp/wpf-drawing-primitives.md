# Drawing Primitives with WPF
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
