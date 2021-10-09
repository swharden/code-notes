# FTP with Csharp

## WebClient (FTP)

```cs
using System;
using System.IO;
using System.Net;

string host = "swharden.com";
string username = "scott";
string password = "secret123";

if (host.Contains(":"))
	host = host.Split(":")[1];
host = "ftp://" + host.TrimStart('/');

FtpWebRequest ftpRequest = (FtpWebRequest)WebRequest.Create(host);
ftpRequest.Credentials = new NetworkCredential(username, password);
ftpRequest.Method = WebRequestMethods.Ftp.ListDirectory; // ACTION GOES HERE

using FtpWebResponse response = (FtpWebResponse)ftpRequest.GetResponse();
using Stream responseStream = response.GetResponseStream();
using StreamReader streamReader = new StreamReader(responseStream);

string line = streamReader.ReadLine();
while (!string.IsNullOrEmpty(line))
{
	Console.WriteLine(">>> " + line);
	line = streamReader.ReadLine();
}
```

## WebClient (FTPS)
```cs
using System;
using System.IO;
using System.Net;

string host = "swharden.com";
string username = "scott";
string password = "secret123";

if (host.Contains(":"))
	host = host.Split(":")[1];
host = "ftp://" + host.TrimStart('/');

// disable certificate verification
ServicePointManager.ServerCertificateValidationCallback += (o, c, ch, er) => true;

FtpWebRequest ftpRequest = (FtpWebRequest)WebRequest.Create(host);
ftpRequest.EnableSsl = true; // FTPS
ftpRequest.Credentials = new NetworkCredential(username, password);
ftpRequest.Method = WebRequestMethods.Ftp.ListDirectory; // ACTION GOES HERE

using FtpWebResponse response = (FtpWebResponse)ftpRequest.GetResponse();
using Stream responseStream = response.GetResponseStream();
using StreamReader streamReader = new StreamReader(responseStream);

string line = streamReader.ReadLine();
while (!string.IsNullOrEmpty(line))
{
	Console.WriteLine(">>> " + line);
	line = streamReader.ReadLine();
}
```

## FluentFTP (FTPS)
```cs
using System;
using FluentFTP;

using var client = new FtpClient("example.com", "user", "password");
client.EncryptionMode = FtpEncryptionMode.Explicit;
client.ValidateAnyCertificate = true;
client.Connect();

foreach (FtpListItem item in client.GetListing("/"))
{
	if (item.Type == FtpFileSystemObjectType.File)
	{
		Console.WriteLine($"File: {item.FullName}");
	}
	else
	{
		Console.WriteLine($"Fldr: {item.FullName}");
	}
}

if (!client.DirectoryExists("/randomFolders"))
	client.CreateDirectory("/randomFolders");

if (!client.DirectoryExists("/randomFiles"))
	client.CreateDirectory("/randomFiles");

string folderPath = $"/randomFolders/random-{Guid.NewGuid()}";
Console.WriteLine($"Creating {folderPath}");
client.CreateDirectory(folderPath);

string filePath = $"/randomFiles/random-{Guid.NewGuid()}.txt";
string filename = Path.GetFileName(filePath);
File.WriteAllText(filename, "test123");
Console.WriteLine($"Uploading {filePath}");
client.UploadFile(filename, filePath);
```
