# Threading with Windows Forms

## Invoke() Actions on Controls for Thread Safety

Directly manipulating controls from any thread other than the main UI thread puts you at risk for _System.InvalidOperationException: 'Cross-thread operation not valid: Control 'label3' accessed from a thread other than the thread it was created on.'_

```cs
// not thread safe
label3.Text = $"new info";
```

Instead, call a control's `Invoke()` method and pass a `delegate`

```cs
// thread safe
label3.Invoke(() =>
{
    label3.Text = "new info";
});
```

## Run a Slow Job & Update

```cs
public partial class Form3 : Form
{
    SlowJob Job = new();

    public Form3()
    {
        InitializeComponent();
        Job.ProgressChanged += OnProgressChanged;
    }

    private void OnProgressChanged(object? sendor, EventArgs e)
    {
        lblStatus.Invoke(() => lblStatus.Text = Job.Status);
    }

    private void btnStart_Click(object sender, EventArgs e)
    {
        Job.StartAsync();
    }

    private void btnStop_Click(object sender, EventArgs e)
    {
        Job.Cancel();
    }
}
```

## Sample Slow Job
```cs
internal class SlowJob
{
    public EventHandler? ProgressChanged = null;

    public string Status = "not started yet";

    private bool Continue = false;

    public async void StartAsync(int count = 100)
    {
        await Task.Factory.StartNew(() => { Start(count); });
    }

    public void Start(int count = 100)
    {
        Continue = true;
        for (int i = 0; i < count; i++)
        {
            if (!Continue)
            {
                Status = "cancelled";
                ProgressChanged?.Invoke(this, EventArgs.Empty);
                return;
            }

            Status = $"processing {i} of {count}";
            ProgressChanged?.Invoke(this, EventArgs.Empty);
            Thread.Sleep(10);
        }

        Status = "complete";
        ProgressChanged?.Invoke(this, EventArgs.Empty);
    }

    public void Cancel()
    {
        Continue = false;
    }
}
```

## BackgroundWorker

There is a `BackgroundWorker` which has logic for running, cancellation, error detection, and reporting progress. This may be useful if the long-running task can be called to move forward in little chunks.

https://docs.microsoft.com/en-us/dotnet/api/system.componentmodel.backgroundworker
