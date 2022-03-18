# Managing Secrets in C#

Consider using user secrets to load environment variables when a program starts
* https://dusted.codes/dotenv-in-dotnet

## User Secrets

* https://docs.microsoft.com/en-us/aspnet/core/security/app-secrets
* Secrets are not stored in the project folder
  * `C:\Users\%USERNAME%\AppData\Roaming\Microsoft\UserSecrets\GUID`
* Right-click the project and hit `Manage User Secrets`
* Or manage secrets from the command line
  * `dotnet user-secrets list`
  * `dotnet user-secrets set SecretKey SecretValue`

```json
{
  "FtpUsername": "someone@example.com",
  "FtpPassword": "s3cr3t123"
}
```

```cs
using System;
using Microsoft.Extensions.Configuration;

var config = new ConfigurationBuilder().AddUserSecrets<Program>().Build();

string username = config["FtpUsername"];
string password = config["FtpPassword"];

if (username is null || password is null)
    throw new InvalidOperationException("secrets not found");

Console.WriteLine($"Username: {username}");
Console.WriteLine($"Password: {password}");
```

```
Username: someone@example.com
Password: s3cr3t123
```

### FtpSecrets

I like to have a small object that contains secrets that I can pass around functions that need it

```cs
internal class FtpSecrets
{
    public readonly string Hostname;
    public readonly string Username;
    public readonly string Password;

    public FtpSecrets()
    {
        var config = new ConfigurationBuilder().AddUserSecrets<FtpSecrets>().Build();
        Hostname = config["hostname"];
        Username = config["username"];
        Password = config["password"];

        if (string.IsNullOrEmpty(Hostname))
            throw new InvalidOperationException("secret 'hostname' not found");

        if (string.IsNullOrEmpty(Username))
            throw new InvalidOperationException("secret 'username' not found");

        if (string.IsNullOrEmpty(Password))
            throw new InvalidOperationException("secret 'password' not found");
    }
}
```
