# Useful snippits for a private project

## Experiment Organizer DataTable
Just create a dataTable and let this code fill it with dummy data.
```
// fill the experiment organizer
DataTable dataTable = new DataTable();
var expOrgColumns = new List<string>() { "ABF ID", "Group", "Notes" };
foreach (string colName in expOrgColumns)
{
    dataTable.Columns.Add(colName, typeof(string));
}

for (int abfNumber=0; abfNumber<listBox2.Items.Count; abfNumber++)
{
    if (random.NextDouble() > .1)
        continue;

    string cellType = "pyramidal";
    if (random.NextDouble() > .5)
        cellType = "interneuron";

    string notes = "";
    if (random.NextDouble() <.1)
        notes = "unstable";

    DataRow dataRow = dataTable.NewRow();
    dataRow.SetField(0, listBox2.Items[abfNumber].ToString());
    dataRow.SetField(1, cellType);
    dataRow.SetField(2, notes);
    dataTable.Rows.Add(dataRow);
}

dataGridView1.DataSource = dataTable;

// adjust the width of a column to fit its contents
dataGridView1.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
```
