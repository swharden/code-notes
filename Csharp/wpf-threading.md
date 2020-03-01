# Threading in WPF

## BackgroundWorder
```cs

private void GenerateClicked(object sender, RoutedEventArgs e)
{
	BackgroundWorker worker = new BackgroundWorker();
	worker.WorkerReportsProgress = true;
	worker.DoWork += Worker_DoWork;
	worker.ProgressChanged += Worker_ProgressChanged;

	GenerateButton.IsEnabled = false;
	worker.RunWorkerAsync();
	GenerateButton.IsEnabled = true;
}

private void Worker_DoWork(object sender, DoWorkEventArgs e)
{
	for (int i = 0; i < demoPlotNames.Length; i++)
	{
		string name = demoPlotNames[i].Replace("ScottPlot.Demo.", "");
		(sender as BackgroundWorker).ReportProgress(i * 100 / demoPlotNames.Length, name);

		IPlotDemo plotDemo = Reflection.GetPlot(demoPlotNames[i]);
		var plt = new Plot(600, 400);
		plotDemo.Render(plt);
		Debug.WriteLine(plotDemo);
	}

	(sender as BackgroundWorker).ReportProgress(100, $"Completed generating {demoPlotNames.Length} plots");
}

private void Worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
{
	ProgressBar1.Value = e.ProgressPercentage;
	ProgressLabel.Content = e.UserState;
	Debug.WriteLine(e.UserState);
} 
```
