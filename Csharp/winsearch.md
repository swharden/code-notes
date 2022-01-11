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

A full list with descriptions is here: https://docs.microsoft.com/en-us/windows/win32/properties/core-bumper




| Topic | Description |
|---------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [System.AcquisitionID](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-acquisitionid)<br/> | A hash value that indicates the acquisition session.<br/> |
| [System.ApplicationDefinedProperties](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-applicationdefinedproperties)<br/> | |
| [System.ApplicationName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-applicationname)<br/> | The name of the application that created this file or item. Do not use version numbers to identify the application's specific version.<br/> |
| [System.AppZoneIdentifier](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-appzoneidentifier)<br/> | Mark of the app container. The zone identifier as determined by the file's last writer.<br/> |
| [System.Author](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-author)<br/> | Represents the author or authors of the document.<br/> |
| [System.CachedFileUpdaterContentIdForConflictResolution](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-cachedfileupdatercontentidforconflictresolution)<br/> | |
| [System.CachedFileUpdaterContentIdForStream](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-cachedfileupdatercontentidforstream)<br/> | |
| [System.Capacity](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-capacity)<br/> | The amount of total storage space, expressed in bytes.<br/> |
| [System.Category](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-category)<br/> | Deprecated. The category that can be assigned to an item such as a document or file.<br/> |
| [System.Comment](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-comment)<br/> | The comment attached to a file, typically added by a user.<br/> |
| [System.Company](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-company)<br/> | The company or publisher.<br/> |
| [System.ComputerName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-computername)<br/> | The name of the computer where the item or file is located.<br/> |
| [System.ContainedItems](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-containeditems)<br/> | A list of the type of content in the item.<br/> |
| [System.ContentStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-contentstatus)<br/> | |
| [System.ContentType](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-contenttype)<br/> | |
| [System.Copyright](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-copyright)<br/> | The copyright information stored as a string.<br/> |
| [System.CreatorAppId](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-creatorappid)<br/> | The AppId of the application that created this file.<br/> |
| [System.CreatorOpenWithUIOptions](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-creatoropenwithuioptions)<br/> | Provides options that influence the behavior of UI controls that launch the file with the app specified in System.CreatorAppId.<br/> |
| [System.DataObjectFormat](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-dataobjectformat)<br/> | The data object format. A string value that is the clipboard format name.<br/> |
| [System.DateAccessed](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-dateaccessed)<br/> | Indicates the last time the item was accessed. The Indexing Service friendly name is "access".<br/> |
| [System.DateAcquired](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-dateacquired)<br/> | The acquisition date of the file or media.<br/> |
| [System.DateArchived](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-datearchived)<br/> | The date the file item was last archived.<br/> |
| [System.DateCompleted](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-datecompleted)<br/> | |
| [System.DateCreated](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-datecreated)<br/> | The date and time the item was created on the file system where it is currently located. <br/> |
| [System.DateImported](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-dateimported)<br/> | The date and time the file was imported into a private application database.<br/> |
| [System.DateModified](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-datemodified)<br/> | The date and time of the last modification to the item. The Indexing Service friendly name is 'write'.<br/> |
| [System.DefaultSaveLocationDisplay](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-defaultsavelocationdisplay)<br/> | Helps display as an icon whether or not a location is the default save location for owner and/or non-owners of a library<br/> |
| [System.DueDate](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-duedate)<br/> | |
| [System.EndDate](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-enddate)<br/> | |
| [System.ExpandoProperties](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-expandoproperties)<br/> | Properties that are not stored in the item itself, where the properties are in the form of a stream containing a SERIALIZEDPROPSTORAGE.<br/> |
| [System.FileAllocationSize](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fileallocationsize)<br/> | |
| [System.FileAttributes](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fileattributes)<br/> | The attributes of the item. These are equivalent to the values recognized in the **dwFileAttributes** member of the [**WIN32\_FIND\_DATA**](/windows/win32/api/minwinbase/ns-minwinbase-win32_find_dataa) structure.<br/> |
| [System.FileCount](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-filecount)<br/> | |
| [System.FileDescription](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-filedescription)<br/> | A user-friendly description of the file.<br/> |
| [System.FileExtension](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fileextension)<br/> | Identifies the file extension of the file-based item, including the leading period.<br/> |
| [System.FileFRN](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-filefrn)<br/> | The unique file ID, also known as the File Reference Number.<br/> |
| [System.FileName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-filename)<br/> | The file name, including its extension.<br/> |
| [System.FileOfflineAvailabilityStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fileofflineavailabilitystatus)<br/> | Null indicates the normal case (file is available offline). The partial case is only for folders where some content may be available offline and some may not.<br/> |
| [System.FileOwner](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fileowner)<br/> | The owner of the file, as known by the file system.<br/> |
| [System.FilePlaceholderStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fileplaceholderstatus)<br/> | Contains the placeholder file's status flags.<br/> |
| [System.FileVersion](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fileversion)<br/> | |
| [System.FindData](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-finddata)<br/> | Contains the [**WIN32\_FIND\_DATA**](/windows/win32/api/minwinbase/ns-minwinbase-win32_find_dataa) structure as a buffer of bytes. Do not use this property for any other purpose.<br/> |
| [System.FlagColor](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-flagcolor)<br/> | |
| [System.FlagColorText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-flagcolortext)<br/> | The user-friendly form of [System.FlagColor](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-flagcolor). This value is not intended to be parsed programmatically.<br/> |
| [System.FlagStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-flagstatus)<br/> | The status of a flag. Values: (0=none 1=white 2=Red). <br/> |
| [System.FlagStatusText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-flagstatustext)<br/> | The user-friendly form of [System.FlagStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-flagstatus). This value is not intended to be parsed programmatically.<br/> |
| [System.FolderKind](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-folderkind)<br/> | This property represents the types of content stored in this folder specified by the storage provider.Each folder type must be one of the known value specified by System.Kind definitionSystem.FolderKind is a readonly property, it should only be updated by the storage provider.<br/> |
| [System.FolderNameDisplay](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-foldernamedisplay)<br/> | This property is similar to System.ItemNameDisplay except it is only set for folders, for files it will be empty. This is useful to segregate files and folders by using this as the first sort key. When System.ItemDate is used as a second sort key it produces results with folders first ordered by name, then files ordered by date.<br/> |
| [System.FreeSpace](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-freespace)<br/> | The amount of free space in a volume, in bytes.<br/> |
| [System.FullText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-fulltext)<br/> | This property is used to specify search terms that should be applied as broadly as possible across all valid properties for the data source(s) being searched. It should not be emitted from a data source.<br/> |
| [System.HighKeywords](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-highkeywords)<br/> | The high confidence keywords for the item.<br/> |
| [System.ImageParsingName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-imageparsingname)<br/> | Image parsing name.<br/> |
| [System.Importance](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-importance)<br/> | |
| [System.ImportanceText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-importancetext)<br/> | The user-friendly form of [System.Importance](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-importance). This value is not intended to be parsed programmatically.<br/> |
| [System.IsAttachment](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isattachment)<br/> | Identifies whether the item is an attachment.<br/> |
| [System.IsDefaultNonOwnerSaveLocation](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isdefaultnonownersavelocation)<br/> | Identifies the default save location for a library for non-owners of the library.<br/> |
| [System.IsDefaultSaveLocation](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isdefaultsavelocation)<br/> | Identifies the default save location for a library for the owner of the library.<br/> |
| [System.IsDeleted](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isdeleted)<br/> | |
| [System.IsEncrypted](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isencrypted)<br/> | Identifies whether the item is encrypted.<br/> |
| [System.IsFlagged](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isflagged)<br/> | |
| [System.IsFlaggedComplete](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isflaggedcomplete)<br/> | |
| [System.IsIncomplete](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isincomplete)<br/> | Identifies whether the message was completely received. This value is used with some error conditions.<br/> |
| [System.IsLocationSupported](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-islocationsupported)<br/> | Identifies whether a location was indexed (locally or remotely) at the time it was added to the library.<br/> |
| [System.IsPinnedToNameSpaceTree](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-ispinnedtonamespacetree)<br/> | Identifies whether a shell folder is pinned to the navigation pane.<br/> |
| [System.IsRead](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isread)<br/> | Identifies whether the item has been read.<br/> |
| [System.IsSearchOnlyItem](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-issearchonlyitem)<br/> | Identifies whether a location or a library is search only.<br/> |
| [System.IsSendToTarget](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-issendtotarget)<br/> | Indicates whether an item is a valid SendTo target. This information is provided by certain Shell folders.<br/> |
| [System.IsShared](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-isshared)<br/> | Indicates whether the item is shared. This checks only the non-inherited ACLs.<br/> |
| [System.ItemAuthors](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemauthors)<br/> | Generic list of authors associated with an item. For example, the artist name for a music track is the item author.<br/> |
| [System.ItemClassType](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemclasstype)<br/> | Class type of the item.<br/> |
| [System.ItemDate](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemdate)<br/> | The primary date of interest for an item. In the case of photos, for example, this property maps to [System.Photo.DateTaken](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-photo-datetaken).<br/> |
| [System.ItemFolderNameDisplay](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemfoldernamedisplay)<br/> | The user-friendly display name of an item's parent folder.<br/> |
| [System.ItemFolderPathDisplay](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemfolderpathdisplay)<br/> | The user-friendly display path of an item's parent folder.<br/> |
| [System.ItemFolderPathDisplayNarrow](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemfolderpathdisplaynarrow)<br/> | The user-friendly display path of an item's parent folder.<br/> |
| [System.ItemName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemname)<br/> | The base name of the [System.ItemNameDisplay](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemnamedisplay) property.<br/> |
| [System.ItemNameDisplay](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemnamedisplay)<br/> | The display name in "most complete" form.<br/> |
| [System.ItemNameDisplayWithoutExtension](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemnamedisplaywithoutextension)<br/> | This is similar to System.ItemNameDisplay except that it never includes a file extension.<br/> |
| [System.ItemNamePrefix](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemnameprefix)<br/> | The prefix of an item, used for e-mail messages where the subject begins with the prefix "Re:".<br/> |
| [System.ItemNameSortOverride](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemnamesortoverride)<br/> | This string should be set to the phonetic version of the display name as defined in System.ItemNameDisplay in CJK locales(CHS Pinyin, JPN Hiragana, KOR Hangul, etc.). The first character of this field is also used for grouping names by firstletter. For most non-CJK languages, this field does not need to be set (in which case System.ItemNameDisplay will be used).However, if it is desirable to override the grouping letter (for example, to remove leading articles such as "a" and "the"),an alternate string can be provided here.<br/> |
| [System.ItemParticipants](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemparticipants)<br/> | The generic list of people associated with and contributing to an item.<br/> |
| [System.ItemPathDisplay](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itempathdisplay)<br/> | The user-friendly display path to the item.<br/> |
| [System.ItemPathDisplayNarrow](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itempathdisplaynarrow)<br/> | The user-friendly display path to the item.<br/> |
| [System.ItemSubType](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemsubtype)<br/> | Describes the sub-type of an item. The value is intended for display to the user.In contrast to System.ItemType, which is generally used to describe a class of itemsthat all have the same common content format, System.ItemSubType may differ based onthe individual contents or purpose of the item.For example, this property may be used to identify an item with System.ItemType = "jpg"as System.ItemSubType = "Panorama" or System.ItemSubType = "Smart Shot".<br/> |
| [System.ItemType](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemtype)<br/> | The canonical type of the item.<br/> |
| [System.ItemTypeText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemtypetext)<br/> | The user-friendly type name of the item.<br/> |
| [System.ItemUrl](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-itemurl)<br/> | Represents a well-formed URL that points to the item.<br/> |
| [System.Keywords](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-keywords)<br/> | The set of keywords (also known as "tags") assigned to the item.<br/> |
| [System.Kind](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-kind)<br/> | Maps extensions to various .Search folders.<br/> |
| [System.KindText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-kindtext)<br/> | The user-friendly form of [System.Kind](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-kind). This value is not intended to be parsed programmatically.<br/> |
| [System.Language](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-language)<br/> | The primary language of the file, particularly if that file is a document.<br/> |
| [System.LastSyncError](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-lastsyncerror)<br/> | |
| [System.LastWriterPackageFamilyName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-lastwriterpackagefamilyname)<br/> | Mark of the app container. The package family name of the last app to edit the file's contents.<br/> |
| [System.LowKeywords](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-lowkeywords)<br/> | The low confidence keywords for the item.<br/> |
| [System.MediumKeywords](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-mediumkeywords)<br/> | The medium confidence keywords for the item.<br/> |
| [System.MileageInformation](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-mileageinformation)<br/> | |
| [System.MIMEType](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-mimetype)<br/> | The MIME type.<br/> |
| [System.Null](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-null)<br/> | |
| [System.OfflineAvailability](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-offlineavailability)<br/> | |
| [System.OfflineStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-offlinestatus)<br/> | |
| [System.OriginalFileName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-originalfilename)<br/> | |
| [System.OwnerSID](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-ownersid)<br/> | SID of the user that owns the library.<br/> |
| [System.ParentalRating](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parentalrating)<br/> | The parental rating stored in a format typically determined by the organization named in [System.ParentalRatingsOrganization](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parentalratingsorganization). <br/> |
| [System.ParentalRatingReason](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parentalratingreason)<br/> | Explains file ratings. <br/> |
| [System.ParentalRatingsOrganization](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parentalratingsorganization)<br/> | The name of the organization whose rating system is used for [System.ParentalRating](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parentalrating).<br/> |
| [System.ParsingBindContext](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parsingbindcontext)<br/> | Used to get the [**IBindCtx**](/windows/win32/api/objidl/nn-objidl-ibindctx) for an item to be parsed.<br/> |
| [System.ParsingName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parsingname)<br/> | The Shell namespace name of an item relative to a parent folder.<br/> |
| [System.ParsingPath](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-parsingpath)<br/> | The Shell namespace path to the item.<br/> |
| [System.PerceivedType](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-perceivedtype)<br/> | The perceived file type based on its canonical type.<br/> |
| [System.PercentFull](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-percentfull)<br/> | The amount of space filled, as a percentage.<br/> |
| [System.Priority](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-priority)<br/> | |
| [System.PriorityText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-prioritytext)<br/> | The user-friendly form of [System.Priority](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-priority). This value is not intended to be parsed programmatically.<br/> |
| [System.Project](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-project)<br/> | |
| [System.ProviderItemID](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-provideritemid)<br/> | |
| [System.Rating](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-rating)<br/> | A rating system that uses integer values between 1 and 99. This is the rating system used by the Windows Vista Shell.<br/> |
| [System.RatingText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-ratingtext)<br/> | The user-friendly form of [System.Rating](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-rating). This value is not intended to be parsed programmatically.<br/> |
| [System.RemoteConflictingFile](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-remoteconflictingfile)<br/> | |
| [System.Sensitivity](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sensitivity)<br/> | |
| [System.SensitivityText](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sensitivitytext)<br/> | The user-friendly form of [System.Sensitivity](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sensitivity). This value is not intended to be parsed programmatically.<br/> |
| [System.SFGAOFlags](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sfgaoflags)<br/> | [**SFGAO**](../shell/sfgao) values as used in [**IShellFolder::GetAttributesOf**](/windows/win32/api/shobjidl_core/nf-shobjidl_core-ishellfolder-getattributesof).<br/> |
| [System.SharedWith](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sharedwith)<br/> | Indicates who the item is shared with.<br/> |
| [System.ShareUserRating](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-shareuserrating)<br/> | |
| [System.SharingStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sharingstatus)<br/> | Indicates the sharing status of an item: Not Shared, Shared, Everyone (homegroup or everyone), or Private.<br/> |
| [System.Shell.OmitFromView](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-shell-omitfromview)<br/> | Omits an item from Shell views.<br/> |
| [System.SimpleRating](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-simplerating)<br/> | A rating system that uses a range of integer values between 0 and 5.<br/> |
| [System.Size](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-size)<br/> | The system-provided file system size of the item, in bytes.<br/> |
| [System.SoftwareUsed](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-softwareused)<br/> | |
| [System.SourceItem](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sourceitem)<br/> | |
| [System.SourcePackageFamilyName](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-sourcepackagefamilyname)<br/> | Package family name of the app which the storage item instance originated.<br/> |
| [System.StartDate](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-startdate)<br/> | |
| [System.Status](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-status)<br/> | Generic status information applicable to the item.<br/> |
| [System.StorageProviderCallerVersionInformation](https://www.bing.com/search?q=System.StorageProviderCallerVersionInformation)<br/> | The storage provider caller protocol version information.The format of this property is provider specific, refer to the storage provider documentation for more information.<br/> |
| [System.StorageProviderError](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageprovidererror)<br/> | |
| [System.StorageProviderFileChecksum](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageproviderfilechecksum)<br/> | The checksum computed by the storage provider for the file. Files with the same checksum value will have the same contents.<br/> |
| [System.StorageProviderFileIdentifier](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageproviderfileidentifier)<br/> | The storage provider identifier for this file.<br/> |
| [System.StorageProviderFileRemoteUri](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageproviderfileremoteuri)<br/> | The storage provider's remote Uri for this file.<br/> |
| [System.StorageProviderFileVersion](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageproviderfileversion)<br/> | The storage provider file version for this file.<br/> |
| [System.StorageProviderFileVersionWaterline](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageproviderfileversionwaterline)<br/> | The storage provider computed file version waterline for this file. This value is used to detect if a file has changed.<br/> |
| [System.StorageProviderId](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageproviderid)<br/> | This property represents the \[Storage Provider ID\] part of the fully-qualified provider identifier"\[Storage Provider ID\]!\[Windows SID\]!\[Account ID\]".<br/> |
| [System.StorageProviderShareStatuses](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageprovidersharestatuses)<br/> | This property represents a list of share statuses for the file/folder specified by the storage provider.Each share status must be one of the known value specified by the enumerations belowStorageProviderShareStatuses is a readonly property, it should only be updated by the storage provider.<br/> |
| [System.StorageProviderSharingStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageprovidersharingstatus)<br/> | This property represents a the most permissive share status for the file/folder specified by the storage provider.The share statuses from most to least permissive are Owned > Co-owned > Public > Shared > Private.StorageProviderSharingStatus is a readonly property.<br/> |
| [System.StorageProviderStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-storageproviderstatus)<br/> | |
| [System.Subject](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-subject)<br/> | The subject of a document. This property maps to the OLE document property *Subject*.<br/> |
| [System.SyncTransferStatus](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-synctransferstatus)<br/> | |
| [System.Thumbnail](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-thumbnail)<br/> | Represents the thumbnail in VT\_CF format.<br/> |
| [System.ThumbnailCacheId](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-thumbnailcacheid)<br/> | A unique value used as a key to cache thumbnails.<br/> |
| [System.ThumbnailStream](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-thumbnailstream)<br/> | Data that represents the thumbnail in VT\_STREAM format, supported by Windows GDI+ and Windows codecs such as .jpg and .png.<br/> |
| [System.Title](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-title)<br/> | The title of the item.<br/> |
| [System.TitleSortOverride](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-titlesortoverride)<br/> | This optional string value allows for overriding the standard sort order of System.Title.This is very important for proper sorting of music files in Japanese which cannot becorrectly sorted phonetically (the user-expected ordering) without this field.It can also be used for customizing sorting in non-East Asian scenarios,such as allowing the user to remove articles for sorting purposes.<br/> |
| [System.TotalFileSize](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-totalfilesize)<br/> | |
| [System.Trademarks](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-trademarks)<br/> | The trademark associated with the item, in a string format.<br/> |
| [System.TransferOrder](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-transferorder)<br/> | |
| [System.TransferPosition](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-transferposition)<br/> | |
| [System.TransferSize](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-transfersize)<br/> | |
| [System.VolumeId](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-volumeid)<br/> | The GUID of the NTFS Volume.<br/> |
| [System.ZoneIdentifier](https://docs.microsoft.com/en-us/windows/win32/properties/props-system-zoneidentifier)<br/> | Mark of the Web zone, as URLZONE enumeration value.<br/> |



 
