## Right-click Menu

```c#
void ShowCopyMenu()
{
    ContextMenuStrip cm = new();
    ToolStripItem watchedPathItem = cm.Items.Add("Watched Path");
    ToolStripItem displayedImagePathItem = cm.Items.Add("Displayed Image File Path");
    ToolStripItem displayedImageFolderPathItem = cm.Items.Add("Displayed Image Folder Path");
    ToolStripItem displayedImageDataItem = cm.Items.Add("Displayed Image Data");

    cm.ItemClicked += (s, e) =>
    {
        if (e.ClickedItem is null)
            return;

        if (e.ClickedItem == watchedPathItem)
        {

        }
        else if (e.ClickedItem == displayedImagePathItem)
        {

        }
        else if (e.ClickedItem == displayedImageFolderPathItem)
        {

        }
        else if (e.ClickedItem == displayedImageDataItem)
        {

        }
    };

    cm.Show(Cursor.Position);
}
```
