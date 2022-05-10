using System.Text.Json;

namespace MyApi;

public static class Humans
{
    public static HttpResult Get(string filePath)
    {
        filePath = Path.GetFullPath(filePath);

        if (!File.Exists(filePath))
        {
            return new HttpResultBadRequest($"file does not exist: {filePath}");
        }

        try
        {
            Human[] humans = Load(filePath);
            return new HttpResultOK(humans);
        }
        catch (Exception ex)
        {
            return new HttpResultBadRequest($"could not load file: {filePath}\n{ex}");
        }

    }

    public static HttpResult Put(string filePath, Human newHuman)
    {
        try
        {
            if (!File.Exists(filePath))
            {
                Human[] emptyHumans = Array.Empty<Human>();
                Save(filePath, emptyHumans);
            }
        }
        catch (Exception ex)
        {
            return new HttpResultBadRequest($"could not create file: {filePath}\n{ex}");
        }

        Human[] humans = Load(filePath);

        int[] matchingIndexes = humans.Select((human, index) => (human, index))
            .Where(x => x.human.Name == newHuman.Name)
            .Select(x => x.index)
            .ToArray();

        if (matchingIndexes.Any())
        {
            humans[matchingIndexes.First()] = newHuman;
            Save(filePath, humans);
            return new HttpResultOK("updated human");
        }
        else
        {
            humans = humans.Append(newHuman).ToArray();
            Save(filePath, humans);
            return new HttpResultOK("added human");
        }
    }

    private static void Save(string filePath, Human[] humans)
    {
        var options = new JsonSerializerOptions() { WriteIndented = true };
        string json = JsonSerializer.Serialize(humans, options);
        File.WriteAllText(filePath, json);
    }

    private static Human[] Load(string filePath)
    {
        string json = File.ReadAllText(filePath);
        Human[] humans = JsonSerializer.Deserialize<Human[]>(json) ?? throw new NullReferenceException();
        return humans;
    }
}
