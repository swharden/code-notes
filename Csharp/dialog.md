# Dialog

## Messagebox
```cs
MessageBox.Show("some long message here","WARNING!!!");
MessageBox.Show(msg, "Source Folder Help", MessageBoxButtons.OK, MessageBoxIcon.Question);
```

## Save File
```cs
SaveFileDialog savefile = new SaveFileDialog();
savefile.FileName = "demo.png";
savefile.Filter = "PNG Files (*.png)|*.png|All files (*.*)|*.*";
if (savefile.ShowDialog() == DialogResult.OK) {
    string saveFilePath = savefile.FileName;
}
```

## Select Folder
```cs
var diag = new FolderBrowserDialog();
if (diag.ShowDialog() == DialogResult.OK)
{
    string selectedPath = diag.SelectedPath;
}
```

## Select Image
```cs
OpenFileDialog diag = new OpenFileDialog();
diag.Filter = "TIF files (*.tif, *.tiff)|*.tif;*.tiff";
diag.Filter += "|JPG Files (*.jpg, *.jpeg)|*.jpg;*.jpeg";
diag.Filter += "|PNG Files (*.png)|*.png;*.png";
diag.Filter += "|BMP Files (*.bmp)|*.bmp;*.bmp";
diag.Filter  += "|All files (*.*)|*.*";
if (diag.ShowDialog() == DialogResult.OK) {
    SetImage(diag.FileName);
}
```

## Dialog from scratch (get a double)
```cs
public double DialogGetNumber(string text, string caption, int valMin=1, int valMax=1000)
{
    Form prompt = new Form();
    prompt.Width = 250;
    prompt.Height = 150;
    prompt.Text = caption;
    Label textLabel = new Label() { Left = 10, Top = 10, Text = text };
    NumericUpDown nudVal = new NumericUpDown() { Left = 10, Top = 40, Width = 100 };
    nudVal.Minimum = valMin;
    nudVal.Maximum = valMax;
    Button btnOk = new Button() { Text = "Ok", Left = 120, Top = 40, Width = 50 };
    btnOk.Click += (sender, e) => { prompt.Close(); };
    prompt.Controls.Add(btnOk);
    prompt.Controls.Add(textLabel);
    prompt.Controls.Add(nudVal);
    prompt.ShowDialog();
    return (double)nudVal.Value;
}
```
