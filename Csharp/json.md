# Working with JSON in C#

## Encoding and Decoding JSON with Native Libraries

There are lots of third party JSON libraries out there, but I prefer to use the ones that come with Visual Studio.

```cs
using System.Web.Script.Serialization;
```

### Constructing JSON from Scratch
```cs
JavaScriptSerializer serializer = new JavaScriptSerializer();
string serializedResult = serializer.Serialize(RegisteredUsers);
//serializedResult = JsonPrettify(serializedResult);
Console.WriteLine(serializedResult);
```

### Decoding JSON
```cs
// this might not be the best for nested JSON...
List<Person> deserializedObjects = serializer.Deserialize<List<Person>>(serializedResult);
foreach (Person person in deserializedObjects)
    Console.WriteLine(person.Name);
```

### Person class

For reference, here's the code that made-up the `RegisteredUsers` List and the `Person` class:

```cs
class Person
{
    public int PersonID;
    public string Name;
    public bool Registered;
}
```

```cs
List<Person> RegisteredUsers = new List<Person>();
RegisteredUsers.Add(new Person() { PersonID = 1, Name = "Bryon Hetrick", Registered = true });
RegisteredUsers.Add(new Person() { PersonID = 2, Name = "Nicole Wilcox", Registered = true });
RegisteredUsers.Add(new Person() { PersonID = 3, Name = "Adrian Martinson", Registered = false });
```

## Prettify Json

```cs
static string JsonPrettify(string json, int indentation = 2)
{
    string indentString = String.Concat(Enumerable.Repeat(" ", indentation));
    int indentLevel = 0;
    int quoteCount = 0;
    var result =
        from ch in json
        let quotes = ch == '"' ? quoteCount++ : quoteCount
        let lineBreak = ch == ',' && quotes % 2 == 0 ? ch + Environment.NewLine + String.Concat(Enumerable.Repeat(indentString, indentLevel)) : null
        let openChar = ch == '{' || ch == '[' ? ch + Environment.NewLine + String.Concat(Enumerable.Repeat(indentString, ++indentLevel)) : ch.ToString()
        let closeChar = ch == '}' || ch == ']' ? Environment.NewLine + String.Concat(Enumerable.Repeat(indentString, --indentLevel)) + ch : ch.ToString()
        select lineBreak == null
                    ? openChar.Length > 1
                        ? openChar
                        : closeChar
                    : lineBreak;
    return String.Concat(result);
}
```

#### Example Input
```
[{"PersonID":1,"Name":"Bryon Hetrick","Registered":true},{"PersonID":2,"Name":"Nicole Wilcox","Registered":true},{"PersonID":3,"Name":"Adrian Martinson","Registered":false}]
```

#### Example Output
```
[
  {
    "PersonID":1,
    "Name":"Bryon Hetrick",
    "Registered":true
  },
  {
    "PersonID":2,
    "Name":"Nicole Wilcox",
    "Registered":true
  },
  {
    "PersonID":3,
    "Name":"Adrian Martinson",
    "Registered":false
  }
]
```
