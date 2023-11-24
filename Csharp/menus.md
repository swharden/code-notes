## Right-click Menu

```c#
void ShowCopyMenu()
{
    ContextMenuStrip cm = new();
    cm.Items.Add("Watched Path");
    cm.Items.Add("Displayed Image File Path");
    cm.Items.Add("Displayed Image Folder Path");
    cm.Items.Add("Displayed Image Data");

    cm.ItemClicked += (s, e) =>
    {
        if (e.ClickedItem is null)
            return;

        Text = e.ClickedItem.Text;
    };

    cm.Show(Cursor.Position);
}
```
