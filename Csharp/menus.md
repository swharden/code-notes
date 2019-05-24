# Menus

## Right-click Menu with `ContextMenuStrip`
```c#
private ContextMenuStrip cmRightClickMenu;

private void RightClickMenuSetup()
{
    cmRightClickMenu = new ContextMenuStrip();
    cmRightClickMenu.Items.Add("Save Image");
    cmRightClickMenu.Items.Add("Auto-Axis");
    cmRightClickMenu.Items.Add("Help");
    cmRightClickMenu.Items.Add("About ScottPlot");
}

private void RightClickMenu()
{
    cmRightClickMenu.Show(pbPlot, PointToClient(Cursor.Position));
    cmRightClickMenu.ItemClicked += new ToolStripItemClickedEventHandler(RightClickMenu_SaveImage);
}

private void RightClickMenuItemClicked(object sender, ToolStripItemClickedEventArgs e)
{
    ToolStripItem item = e.ClickedItem;
    System.Console.WriteLine(item);
}
```
