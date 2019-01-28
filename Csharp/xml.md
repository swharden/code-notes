# XML Parsing

## Example Code
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
