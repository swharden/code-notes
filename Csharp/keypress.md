# Capturing Keypresses
* ***must set Form1 keyPreview to TRUE***
* bind to Form1 events, not individual control events

```cs
private void Form1_KeyDown(object sender, KeyEventArgs e)
{
    System.Console.WriteLine("KEYPRESS");
    switch (e.KeyCode)
    {
        case Keys.Down:
        case Keys.Right:
            LoadAdjacentImage();
            break;
        case Keys.Up:
        case Keys.Left:
            LoadAdjacentImage(true);
            break;
    }
}
```

## Keypress capture inside a user control
```cs
protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
{
    if (busy)
        return true;
    if ((keyData == Keys.Right) || (keyData == Keys.Up))
    {
        btnSweepNext_Click(null, null);
        return true;
    }
    else if ((keyData == Keys.Left) || (keyData == Keys.Down))
    {
        btnSweepPrev_Click(null, null);
        return true;
    }
    else
    {
        return base.ProcessCmdKey(ref msg, keyData);
    }
}
```
