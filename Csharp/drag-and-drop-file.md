# Drag and Drop a File onto a Windows Forms Application

```cs
void SetupDragDrop()
{
    AllowDrop = true;

    DragEnter += (o, e) =>
    {
        if (e.Data is null) return;
        if (e.Data.GetDataPresent(DataFormats.FileDrop))
            e.Effect = DragDropEffects.Copy;
    };

    DragDrop += (o, e) =>
    {
        if (e.Data is null) return;
        string[]? paths = e.Data.GetData(DataFormats.FileDrop) as string[];
        if (paths is null) return;

        foreach (string path in paths)
        {
            System.Diagnostics.Debug.WriteLine(path);
        }
    };
}
```
