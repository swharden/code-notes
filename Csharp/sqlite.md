# SQLite in Csharp

* [SQLite Browser](https://sqlitebrowser.org/)

* DO NOT CONSTRUCT QUERIES BY EDITING STRINGS! Interact with command abstractions instead (e.g., SqliteCommand.Parameters)

## Create a DB

```cs
// open the database file (creating it if it doesn't exist)
using var conn = new SqliteConnection($"Data Source=test.db;");
conn.Open();
```
## Create a Table
```cs
using var createTableCommand = conn.CreateCommand();
createTableCommand.CommandText =
    "CREATE TABLE IF NOT EXISTS Abfs" +
    "(" +
        "[Id] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
        "[Folder] TEXT NOT NULL, " +
        "[Filename] TEXT NOT NULL, " +
        "[Date] CHAR(10) NOT NULL, " + // YYYY-MM-DD
        "[Time] CHAR(12) NOT NULL " + // HH:MM:SS.SSS
    ")";
createTableCommand.ExecuteNonQuery();
```

## Insertions
```cs
foreach (string abfFile in System.IO.Directory.GetFiles(SampleData.DATA_FOLDER, "*.abf"))
{
    string abfFilePath = System.IO.Path.GetFullPath(abfFile);
    var abf = new AbfSharp.ABF(abfFilePath);

    using var insertAbfCommand = new SqliteCommand("INSERT INTO Abfs " +
        "(Folder, Filename, Date, Time) " +
        "VALUES (@folder, @filename, @date, @time)", conn);
    insertAbfCommand.Parameters.AddWithValue("folder", System.IO.Path.GetDirectoryName(abf.Path));
    insertAbfCommand.Parameters.AddWithValue("filename", System.IO.Path.GetFileName(abf.Path));
    insertAbfCommand.Parameters.AddWithValue("date", abf.Header.StartDateTime.ToString("yyyy-MM-dd"));
    insertAbfCommand.Parameters.AddWithValue("time", abf.Header.StartDateTime.ToString("HH:mm:ss.fff"));
    insertAbfCommand.ExecuteNonQuery();
}
```
