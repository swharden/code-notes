# Dialog

## Use Windows Forms Dialogs in WPF
### Add this to your csproj `PropertyGroup`
```xml
<UseWindowsForms>true</UseWindowsForms>
```

### Add this `using`
```cs
using WinForms = System.Windows.Forms;
```

### Add a WinForms Dialog
```cs
var diag = new WinForms.FolderBrowserDialog();
if (diag.ShowDialog() == WinForms.DialogResult.OK)
{
    string selectedPath = diag.SelectedPath;
}
```

## Messagebox
```cs
MessageBox.Show("some long message here","WARNING!!!");
MessageBox.Show(msg, "Source Folder Help", MessageBoxButtons.OK, MessageBoxIcon.Question);
```

## Yes/No Prompt
```cs
DialogResult dialogResult = MessageBox.Show("Do you really want to do this?", "Window title", MessageBoxButtons.YesNo);
if (dialogResult == DialogResult.Yes)
{
    //do something
}
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

## Select File
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

You can also:

```cs
diag.Multiselect = true;
```

## Select Folder
```cs
var diag = new FolderBrowserDialog();
if (diag.ShowDialog() == DialogResult.OK)
{
    string selectedPath = diag.SelectedPath;
}
```

## Select Folder Hack
You may want to use the save dialog to select the folder because it's better than the folder browser dialog
```cs
SaveFileDialog sf = new SaveFileDialog();
sf.FileName = "Load this folder";
if (sf.ShowDialog() == DialogResult.OK)
{
    string pathFolder = System.IO.Path.GetDirectoryName(sf.FileName);
    SetFolder(pathFolder);
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
