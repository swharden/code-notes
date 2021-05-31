# Working with JSON in C#

System.Text.Json is a modern built-in alternative to Newtonsoft libraries.

```cs
using System.Text.Json;
```

## Create JSON From Scratch

```cs
using var stream = new MemoryStream();
var options = new JsonWriterOptions() { Indented = true };
using var writer = new Utf8JsonWriter(stream, options);

writer.WriteStartObject();
writer.WriteNumber("temperatureC", TemperatureC);
writer.WriteStartArray("ions");
foreach (var ion in Ions)
{
    writer.WriteStartObject();
    writer.WriteString("name", ion.name);
    writer.WriteNumber("charge", ion.charge);
    writer.WriteNumber("conductivity", ion.conductivity);
    writer.WriteEndObject();
}
writer.WriteEndArray();
writer.WriteEndObject();

writer.Flush();
string json = Encoding.UTF8.GetString(stream.ToArray());
```

## Navigate JSON Manually

```cs
using (JsonDocument document = JsonDocument.Parse(jsonString))
{
    double temperatureC = document.RootElement.GetProperty("temperatureC").GetDouble();
    List<Ion> ions = new List<Ion>();
    foreach (JsonElement element in document.RootElement.GetProperty("ions").EnumerateArray())
    {
        string name = element.GetProperty("name").GetString();
        int charge = element.GetProperty("charge").GetInt32();
        double conductivity = element.GetProperty("conductivity").GetDouble();
    }
};
```

## Serialize/Deserialize C# Objects To/From JSON

Serializable objects are POCOs that:
* Have auto-properties
* Have a parameterless constructor

```cs
class Life
{
    public string Name { get; set; }
    public int Age { get; set; }
    public List<string> Interests { get; set; } = new List<string>();
}
```

```cs
// instantiate an object
Life myLife = new Life() { Name = "Scott", Age = 35 };
myLife.Interests.Add("science");
myLife.Interests.Add("computers");
myLife.Interests.Add("space");
```

```cs
// C# Object to JSON (with option for pretty formatting)
var options = new JsonSerializerOptions() { WriteIndented = true };
string json = JsonSerializer.Serialize(myLife, options);
Console.WriteLine(json);
```

```cs
```

```cs
// JSON to C# object
Life myNewLife = JsonSerializer.Deserialize<Life>(json);
Console.WriteLine(myNewLife.Name + " likes " + string.Join(" and ", myNewLife.Interests));
```

## Prettify JSON with C#

```cs
// convert an ugly document to a pretty one
JsonDocument document = JsonDocument.Parse(jsonString);
using var stream = new MemoryStream();
var options = new JsonWriterOptions() { Indented = true };
using var writer = new Utf8JsonWriter(stream, options);
document.WriteTo(writer);
writer.Flush();
string jsonPretty = Encoding.UTF8.GetString(stream.ToArray());
```
