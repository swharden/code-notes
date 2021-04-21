# Azure Tables in Storage

```cs
// NuGet
// Microsoft.Azure.Cosmos
// Microsoft.Azure.Cosmos.Table
```

```cs
class PackageStat : TableEntity
{
    public string Package { get; set; }
    public int Downloads { get; set; }
    public PackageStat()
    {
        PartitionKey = "partition1";
        RowKey = Guid.NewGuid().ToString();
    }
}
```

```cs
static void Main(string[] args)
{
    CloudStorageAccount cloudStorageAccount = CloudStorageAccount.Parse("SECRET");
    CloudTableClient tableClient = cloudStorageAccount.CreateCloudTableClient();
    CloudTable table = tableClient.GetTableReference("devtable");
    table.CreateIfNotExists();

    Random rand = new Random();
    PackageStat packageStat = new PackageStat()
    {
        Package = "ScottPlot",
        Downloads = rand.Next(12345),
        Timestamp = DateTime.UtcNow
    };

    TableOperation insertOrMergeOperation = TableOperation.InsertOrMerge(packageStat);
    TableResult result = table.Execute(insertOrMergeOperation);
    PackageStat insertedThing = result.Result as PackageStat;

    IQueryable<PackageStat> items = table.CreateQuery<PackageStat>().Where(x => x.Package == "ScottPlot");
    foreach (var item in items)
    {
        Console.WriteLine(item.Downloads);
    }
}
```

### Batch Operations
```cs
/// <summary>
/// Insert many items table storage in a single operation
/// </summary>
public static void AddGrabResults(GrabResult[] grabs)
{
    CloudStorageAccount storageAccount = CloudStorageAccount.Parse(Cloud.GetStorageConnectionString());
    CloudTableClient tableClient = storageAccount.CreateCloudTableClient();

    CloudTable table = tableClient.GetTableReference("GrabResults");
    table.CreateIfNotExists();

    TableBatchOperation batchOperation = new();
    foreach (GrabResult grab in grabs)
        batchOperation.Insert(grab);
    table.ExecuteBatch(batchOperation);
}
```
