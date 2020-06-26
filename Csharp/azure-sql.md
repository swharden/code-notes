# Azure SQL Database

```cs
using SqlConnection conn = new SqlConnection(Environment.GetEnvironmentVariable("sqlConnString"));
conn.Open();

// read package list from the database
var packageNames = new List<string>();
using (SqlCommand sqlCmd = new SqlCommand("SELECT * FROM PackageStatsPackages", conn))
using (SqlDataReader reader = sqlCmd.ExecuteReader())
{
	while (reader.Read())
	{
		string packageName = (string)reader["PackageName"];
		packageNames.Add(packageName);
	}
}
log.LogInformation($"Database listed {packageNames.Count()} packages: " + string.Join(", ", packageNames));

// look up downloads for each package and build a query
string timestamp = DateTime.UtcNow.ToString();
StringBuilder sb = new StringBuilder();
foreach (var packageName in packageNames)
{
	int downloadsApi = GetDownloadsFromJson(packageName);
	int downloadsWeb = GetDownloadsFromHtml(packageName);
	sb.AppendLine($"INSERT INTO PackageStatsAPI VALUES ('{timestamp}', '{packageName}', {downloadsApi});");
	sb.AppendLine($"INSERT INTO PackageStatsWeb VALUES ('{timestamp}', '{packageName}', {downloadsWeb});");
	log.LogInformation($"NuGet package '{packageName}' has {downloadsApi} API and {downloadsWeb} web downloads");
}

// execute the query
using (SqlCommand sqlCmd = new SqlCommand(sb.ToString(), conn))
{
	int affectedRowCount = sqlCmd.ExecuteNonQuery();
	log.LogInformation($"affected {affectedRowCount} database rows");
}
```
