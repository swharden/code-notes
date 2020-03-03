# Threading in WPF

## BackgroundWorder
```cs

private void GenerateClicked(object sender, RoutedEventArgs e)
{
    BackgroundWorker worker = new BackgroundWorker();
    worker.WorkerReportsProgress = true;
    worker.DoWork += Worker_DoWork;
    worker.ProgressChanged += Worker_ProgressChanged;
    worker.RunWorkerCompleted += Worker_RunWorkerCompleted; ;
    worker.RunWorkerAsync();
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
}

private void Worker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
{
    // you may access GUI components from this thread
}
```
