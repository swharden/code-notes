# Label

## Programmatically Create a Label with Special Font
```cs
Label lbl = new Label();
lbl.Location = new Point(10, 20);
lbl.Text = "test label";
lbl.AutoSize = true;
lbl.Font = new Font("Arial", 14, FontStyle.Bold);
```
