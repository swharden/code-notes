# Azure Tables in Storage

```cs
class PackageStat : TableEntity
{
    public string PackageName { get; set; }
    public int DownloadCount { get; set; }
    public PackageStat(string packageName, int downloadCount, DateTime timeStamp)
    {
        PackageName = packageName;
        DownloadCount = downloadCount;
        PartitionKey = "partition1";
        RowKey = Guid.NewGuid().ToString();
        Timestamp = timeStamp;
    }
}
```

```cs
static void Main(string[] args)
{
    CloudStorageAccount cloudStorageAccount = CloudStorageAccount.Parse("SECRET");
    CloudTableClient tableClient = cloudStorageAccount.CreateCloudTableClient();
    CloudTable table = tableClient.GetTableReference("devtable");

    Random rand = new Random();
    PackageStat packageStat = new PackageStat("ScottPlot", rand.Next(12345), DateTime.UtcNow);
    TableOperation insertOrMergeOperation = TableOperation.InsertOrMerge(packageStat);
    TableResult result = table.Execute(insertOrMergeOperation);
    PackageStat insertedThing = result.Result as PackageStat;
    Console.WriteLine(insertedThing.PartitionKey);
    Console.WriteLine(insertedThing.RowKey);
}
```
