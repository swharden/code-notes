# DataGridView

```cs
dataGridView1.DataSource = AbfTable(abfFolder);

public DataTable AbfTable(string abfFolder)
{
    if (!System.IO.Directory.Exists(abfFolder)){
        return null;
    }

    DataTable table = new DataTable();
    table.Columns.Add("abfID", typeof(string));
    table.Columns.Add("path", typeof(string));
    table.Columns.Add("protocol", typeof(string));
    table.Columns.Add("sweepCount", typeof(int));
    table.Columns.Add("channelCount", typeof(int));
    table.Columns.Add("lengthSec", typeof(double));
    table.Columns.Add("units", typeof(string));
    table.Columns.Add("tags", typeof(string));

    string[] filePaths = System.IO.Directory.GetFiles(abfFolder, "*.abf");
    foreach (string filePath in filePaths)
    {
        ABF abf = new ABF(filePath, false);
        string protocol = System.IO.Path.GetFileNameWithoutExtension(abf.protocolPath);
        double lengthSec = abf.dataPointCount / abf.dataRate;
        string units = String.Join(", ", abf.adcUnits);
        string tags = String.Join(", ", abf.tagComments);
        table.Rows.Add(abf.abfID, abf.abfFilePath, protocol, abf.sweepCount, abf.channelCount, lengthSec, units, tags);
    }

    return table;

}
```

## Right-Click Menu
```cs
private void dataGridView1_MouseClick(object sender, MouseEventArgs e)
{
    if (e.Button == MouseButtons.Right)
    {
        int thisRow = dataGridView1.HitTest(e.X, e.Y).RowIndex;
        string abfFilePath = dataGridView1.Rows[thisRow].Cells[1].Value.ToString();
        string abfFileName = System.IO.Path.GetFileName(abfFilePath);

        dataGridView1.ClearSelection();
        dataGridView1.Rows[thisRow].Selected = true;

        ContextMenu m = new ContextMenu();
        m.MenuItems.Add(new MenuItem($"Copy Path to {abfFileName}"));
        m.MenuItems.Add(new MenuItem($"Launch {abfFileName} in ClampFit"));
        m.Show(dataGridView1, new Point(e.X, e.Y));

    }
}
```
