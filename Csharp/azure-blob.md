# Azure Blob Storage

```cs
BlobContainerClient container = new("CONNECTION_STRING", "$web");
BlobClient blob = container.GetBlobClient("demo.txt");

byte[] myData = /* demo data */;
using var stream = new MemoryStream(myData, writable: false);
blob.Upload(stream);
stream.Close();
```

```cs
private static StarRecord[] LoadStarRecords(BlobContainerClient container, string filename = "starRecords.json")
{
    BlobClient blob = container.GetBlobClient(filename);
    if (!blob.Exists())
	throw new InvalidOperationException($"file not found: {filename}");
    using MemoryStream stream = new();
    blob.DownloadTo(stream);
    string json = Encoding.UTF8.GetString(stream.ToArray());
    StarRecord[] records = IO.RecordsFromJson(json);
    return records;
}
```

```cs
private static void SaveStarRecords(StarRecord[] records, BlobContainerClient container, string filename = "starRecords.json")
{
    BlobClient blob = container.GetBlobClient(filename);
    string json = IO.RecordsToJson(records);
    byte[] bytes = Encoding.UTF8.GetBytes(json);
    using var stream = new MemoryStream(bytes, writable: false);
    blob.Upload(stream, overwrite: true);
    stream.Close();
}
```

## Outdated Methods

```cs
// read a blob file into a string
public static string ReadBlobText(string containerName, string fileName)
{
	string connectionString = Environment.GetEnvironmentVariable("AzureWebJobsStorage", EnvironmentVariableTarget.Process);
	CloudStorageAccount storageAccount = CloudStorageAccount.Parse(connectionString);
	CloudBlobClient blobClient = storageAccount.CreateCloudBlobClient();
	CloudBlobContainer container = blobClient.GetContainerReference(containerName);
	var thisBlob = container.GetBlockBlobReference(fileName);

	using var memoryStream = new MemoryStream();

	var blobRequestOptions = new BlobRequestOptions
	{
		ServerTimeout = TimeSpan.FromSeconds(30),
		MaximumExecutionTime = TimeSpan.FromSeconds(120),
		RetryPolicy = new ExponentialRetry(TimeSpan.FromSeconds(3), maxAttempts: 3),
	};

	thisBlob.DownloadToStream(memoryStream, null, blobRequestOptions);
	byte[] bytes = memoryStream.ToArray();
	string text = Encoding.Default.GetString(bytes);

	return text;
}
```

```cs
// append a string to an AppendBlob
public static void AppendBlob(string containerName, string fileName, string txt, bool lineBreakBefore = true)
{
	string connectionString = Environment.GetEnvironmentVariable("AzureWebJobsStorage", EnvironmentVariableTarget.Process);
	CloudStorageAccount storageAccount = CloudStorageAccount.Parse(connectionString);
	CloudBlobClient blobClient = storageAccount.CreateCloudBlobClient();
	CloudBlobContainer container = blobClient.GetContainerReference(containerName);
	CloudAppendBlob appendBlob = container.GetAppendBlobReference(fileName);
	if (!appendBlob.Exists())
		appendBlob.CreateOrReplace();
	if (lineBreakBefore)
		appendBlob.AppendText("\n");
	appendBlob.AppendText(txt);
}
```
