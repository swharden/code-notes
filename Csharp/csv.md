# CSV Parsing with C#

### I don't like third party options

You could use a third party library, but lots of them are complicated:

* [CsvHelper](https://joshclose.github.io/CsvHelper/getting-started/)
* [TinyCsvParser](https://github.com/TinyCsvParser/TinyCsvParser)

`Microsoft.VisualBasic.FileIO.TextFieldParser` used to be standard, but it's .NET Framework only and ports are unofficial:

* [CsvTextFieldParser](https://www.nuget.org/packages/CsvTextFieldParser)
* [TextFieldParserStandard](https://www.nuget.org/packages/TextFieldParserStandard)

## Native C# CSV Parser

This code has the minimum functionality to parse CSV files and escape commas inside quotes

```cs
string[][] itemsByLine = CSV.ReadFile("demo.csv");
foreach (string[] items in itemsByLine)
{
    string line = string.Join(", ", items);
    Console.WriteLine(line);
}
```

```cs
public static class CSV
{
    public static string[][] ReadFile(string filename)
    {
        string[] lines = File.ReadAllLines(filename);
        string[][] itemsByLine = lines.Select(x => ParseLine(x)).ToArray();
        return itemsByLine;
    }

    public static string[] ParseLine(string text, char separator = ',')
    {
        bool isquotedString = false;
        int i1 = 0;
        int i2 = 0;
        List<string> items = new();

        foreach (char c in text)
        {
            if (c == '"')
            {
                isquotedString = !isquotedString;
            }

            if (c == separator && !isquotedString)
            {
                items.Add(RemoveQuotes(text[i1..i2]));
                i1 = i2 + 1;
            }

            i2++;
        }

        items.Add(RemoveQuotes(text[i1..i2]));
        return items.ToArray();
    }

    private static string RemoveQuotes(string text)
    {
        if (string.IsNullOrEmpty(text))
            return text;

        if (text[0] == '"' && text.Length > 2)
            return text.Substring(1, text.Length - 2).Replace("\"\"", "\"");

        return text.Replace("\"\"", "\"");
    }
}
```

## CSV Builder
```cs
using System.Text;

namespace ConvertCsv;

public class CsvBuilder
{
    private readonly struct Column
    {
        public readonly string Title;
        public readonly string[] Values;

        public Column(string title, IEnumerable<double> values)
        {
            Title = title;
            Values = values.Select(x => x.ToString()).ToArray();
        }

        public Column(string title, IEnumerable<string> values)
        {
            Title = title;
            Values = values.Select(x => $"\"{x}\"").ToArray();
        }
    }

    private readonly List<Column> Columns = [];

    public int ColumnCount => Columns.Count;

    public int RowCount => Columns.Select(x => x.Values.Length).Max();

    public CsvBuilder()
    {
    }

    public void Add(string title, IEnumerable<double> data)
    {
        Columns.Add(new Column(title, data));
    }

    public void Add(string title, IEnumerable<string> data)
    {
        Columns.Add(new Column(title, data));
    }

    public void SaveAs(string filePath, bool header = true)
    {
        StringBuilder sb = new();

        if (header)
        {
            sb.AppendLine(string.Join(", ", Columns.Select(x => $"\"{x.Title}\"")));
        }

        for (int rowIndex = 0; rowIndex < RowCount; rowIndex++)
        {
            for (int colIndex = 0; colIndex < Columns.Count; colIndex++)
            {
                int rowsInThisColumn = Columns[colIndex].Values.Length;

                if (rowIndex < rowsInThisColumn)
                {
                    sb.Append(Columns[colIndex].Values[rowIndex]);
                }

                if (colIndex < Columns.Count - 1)
                {
                    sb.Append(", ");
                }
                else
                {
                    sb.AppendLine();
                }
            }
        }

        System.IO.File.WriteAllText(filePath, sb.ToString());
    }
}
```
