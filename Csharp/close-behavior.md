# Form Close Behavior
If you have a child form and you want clicking the "X" to hide it rather than closing the form (requiring it to be recreated from a new form object to show it again later), override the OnFormClosing method:
```cs
protected override void OnFormClosing(FormClosingEventArgs e)
{
    base.OnFormClosing(e);
    e.Cancel = true; // cancel the close event
    this.Visible = false;
}
```
