# Parse Apache HTTP Log Files with C#

I use this class to quickly parse an Apache-style log line like this:

```
70.106.226.109 swharden.com - [22/Feb/2022:04:39:50 +0000] "GET /blog/2021-11-17-ndepend-badges/badges/issues-with-severity-critical.svg HTTP/2.0" 200 497 "https://swharden.com/" "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/98.0.4758.102 Safari/537.36" | TLSv1.3 | - - 1.002 - 0 NC:000000 UP:-DT
```

```cs
internal record LogRecord
{
    public string IP { get; init; } = string.Empty;
    public string Hostname { get; init; } = string.Empty;
    public DateTime DateTime { get; init; } = DateTime.MinValue;
    public string Method { get; init; } = string.Empty;
    public string Path { get; init; } = string.Empty;
    public string RequestType { get; init; } = string.Empty;
    public int ResponseCode { get; init; } = 0;
    public int ResponseSize { get; init; } = 0;
    public string Referrer { get; init; } = string.Empty;
    public string Agent { get; init; } = string.Empty;
    public string Tail { get; init; } = string.Empty;

    public static LogRecord FromLogLine(string line)
    {
        string[] parts = line.Split('"');

        if (parts.Length != 7)
            throw new InvalidOperationException("line must have six double quote characters");

        string[] partsZero = parts[0].Split(' ');
        string[] partsOne = parts[1].Split(' ');
        string[] partsTwo = parts[2].Trim().Split(' ');

        return new LogRecord()
        {
            IP = partsZero[0],
            Hostname = partsZero[1],
            DateTime = GetDateTime(parts),
            Method = partsOne[0],
            Path = partsOne.Length > 1 ? partsOne[1] : string.Empty,
            RequestType = partsOne.Length > 1 ? partsOne[2] : string.Empty,
            ResponseCode = int.Parse(partsTwo[0]),
            ResponseSize = int.Parse(partsTwo[1]),
            Referrer = parts[3],
            Agent = parts[5],
            Tail = parts[6],
        };
    }

    public static DateTime GetDateTime(string[] parts)
    {
        string dateRaw = parts[0].Split("[")[1].Split("+")[0];

        string[] dateStringParts = dateRaw.Split(":")[0].Split("/");
        string dateOnlyString = $"{dateStringParts[1]} {dateStringParts[0]} {dateStringParts[2]}";
        DateOnly dtOnly = DateOnly.Parse(dateOnlyString);

        string timeOnlyString = dateRaw.Split(":", 2)[1];
        TimeOnly tmOnly = TimeOnly.Parse(timeOnlyString);
        DateTime dt = dtOnly.ToDateTime(tmOnly);

        return dt;
    }
}
```
