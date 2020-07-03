# Use Serialization to Manage a Configuration File

User settings can be stored in an XML file which is easy to convert to/from classes in C# using common serialization libraries.

```cs
using System.IO;
using System.Xml.Serialization;
```

```cs
class ProgramSettings
{
    public string Version;
    public int width = 111;
    public int height = 222;

    public ProgramSettings()
    {
        var version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
        Version = $"{version.Major}.{version.Minor}.{version.Build}";
    }

    public static ProgramSettings Load(string filePath = "settings.xml")
    {
        var version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
        string expectedVersion = $"{version.Major}.{version.Minor}.{version.Build}";

        XmlSerializer reader = new XmlSerializer(typeof(ProgramSettings));
        using (StreamReader file = new StreamReader(filePath))
        {
            ProgramSettings loadedConfig = (ProgramSettings)reader.Deserialize(file);
            if (loadedConfig.Version == expectedVersion)
                return loadedConfig;
            else
                throw new InvalidOperationException("incompatible config file version");
        }
    }

    public void Save(string filePath = "settings.xml")
    {
        XmlSerializer serializer = new XmlSerializer(typeof(ProgramSettings));
        using (StreamWriter fileWriter = new StreamWriter(filePath))
        {
            serializer.Serialize(fileWriter, this);
        }
    }

    public string GetXML()
    {
        using (StringWriter textWriter = new StringWriter())
        {
            XmlSerializer xmlSerializer = new XmlSerializer(this.GetType());
            xmlSerializer.Serialize(textWriter, this);
            return textWriter.ToString();
        }
    }
}
```
