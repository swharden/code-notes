# Use Serialization to Manage a Configuration File

User settings can be stored in an XML file which is easy to convert to/from classes in C# using common serialization libraries.

```cs
public class MyProgramConfig
{
    public string Version;
    public int width = 111;
    public int height = 222;

    public MyProgramConfig()
    {
        var version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
        Version = $"{version.Major}.{version.Minor}.{version.Build}";
    }

    public static MyProgramConfig Load(string filePath)
    {
        var version = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
        string expectedVersion = $"{version.Major}.{version.Minor}.{version.Build}";

        XmlSerializer reader = new XmlSerializer(typeof(MyProgramConfig));
        using StreamReader file = new StreamReader(filePath);
        MyProgramConfig loadedConfig = (MyProgramConfig)reader.Deserialize(file);
        if (loadedConfig.Version == expectedVersion)
            return loadedConfig;
        else
            throw new InvalidOperationException("incompatible config file version");
    }

    public void Save(string filePath)
    {
        XmlSerializer serializer = new XmlSerializer(typeof(MyProgramConfig));
        using StreamWriter fileWriter = new StreamWriter(filePath);
        serializer.Serialize(fileWriter, this);
    }

    public string GetXML()
    {
        using StringWriter textWriter = new StringWriter();
        XmlSerializer xmlSerializer = new XmlSerializer(this.GetType());
        xmlSerializer.Serialize(textWriter, this);
        return textWriter.ToString();
    }
}
```
