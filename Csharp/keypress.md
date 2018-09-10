# Capturing Keypresses
bind to Form1 events, not individual control events

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
