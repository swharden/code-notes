# Search a Windows Indexed Filesystem with C#

Walking directories can be slow, but Windows often indexes drives to enable fast _Windows Search_. Queries can be run directly against the indexed database for extremely fast walking/searching.

```cs
/// <summary>
/// Return an array of all files matching the search pattern.
/// Note that indexing may not be enabled for every folder on a drive.
/// </summary>
public static string[] FindIndexedFiles(string basePath = "C:/", string searchPattern = "*.log")
{
    basePath = System.IO.Path.GetFullPath(basePath);
    searchPattern = searchPattern.Replace("*", "%");
    string query = "SELECT System.ItemPathDisplay FROM SystemIndex " +
                   $"WHERE scope ='file:{basePath}' " +
                   $"AND System.ItemName LIKE '{searchPattern}'";
    Console.WriteLine(query);

    using OleDbConnection connection = new(@"Provider=Search.CollatorDSO;Extended Properties=""Application=Windows""");
    connection.Open();
    using OleDbCommand command = new(query, connection);
    using OleDbDataReader reader = command.ExecuteReader();

    List<string> paths = new();
    while (reader.Read())
        paths.Add(reader.GetString(0));

    connection.Close();

    return paths.ToArray();
}
```

## Windows Search Columns
System.Author
System.Category
System.Comment
System.Company
System.ComputerName
System.ContentStatus
System.ContentType
System.Copyright
System.DateAccessed
System.DateAcquired
System.DateArchived
System.DateCompleted
System.DateCreated
System.DateImported
System.DateModified
System.DueDate
System.EndDate
System.FileAttributes
System.FileDescription
System.FileExtension
System.FileName
System.FileOwner
System.ItemAuthors
System.ItemDate
System.ItemFolderNameDisplay
System.ItemFolderPathDisplay
System.ItemFolderPathDisplayNarrow
System.ItemName
System.ItemNameDisplay
System.ItemNamePrefix
System.ItemParticipants
System.ItemPathDisplay
System.ItemPathDisplayNarrow
System.ItemType
System.ItemTypeText
System.ItemUrl
System.Keywords
System.Kind
System.SourceItem
System.StartDate
System.Status
System.Subject
System.ThumbnailCacheId
System.Title

### Search-Specific Columns
System.Search.AutoSummary
System.Search.Contents
System.Search.EntryID
System.Search.GatherTime
System.Search.Rank
System.Search.Store

### Document-Specific Columns
System.Document.ByteCount
System.Document.ByteCount
System.Document.CharacterCount
System.Document.CharacterCount
System.Document.ClientID
System.Document.ClientID
System.Document.Contributor
System.Document.Contributor
System.Document.DateCreated
System.Document.DateCreated
System.Document.DatePrinted
System.Document.DatePrinted
System.Document.DateSaved
System.Document.DateSaved
System.Document.Division
System.Document.Division
System.Document.DocumentID
System.Document.DocumentID
System.Document.HiddenSlideCount
System.Document.HiddenSlideCount
System.Document.LastAuthor
System.Document.LastAuthor
System.Document.LineCount
System.Document.LineCount
System.Document.Manager
System.Document.Manager
System.Document.PageCount
System.Document.PageCount
System.Document.ParagraphCount
System.Document.ParagraphCount
System.Document.PresentationFormat
System.Document.PresentationFormat
System.Document.RevisionNumber
System.Document.RevisionNumber
System.Document.SlideCount
System.Document.SlideCount
System.Document.TotalEditingTime
System.Document.TotalEditingTime
System.Document.WordCount
System.Document.WordCount
