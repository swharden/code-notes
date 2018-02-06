# Menus

## Create a right-click menu dynamically
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
