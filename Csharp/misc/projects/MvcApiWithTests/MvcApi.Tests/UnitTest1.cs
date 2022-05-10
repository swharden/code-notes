using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using NUnit.Framework;
using System;

namespace MvcApi.Tests
{
    public class Tests
    {
        Controllers.HumansController HumansController = new(null!);

        private static Models.Human RandomHuman()
        {
            return new Models.Human()
            {
                Name = "Name" + Random.Shared.NextDouble().ToString().Replace(".", ""),
                Birthday = DateTime.Now + TimeSpan.FromDays(Random.Shared.Next(10_000)),
                FavoriteColor = "Color" + Random.Shared.NextDouble().ToString().Replace(".", ""),
            };
        }

        private static Models.Human[] GetHumans(Controllers.HumansController humansController, string dbFilePath)
        {
            IActionResult actionResult3 = humansController.Get(dbFilePath);
            Assert.IsInstanceOf<ObjectResult>(actionResult3);
            ObjectResult objectResult3 = (ObjectResult)actionResult3;

            if (objectResult3.Value is null)
                throw new NullReferenceException();

            return (Models.Human[])objectResult3.Value;
        }

        [SetUp]
        public void SetupControllerWithConsoleLogging()
        {
            using var logFactory = LoggerFactory.Create(builder => builder.AddConsole());
            var consoleLogger = logFactory.CreateLogger<Controllers.HumansController>();
            HumansController = new(consoleLogger);
        }

        [Test]
        public void Test_Human_NoDbFile()
        {
            IActionResult actionResult = HumansController!.Get("known-missing-name.json");
            Assert.IsInstanceOf<StatusCodeResult>(actionResult);
            StatusCodeResult codeResult = (StatusCodeResult)actionResult;

            Assert.AreEqual(StatusCodes.Status404NotFound, codeResult.StatusCode);
        }

        [Test]
        public void Test_Human_CorruptedDbFile()
        {
            System.IO.File.WriteAllText("bad-data.json", "asdfasdfasfdasdf");

            IActionResult actionResult = HumansController!.Get("bad-data.json");
            Assert.IsInstanceOf<ObjectResult>(actionResult);
            ObjectResult objectResult = (ObjectResult)actionResult;

            Assert.AreEqual(StatusCodes.Status500InternalServerError, objectResult.StatusCode);
        }

        [Test]
        public void Test_Human_DbCanBeAppended()
        {
            // start with blank database
            string dbFilePath = "test-data.json";
            Controllers.HumansController.Save(dbFilePath, Array.Empty<Models.Human>());

            Assert.IsEmpty(GetHumans(HumansController, dbFilePath));

            HumansController.Put(RandomHuman(), dbFilePath);

            Assert.IsNotEmpty(GetHumans(HumansController, dbFilePath));
        }
    }
}