using Microsoft.AspNetCore.Mvc;
using System.IO;
using System.Text.Json;

namespace MvcApi.Controllers;

[ApiController]
[Route("[controller]")]
public class HumansController : ControllerBase
{
    private readonly ILogger<HumansController> Logger;

    public HumansController(ILogger<HumansController> logger)
    {
        Logger = logger;
    }

    [HttpGet]
    [ProducesResponseType(typeof(Models.Human[]), StatusCodes.Status200OK)]
    [ProducesResponseType(StatusCodes.Status404NotFound)]
    [ProducesResponseType(StatusCodes.Status500InternalServerError)]
    public IActionResult Get(string dbFilename = "humans.json")
    {
        if (!System.IO.File.Exists(dbFilename))
        {
            return StatusCode(StatusCodes.Status404NotFound);
        }

        try
        {
            Models.Human[] humans = Load(dbFilename);
            return StatusCode(StatusCodes.Status200OK, humans);
        }
        catch (Exception ex)
        {
            string message = $"could not parse file: {dbFilename}\n{ex}";
            Logger.LogError(message);
            return StatusCode(StatusCodes.Status500InternalServerError, message);
        }
    }

    [HttpPut()]
    [ProducesResponseType(StatusCodes.Status500InternalServerError)]
    [ProducesResponseType(StatusCodes.Status201Created)]
    [ProducesResponseType(StatusCodes.Status200OK)]
    public IActionResult Put(Models.Human newHuman, string dbFilename = "humans.json")
    {
        try
        {
            if (!System.IO.File.Exists(dbFilename))
            {
                Models.Human[] emptyHumans = Array.Empty<Models.Human>();
                Save(dbFilename, emptyHumans);
            }
        }
        catch (Exception ex)
        {
            string message = $"could not create file: {dbFilename}\n{ex}";
            Logger.LogError(message);
            return StatusCode(StatusCodes.Status500InternalServerError, message);
        }

        Models.Human[] humans = Load(dbFilename);

        int[] matchingIndexes = humans.Select((human, index) => (human, index))
            .Where(x => x.human.Name == newHuman.Name)
            .Select(x => x.index)
            .ToArray();

        if (matchingIndexes.Any())
        {
            humans[matchingIndexes.First()] = newHuman;
            Save(dbFilename, humans);
            return StatusCode(StatusCodes.Status201Created);
        }
        else
        {
            humans = humans.Append(newHuman).ToArray();
            Save(dbFilename, humans);
            return StatusCode(StatusCodes.Status200OK);
        }
    }

    public static void Save(string filePath, Models.Human[] humans)
    {
        var options = new JsonSerializerOptions() { WriteIndented = true };
        string json = JsonSerializer.Serialize(humans, options);
        System.IO.File.WriteAllText(filePath, json);
    }

    public static Models.Human[] Load(string filePath)
    {
        string json = System.IO.File.ReadAllText(filePath);
        Models.Human[] humans = JsonSerializer.Deserialize<Models.Human[]>(json) ?? throw new NullReferenceException();
        return humans;
    }
}
