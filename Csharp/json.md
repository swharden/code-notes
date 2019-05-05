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

## Nesting JSON
The serializer is a simple way to turn a class into a JSON string. To create nested JSON, put classes inside other classes and serialize the whole thing.

#### First create nested classes...
```cs
public class Names
{
    public string name1 = "alpha";
    public string name2 = "bravo";
    public string name3 = "charley";
    public string name4 = "delta";
}

public class Request
{
    public readonly Action action;
    public readonly string path;
    public readonly string identifier;
    public readonly string value;
    public readonly Names names;
    public readonly int coolNumber;

    public Request(Action action, string path = null, string identifier = null, string value = null)
    {
        this.action = action;
        this.path = path;
        this.identifier = identifier;
        this.value = value;
        names = new Names();
        coolNumber = 12345;
    }
}
```

#### Then serialize the top class...
```cs
JavaScriptSerializer serializer = new JavaScriptSerializer();
string json = serializer.Serialize(this); // a class can serialize itself!!!
Console.WriteLine(json);
```

#### Output
```
{
  "action":0,
  "path":"Path",
  "identifier":"17703011.abf",
  "value":"1234",
  "names":{
    "name1":"alpha",
    "name2":"bravo",
    "name3":"charley",
    "name4":"delta"
  },
  "coolNumber":12345
}
```
