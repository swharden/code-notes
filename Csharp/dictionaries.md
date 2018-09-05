# dictionaries

## Simple Example
```cs
Dictionary<string, string> dict = new Dictionary<string, string>();

dict.Add("scott", "harden");
dict.Add("bill", "gates");
dict.Add("steve", "jobs");

// print items in the order they were added
foreach (string key in dict.Keys)
    Console.WriteLine($"{key} = {dict[key]}\n");

// print items in alphabetical order
List<string> keyList = new List<string>(dict.Keys);
keyList.Sort();
foreach (string key in keyList)
    Console.WriteLine($"{key} = {dict[key]}\n");
```

## Dictionary where the value is a list
```cs
Dictionary<string, List<string>> abfIDsByParent = new Dictionary<string, List<string>>();

// add every ABF to its particular parent
abfIDsByParent.Clear();
string currentParent = "orphan";
foreach (string abfID in abfIDs)
{
    // update our parent if needed
    if (abfParentIDs.Contains(abfID))
    {
        currentParent = abfID;
    }

    // ensure the key exists in the dictionary
    if (!abfIDsByParent.ContainsKey(currentParent))
    {
        abfIDsByParent.Add(currentParent, new List<string>());
    }

    // add this ABF to the dictionary key list
    List<string> l = abfIDsByParent[currentParent];
    l.Add(abfID);
    abfIDsByParent[currentParent] = l;
}
```
