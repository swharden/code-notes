# dictionaries

```cs
IDictionary<string, List<string>> abfIDsByParent = new Dictionary<string, List<string>>();

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
