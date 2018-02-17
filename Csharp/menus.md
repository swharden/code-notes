# Menus

## Right-click Menu with `ContextMenuStrip`
```C#
ContextMenuStrip cm = new ContextMenuStrip();
cm.Items.Add("Save Image");
cm.Items.Add("Auto-Axis");
cm.Items.Add("Help");
cm.Items.Add("About ScottPlot");
cm.Show(pictureBox1, e.Location);
cm.ItemClicked += new ToolStripItemClickedEventHandler(RightClickMenuItemSelected);
```

```C#
private void RightClickMenuItemSelected(object sender, ToolStripItemClickedEventArgs e)
{
    ToolStripItem item = e.ClickedItem;
    System.Console.WriteLine(item);
}
```

## Right-click Menu with `ContextMenu`
```C#
ContextMenu marker_right_click_menu = new ContextMenu();
marker_right_click_menu.MenuItems.Add(new MenuItem("item one", new EventHandler(Clicked1)));
marker_right_click_menu.MenuItems.Add(new MenuItem("item two", new EventHandler(Clicked2)));
marker_right_click_menu.Show(panel_dataView, mouse_position);
```

```
private void Clicked1(object sender, EventArgs e)
{
    System.Console.WriteLine("clicked number 1");
}

private void Clicked2(object sender, EventArgs e)
{
    System.Console.WriteLine("clicked number 2");
}
```
