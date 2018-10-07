# Dialog

## Messagebox
```cs
MessageBox.Show("some long message here","WARNING!!!");
MessageBox.Show(msg, "Source Folder Help", MessageBoxButtons.OK, MessageBoxIcon.Question);
```

## Save File
```cs
SaveFileDialog savefile = new SaveFileDialog();
savefile.FileName = "diyECG.jpg";
savefile.Filter = "JPG Files (*.jpg)|*.jpg|All files (*.*)|*.*";
if (savefile.ShowDialog() == DialogResult.OK) { /* do something */ }
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
