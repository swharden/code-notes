# Classes

## Creating Disposable Classes
This allows your class to have the `Dispose()` method called automatically if instantiated with a `using` statement. This is helpful for classes which must only be run one at a time, or to ensure the user doesn't forget to call the `Dispose()` method manually after using the class.

```cs
public class AbfReader : IDisposable
{
    public vsABF.ABF abf;

    public AbfReader(string abfFilePath)
    {
        abf = new vsABF.ABF(abfFilePath);
    }

    public void Dispose()
    {
        abf.Close();
    }
}
```

```cs
using (AbfReader abf = new AbfReader(childAbfFilePath))
{
    details = abf.GetOneLineSummary();
}
```

```cs
using (AbfReader abf = new AbfReader(childAbfFilePath))
{
    details = abf.GetOneLineSummary();
}
```

## Making properties read-only
```C#
class Axis1d
{
  public double x1 { get; private set; }
  public double x2 { get; private set; }
}
```

## Override ToString()
```cs
class Person
{
    public string Name { get; set; }
    public int Age { get; set; }

    public override string ToString()
    {
        return "Person: " + Name + " " + Age;
    }
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
if (val.GetType().IsArray)
{
    List<string> vals = new List<string>();
    foreach (var item in (Array)val)
    {
        vals.Add(item.ToString());
    }
    valStr = "[" + string.Join(", ", vals) + "]";
}
```
