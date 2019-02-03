# Panels

## Programmatically Adding Controls to a Scrollable Panel
Enable the `AutoScroll` property of the panel so scrollbars appear when controls are outside the viewable area.

```cs
private void PlaceLabelsOnPanel(int numLabels = 50, int xSpacing = 10, int ySpacing = 20)
{
    for (int i = 0; i < numLabels; i++)
    {
        int xPos = (i + 1) * xSpacing;
        int yPos = (i + 1) * ySpacing;

        Label lbl = new Label();
        lbl.Location = new Point(xPos, yPos);
        lbl.Text = $"Label {i + 1} at ({xPos}, {yPos})";
        lbl.AutoSize = true;

        panel1.Controls.Add(lbl);
    }
}
```
