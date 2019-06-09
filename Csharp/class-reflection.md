# Class Inspection with Reflection
Sometimes I want to iterate through every class-level variable or property.

```cs
// iterates fields (not properties)
foreach (var field in this.GetType().GetFields())
{
    string type = field.FieldType.ToString();
    string name = field.Name;
    string value = field.GetValue(this).ToString();
    Console.WriteLine($"({type}) {name} = {value}");
}
```
