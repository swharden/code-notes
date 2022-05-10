using NUnit.Framework;
using System.IO;
using System;

namespace MyApi.Tests
{
    public class Tests
    {
        [Test]
        public void Test_Humans_GetBadPath_Returns404()
        {
            HttpResult resp = Humans.Get("does-not-exist.json");
            Assert.AreEqual(System.Net.HttpStatusCode.BadRequest, resp.StatusCode);
        }

        [Test]
        public void Test_Humans_GetPut_AddsHumans()
        {
            string filePath = Path.GetFullPath("humans-put-test.json");
            if (File.Exists(filePath))
                File.Delete(filePath);

            HttpResult resp1 = Humans.Get(filePath);
            Assert.AreEqual(System.Net.HttpStatusCode.BadRequest, resp1.StatusCode);

            Human human1 = new() { Name = "name1", Birthday = new(1, 2, 3), FavoriteColor = "blue" };
            HttpResult resp2 = Humans.Put(filePath, human1);
            Assert.AreEqual(System.Net.HttpStatusCode.OK, resp2.StatusCode);

            Human human2 = new() { Name = "name2", Birthday = new(4, 5, 6), FavoriteColor = "yellow" };
            HttpResult resp3 = Humans.Put(filePath, human2);
            Assert.AreEqual(System.Net.HttpStatusCode.OK, resp3.StatusCode);

            HttpResult resp4 = Humans.Put(filePath, human1);
            Assert.AreEqual(System.Net.HttpStatusCode.OK, resp4.StatusCode);

            HttpResult resp5 = Humans.Get(filePath);
            Assert.AreEqual(System.Net.HttpStatusCode.OK, resp5.StatusCode);

            Human[] humans = (Human[])resp5.Data!;
            Assert.IsNotNull(humans);
            Assert.IsNotEmpty(humans);
            Assert.AreEqual(2, humans.Length);
        }
    }
}