# Searching an Indexed Filesystem

Note: Only Windows is supported so edit the `.csproj` to target `-Windows`

Install the [`System.Data.OleDb` NuGet Package](https://www.nuget.org/packages/System.Data.OleDb)

OLE DB SQL Field definitions: https://learn.microsoft.com/en-us/windows/win32/properties/core-bumper

```cs
using System.Data.OleDb;

OleDbConnection connection = new(@"Provider=Search.CollatorDSO;Extended Properties=""Application=Windows""");

string query1 = """
    SELECT System.ItemName 
    FROM SystemIndex 
    WHERE scope ='file:C:/' 
    AND System.ItemName LIKE '%.png'
    """;

connection.Open();

OleDbCommand command = new(query1, connection);

using (OleDbDataReader dbReader = command.ExecuteReader())
{
    while (dbReader.Read())
    {
        Console.WriteLine(dbReader[0]);
    }
}

connection.Close();
```
