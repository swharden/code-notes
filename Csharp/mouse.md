# Interacting with the mouse

### Detect if the mouse is held down without requiring a sender
poll `System.Windows.Forms.Control.MouseButtons`

```C#
// example ignore a scrollbar until it is let go
private void vScrollBar1_Scroll(object sender, ScrollEventArgs e)
{
    if (System.Windows.Forms.Control.MouseButtons == MouseButtons.Left) return;
    ScollBarMoved();
}
```

### Prevent focus of buttons after they are clicked
When buttons are clicked, they gain a little blue border. They remain selected until something else is clicked. This looks very bad for some applications where it doesn't make sense (i.e., zoom in/out buttons). This has to do with `FocusVisualStyle` and [it's not easy to remove this behavior](https://stackoverflow.com/questions/1055670/deactivate-focusvisualstyle-globally).

My workaround is to bind the `MouseUp` event with a function which focuses on an invisible button. It's inelegant, but fast and functional.

```C#
// when MouseUp event is called, this moves focus to an invisible button
private void Focus_Reset(object sender, MouseEventArgs e)
{
    button1.Focus();
}
```

### Detecting (X, Y) Location in a Panel
Bind a function to the `MouseMove` event
```C#
private void panel1_MouseMove(object sender, MouseEventArgs e)
{
    lbl_title.Text = string.Format("({0}, {1})", e.X, e.Y);
}
```

```C#
Point pt = new Point(e.Location); // also works
```

### Change the cursor
```C#
panel1.Cursor = Cursors.SizeWE;
```
<img src="http://www.csharphelper.com/howto_display_cursors.png">

### Mouse tracking _through_ controls.
What if you want to track `MouseMove` for `Panel1` but the things inside the panel cover up the panel backgruond? The solution is to create a hanlder function and connect the `MouseMove` event of the panel _and every control inside the panel_ to the same handler. Some controls contain other controls (i.e., nested panels) so a recursive solution is ideal.

```c#
public Form1()
{
    InitializeComponent();
    mouse_track_this_control(panel_dataView);
}

private void MouseTracker_move(object sender, MouseEventArgs e)
{
    richTextBox1.Text = string.Format("MOVE: ({0}, {1})", e.X, e.Y);
}
private void MouseTracker_down(object sender, MouseEventArgs e)
{
    richTextBox1.Text = string.Format("DOWN: ({0}, {1})", e.X, e.Y);
}
private void MouseTracker_up(object sender, MouseEventArgs e)
{
    richTextBox1.Text = string.Format("UP: ({0}, {1})", e.X, e.Y);
}

private void mouse_track_this_control(Control control)
{
    control.MouseMove += MouseTracker_move;
    control.MouseDown += MouseTracker_down;
    control.MouseUp += MouseTracker_up;
    System.Console.WriteLine($"Connecting mouse tracker to {control.Name}");
    foreach (Control control_child in control.Controls)
    {
        mouse_track_this_control(control_child);
    }

}
```

### Cursor Location on the Screen
```C#
mouse_position_screen = new Point(Cursor.Position.X, Cursor.Position.Y);
```

### Cusor Location relative to a Panel
```C#
// find absolute cusor position on the screen
mouse_position = new Point(Cursor.Position.X, Cursor.Position.Y);

// subtract-out the location of the panel we consider (0, 0)
mouse_position.X -= this.PointToScreen(panel_dataView.Location).X;
mouse_position.Y -= this.PointToScreen(panel_dataView.Location).Y;
```

## Click-and-Drag Panning and Zooming
The zooming code keeps messing me up! It works well this way though.

#### Left-Click-Drag Panning
_shift the axis by the pixel distance dragged times unitsPerPixel_
```C#
double dX = (mouse_left_down_position.X - mouse_position.X) * mouse_left_down_axis.xAxis.unitsPerPx;
double dY = (mouse_position.Y - mouse_left_down_position.Y) * mouse_left_down_axis.yAxis.unitsPerPx;
axis1 = new FigureAxis(mouse_left_down_axis.xAxis.min + dX, mouse_left_down_axis.xAxis.max + dX,
		       mouse_left_down_axis.yAxis.min + dY, mouse_left_down_axis.yAxis.max + dY,
		       mouse_left_down_axis.xAxis.pxSize, mouse_left_down_axis.yAxis.pxSize);
```

#### Right-Click-Drag Zooming (v1)
_expand the edges by the same distance of the drag when zooming out, or sqrt(distance) when zooming in_
```C#
double dX = (mouse_right_down_position.X - mouse_position.X) * mouse_right_down_axis.xAxis.unitsPerPx;
double dY = (mouse_position.Y - mouse_right_down_position.Y) * mouse_right_down_axis.yAxis.unitsPerPx;
if (dX < 0) dX = -Math.Sqrt(Math.Abs(dX));
if (dY < 0) dY = -Math.Sqrt(Math.Abs(dY));
axis1 = new FigureAxis(mouse_right_down_axis.xAxis.min - dX, mouse_right_down_axis.xAxis.max + dX,
		       mouse_right_down_axis.yAxis.min - dY, mouse_right_down_axis.yAxis.max + dY,
		       mouse_right_down_axis.xAxis.pxSize, mouse_right_down_axis.yAxis.pxSize);
```

#### Right-Click-Drag Zooming (v1)
This one feels pretty natural. It gets the dX as a fraction of the original window size (dXunits / axisWidthUnits) then applies the zoom function with 10^dX. That's a magical number that feels really nice, and it automatically slows down at extremes.
```C#
double dX = (mouse_right_down_position.X - mouse_position.X) * mouse_right_down_axis.xAxis.unitsPerPx;
double dY = (mouse_position.Y - mouse_right_down_position.Y) * mouse_right_down_axis.yAxis.unitsPerPx;

double dXFrac = dX / (Math.Abs(dX) + (mouse_right_down_axis.xAxis.max - mouse_right_down_axis.xAxis.min));
double dYFrac = dY / (Math.Abs(dY) + (mouse_right_down_axis.yAxis.max - mouse_right_down_axis.yAxis.min));

axis1 = new FigureAxis(mouse_right_down_axis.xAxis.min, mouse_right_down_axis.xAxis.max,
		       mouse_right_down_axis.yAxis.min, mouse_right_down_axis.yAxis.max,
		       mouse_right_down_axis.xAxis.pxSize, mouse_right_down_axis.yAxis.pxSize);

axis1.Zoom(Math.Pow(10, dXFrac), Math.Pow(10, dYFrac)); // THE MAGIC HAPPENS HERE

Clear();
RedrawFrame();
```
