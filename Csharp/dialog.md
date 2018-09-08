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
