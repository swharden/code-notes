# Azure Cosmos DB

```cs
class PackageStat
{
    public string PackageName;
    public DateTime UtcTimeStamp;
    public int Downloads;
    public Guid id = Guid.NewGuid();
}

static async System.Threading.Tasks.Task Main(string[] args)
{
    string SECRET_CONN_STR = "asdfasdfasdf";
    CosmosClient client = new CosmosClient(SECRET_CONN_STR);
    Database database = client.GetDatabase("devdb");
    Container container = database.GetContainer("devcontainer");

    // Create an item
    Random rand = new Random();
    PackageStat testItem = new PackageStat()
    {
        PackageName = "ScottPlot",
        UtcTimeStamp = DateTime.UtcNow,
        Downloads = rand.Next(12345),
    };

    ItemResponse<PackageStat> result = await container.CreateItemAsync(testItem);
}
```
