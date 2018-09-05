# Classes

## Making properties read-only
```C#
class Axis1d
{
  public double x1 { get; private set; }
  public double x2 { get; private set; }
}
```

## Listing Every Object in a Class
```cs
public string Info()
{
    string info = $"### ABF Information for {abfID} ###\n";

    // populate a dictionary with fields in this class
    Dictionary<string, string> dict = new Dictionary<string, string>();
    foreach (System.Reflection.FieldInfo x in this.GetType().GetFields())
    {
        System.Object val = x.GetValue(this);
        string valStr = "null";
        if (val != null)
            valStr = val.ToString();
        dict.Add(x.Name, valStr);
    }

    // print items in alphabetical order
    List<string> keyList = new List<string>(dict.Keys);
    keyList.Sort();
    foreach (string key in keyList)
    {
        info += $"{key} = {dict[key]}\n";
    }
    return info;
}
```

```cs
FieldInfo[] fields = this.GetType().GetFields(BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Public);
foreach (FieldInfo x in fields){}
```

```cs
string valStr=null;
if (val == null)
{
    valStr = "null";
}
else if (val.GetType().IsArray)
{
    valStr = "[" + string.Join(", ", (string[])val) + "]";
}
```
