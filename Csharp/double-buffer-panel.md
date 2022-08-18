# Windows Forms: Double Buffering a Panel

Drawing on a Panel directly will cause flickering. Enable the Panel's double buffering to eliminate flickering, 
but since the field is private it must be accessed and changed using reflection.

```cs
// put this in your startup sequence
EnableDoubleBuffering(panel1);
panel1.Paint += Panel1_Paint;
```

```cs
private static void EnableDoubleBuffering(Panel target)
{
    BindingFlags flags = BindingFlags.SetProperty | BindingFlags.Instance | BindingFlags.NonPublic;
    typeof(Panel).InvokeMember("DoubleBuffered", flags, null, target, new object[] { true });
}
```

```cs
// graphics logic goes here
private void Panel1_Paint(object sender, PaintEventArgs e)
{
    Graphics gfx = e.Graphics;
    gfx.DrawLine(Pens.Red, 0, 0, 42, 69);
}
```
