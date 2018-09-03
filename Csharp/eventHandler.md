# Event Handler

```cs
public event EventHandler IconSelected;
protected virtual void OnIconSelected(EventArgs e)
{
    var handler = IconSelected;
    if (handler != null)
        handler(this, e);
}

public string selectedIcon;
private void listView1_SelectedIndexChanged(object sender, EventArgs e)
{
    OnIconSelected(EventArgs.Empty);
}
```
