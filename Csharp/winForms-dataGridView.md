# DataGridView

```cs

/// <summary>
/// Prepare a DataTable for all ABFs in the folder
/// </summary>
/// <returns></returns>
public DataTable GetDataTable(bool parentsOnly=false, bool blankOrphans=true)
{
    DataTable table = new DataTable();
    table.Columns.Add("abfID", typeof(string));
    table.Columns.Add("parent", typeof(string));
    table.Columns.Add("path", typeof(string));
    table.Columns.Add("protocol", typeof(string));
    table.Columns.Add("units", typeof(string));
    table.Columns.Add("annotations", typeof(string));
    table.Columns.Add("sweeps", typeof(int));
    table.Columns.Add("channels", typeof(int));
    table.Columns.Add("length (min)", typeof(double));
    table.Columns.Add("size (Mb)", typeof(double));
    table.Columns.Add("group", typeof(string));
    table.Columns.Add("tags", typeof(string));
    table.Columns.Add("color", typeof(string));

    foreach (ABFinfo abf in abfs)
    {
        if (parentsOnly && abf.abfID != abf.parent)
            continue;
        DataRow row = table.NewRow();
        row.SetField(0, abf.abfID);
        row.SetField(1, abf.parent);
        row.SetField(2, abf.path);
        row.SetField(3, abf.protocol);
        row.SetField(4, abf.units);
        row.SetField(5, abf.annotations);
        row.SetField(6, abf.sweeps);
        row.SetField(7, abf.channels);
        row.SetField(8, abf.lengthMinutes);
        row.SetField(9, abf.sizeMB);
        row.SetField(10, abf.group);
        row.SetField(11, abf.comments);
        row.SetField(12, abf.color);

        if (blankOrphans == true && abf.parent == "orphan")
        {
            row.SetField(1, "");
        }

        table.Rows.Add(row);
    }

    return table;
}

dataGridView1.DataSource = abfFolder.GetDataTable(cbParentsOnly.Checked);
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

## Column Resizing
After filling rows with data:

```cs
// this worked in 2024
dataGridView1.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
```

```cs
// resize one column
dataGridView1.AutoResizeColumn(0);
```

```cs
// resize all columns
dataGridView1.AutoResizeColumns();
```

## Lots of stuff programmatically

This method is SLOW! 2 columns with 10,000 rows takes almost 2 full seconds to populate this way.

```cs
Random rand = new Random();

int rowCount = 10_000;
DataGridViewRow[] rows = new DataGridViewRow[rowCount];
var view = new DataGridView();

for (int i = 0; i < rowCount; i++)
{
    double valueA = rand.NextDouble() * 1000;
    double valueB = rand.NextDouble() * 1000;
    rows[i] = new DataGridViewRow();
    rows[i].HeaderCell.Value = i.ToString();
    rows[i].CreateCells(dataGridView1, valueA.ToString(), valueB.ToString());
}
dataGridView1.Rows.Clear();
dataGridView1.Rows.AddRange(rows);
dataGridView1.TopLeftHeaderCell.Value = "#";
dataGridView1.AutoResizeRowHeadersWidth(DataGridViewRowHeadersWidthSizeMode.AutoSizeToAllHeaders);
dataGridView1.AutoResizeColumns();
```
