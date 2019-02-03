# Panels

## Programmatically Adding Labels to a Scrollable Panel
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

## Programmatically Adding Images to a Scrollable Panel
```cs
string imageFolder = @"C:\Users\scott\Documents\GitHub\pyABF\data\headers";
string[] imagePaths = System.IO.Directory.GetFiles(imageFolder, "*.png");

int paddingLeft = 10;
int paddingTop = 10;

int nextYPos = paddingTop;

foreach (string imagePath in imagePaths)
{
    string imageFileName = System.IO.Path.GetFileName(imagePath);
    Bitmap bmp = new Bitmap(imagePath);
    PictureBox pb = new PictureBox();
    pb.Image = bmp;
    pb.Size = new Size(bmp.Width, bmp.Height);
    pb.Location = new Point(paddingLeft, nextYPos);
    panel1.Controls.Add(pb);
    nextYPos += pb.Height + paddingTop;
    Console.WriteLine($"{pb.Location} {imageFileName} ({bmp.Width}, {bmp.Height})");
}
```

## Remove all Controls from a Panel
```cs
panel1.Controls.Clear();
```
