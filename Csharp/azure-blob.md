# Azure Blob Storage

```cs
// read a blog file into a string
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
