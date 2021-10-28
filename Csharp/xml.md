# XML Parsing

* Favor `XDocument` over `XmlDocument`. It's newer and works with LINQ.
* [Microsoft: XDocument](https://docs.microsoft.com/en-us/dotnet/api/system.xml.linq.xdocument)
* [Microsoft: XElement](https://docs.microsoft.com/en-us/dotnet/api/system.xml.linq.xelement)

### Parse XML
```cs
// parse XML in a string
string xmlText = File.ReadAllText(xmlPath);
XDocument doc = XDocument.Parse(xmlText);
```

```cs
// load XML from a file
XDocument doc = XDocument.Load(xmlPath);
```

### Select an element by its path

```cs
using System.Xml.XPath;
```

```cs
var element = doc.XPathSelectElement("/top/middle/low");
```

### Find child element by name at any level
```cs
XDocument doc = XDocument.Parse(xmlText);
foreach (XElement element in doc.Descendants("grandchild"))
    Console.WriteLine(element);
```

### Create XML _de novo_
```cs

XDocument doc = new XDocument();

/*
or this to get the <?xml ?> header
XDeclaration declaration = new(version: "1.0", encoding: "utf-16", standalone: "yes");
XDocument doc = new(declaration);
*/
	    
XElement experiment = new XElement("Experiment");
experiment.SetAttributeValue("created", $"2018-01-01");
experiment.SetAttributeValue("modified", $"2019-09-29");
doc.Add(experiment);

XElement notes = new XElement("notes");
notes.Value = "experiment worked so awesomely";
experiment.Add(notes);

XElement tags = new XElement("tags");
for (int i = 0; i < 5; i++)
{
	XElement tag = new XElement("tag");
	tag.Value = $"fancy drug {i + 1}";
	tag.SetAttributeValue("timeSec", $"{i * 60}");
	tag.SetAttributeValue("frame", $"{i * 5}");
	tags.Add(tag);
}
experiment.Add(tags);

System.Console.WriteLine(doc.ToString());
System.IO.File.WriteAllText(pathFile, doc.ToString());
System.Console.WriteLine($"Saved: {pathFile}");
```

---

## XmlDocument (obsolete)

### Reading XML with `XmlDocument`
```cs
using System.Xml;
```

```cs
XmlDocument xmlDoc = new XmlDocument();
xmlDoc.Load(pathXML);

// top level XML properties
Version = xmlDoc.DocumentElement.SelectSingleNode("/PVScan").Attributes["version"].Value;
Date = xmlDoc.DocumentElement.SelectSingleNode("/PVScan").Attributes["date"].Value;
SequenceType = xmlDoc.DocumentElement.SelectSingleNode("/PVScan/Sequence").Attributes["type"].Value;

// load all laser settings
XmlNodeList nodesLaserPower = xmlDoc.DocumentElement.SelectNodes("/PVScan/PVStateShard/PVStateValue[@key='laserPower']");
foreach (XmlElement xmlLaser in nodesLaserPower[0].ChildNodes)
{
	int laserIndex = int.Parse(xmlLaser.Attributes["index"].Value);
	double laserPower = double.Parse(xmlLaser.Attributes["value"].Value);
	string laserName = xmlLaser.Attributes["description"].Value;
}
```

### Creating XML with `XmlDocument`
```cs

XmlDocument doc = new XmlDocument();

XmlElement notes = doc.CreateElement("notes");
notes.InnerText = "experiment worked so awesomely";

XmlElement tags = doc.CreateElement("tags");
for (int i = 0; i < 5; i++)
{
	XmlElement tag = doc.CreateElement("tag");
	tag.SetAttribute("timeSec", $"{i * 60}");
	tag.SetAttribute("frame", $"{i * 5}");
	tag.InnerText = $"fancy drug {i + 1}";
	tags.AppendChild(tag);
}

XmlElement xmlExperiment = doc.CreateElement("Experiment");
xmlExperiment.SetAttribute("created", $"2018-01-01");
xmlExperiment.SetAttribute("modified", $"2019-09-29");
xmlExperiment.AppendChild(notes);
xmlExperiment.AppendChild(tags);
doc.AppendChild(xmlExperiment);

string xmlText = doc.OuterXml;
System.IO.File.WriteAllText(pathFile, xmlText);
System.Console.WriteLine($"Saved: {pathFile}");
```

Output:
```xml
<Experiment created="2018-01-01" modified="2019-09-29">
  <notes>experiment worked so awesomely</notes>
  <tags>
    <tag timeSec="0" frame="0">fancy drug 1</tag>
    <tag timeSec="60" frame="5">fancy drug 2</tag>
    <tag timeSec="120" frame="10">fancy drug 3</tag>
    <tag timeSec="180" frame="15">fancy drug 4</tag>
    <tag timeSec="240" frame="20">fancy drug 5</tag>
  </tags>
</Experiment>
```
