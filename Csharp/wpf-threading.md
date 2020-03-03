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
    // do NOT access GUI components from this thread

    for (int i = 0; i < 100; i++)
    {
	(sender as BackgroundWorker).ReportProgress(i);
    }
}

private void Worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
{
    // you may access GUI components from this thread
    //ProgressBar1.Value = e.ProgressPercentage;
    //ProgressLabel.Content = e.UserState;
}
```
