using BlazorApp5.Shared;
using Microsoft.AspNetCore.Mvc;

namespace BlazorApp5.Server.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class FolderController : ControllerBase
    {
        private readonly ILogger<WeatherForecastController> _logger;

        public FolderController(ILogger<WeatherForecastController> logger)
        {
            _logger = logger;
        }

        [HttpGet]
        public FolderContents Get(string? path)
        {
            path = path ?? "C:/";
            Console.WriteLine($"requesting contents of: {path}");
            return FolderContents.Scan(path);
        }
    }
}
