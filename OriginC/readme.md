# OriginC Code Examples

## Workbook Operations
* Workbooks are `WorksheetPage` objects
* Duplicate long names are OK but short names must be unique project wide

### Links
* https://www.originlab.com/doc/OriginC/guide/Basic-Workbook-Operation
* https://www.originlab.com/doc/OriginC/ref/WorksheetPage
* https://www.originlab.com/doc/OriginC/ref/Page-AddLayer
* https://www.originlab.com/doc/OriginC/ref/Page-Create

### Code Examples

```c
void BookActivate(string bookName, bool inActiveFolder = true){
	// activate a workbook by name (partial matches supported)
	foreach(WorksheetPage wksPage in Project.WorksheetPages){
		if (stringContains(wksPage.GetLongName(), bookName, false)){
			if (inActiveFolder){
				string folderPathActive = FolderFullPath(FolderActive());
				string folderPathThisNote = FolderFullPath(wksPage.GetFolder());
				if (folderPathActive != folderPathThisNote)
					continue;
			} 
			wksPage.SetShow(PAGE_ACTIVATE);  // Activate the workbook
		}
	}
}
```

```c
// display the active workbook and worksheet
Worksheet wks = Project.ActiveLayer();
WorksheetPage wksPage = wks.GetPage();
string workSheetName = wks.GetName();
string workBookName = wksPage.GetName();
printf("[%s]%s",workBookName,workSheetName);
```

```c
void BooksClear(){
	// delete every workbook in the project
	foreach(WorksheetPage wksPage in Project.WorksheetPages){
		wksPage.Destroy();
	}
}
```

```c
WorksheetPage BookWithLongName(string bookName){
	// return the workbook whose long name matches the string
	foreach(WorksheetPage wksPage in Project.WorksheetPages){
		if (wksPage.GetLongName()==bookName){
			return wksPage;
		}
	}
	
	// return a null workbook if no match is found
	WorksheetPage wksPageNull;
	return wksPageNull;
}
```

```c
WorksheetPage BookCreate(string bookName){
	// create a new workbook and return it
	WorksheetPage wksPage;
	wksPage.Create(NULL, CREATE_VISIBLE | CREATE_EMPTY );
	wksPage.SetLongName(bookName);
	return wksPage;
}

```

```c
WorksheetPage BookGetOrCreate(string bookName){
	// if a workbook by the name exists return it, otherwise create it
	WorksheetPage wksPage;
	wksPage = BookWithLongName(bookName);
	if (wksPage) {	
		return wksPage;
	} else {
		wksPage = BookCreate(bookName);
		return wksPage;
	}
}
```

## Worksheet Operations
* `Worksheet` objects are really `Layer` objects of `WorksheetPage` objects (I think?)

### Links
* https://www.originlab.com/doc/OriginC/guide/Worksheet-Basic-Operation
* https://www.originlab.com/doc/OriginC/ref/Worksheet-Class
* https://www.originlab.com/doc/OriginC/ref/Page-AddLayer

### Code Examples

```c
Worksheet SheetWithName(WorksheetPage wksPage, string sheetName){
	// return the worksheet whose name matches the string
	foreach (Layer lyr in wksPage.Layers){
		Worksheet thisWks = lyr;
		if (thisWks.GetName()==sheetName){
			return thisWks;
		}
	}
	
	// return a null worksheet if no match is found
	Worksheet thisWksNull;
	return thisWksNull;
}
```

```c
Worksheet SheetGetOrCreate(WorksheetPage wksPage, string sheetName){
	// return the worksheet with the given name, and creating it if it doesn't exist
	Worksheet wks = SheetWithName(wksPage, sheetName);
	if (wks){
		return wks;
	} else {
		int layer = wksPage.AddLayer(sheetName);
		Worksheet wksNew = wksPage.Layers(layer);
		return wksNew;	
	}	
}
```

# Column Operations

### Links
* https://www.originlab.com/doc/OriginC/guide/Worksheet-Column-Operation

### Code Examples

```c
void ColumnsEnsureCount(Worksheet wks, int columnCount){
	// add columns to the worksheet until the count is reached
	int columnsNeeded = columnCount - wks.Columns.Count();
	while (columnsNeeded--){
		wks.AddCol();
	}
}
```

```c
void ColumnsClear(Worksheet wks){
	// delete all columns in the worksheet
	int colsToDelete = wks.Columns.Count();
	while (colsToDelete--){
		wks.Columns(0).Destroy();
	}
}
```

```c
Column ColumnAdd(Worksheet wks, string longName="", string units="", string comments="", string type="Y"){
	// add a column to the given worksheet
	int columnIndex = wks.AddCol();
	Column col = wks.Columns(columnIndex);
	col.SetLongName(longName);
	col.SetUnits(units);
	col.SetComments(comments);
	type.MakeUpper();
	if (type=="X")
		col.SetType(OKDATAOBJ_DESIGNATION_X);
	else if (type=="Y")
		col.SetType(OKDATAOBJ_DESIGNATION_Y);
	else if (type=="ERR")
		col.SetType(OKDATAOBJ_DESIGNATION_ERROR);
	return col;
}
```

```c
void ColumnFillAscending(Column col, int count=100, double mult=1, double offset=0){
	// fill the column with ascending numbers
	vector<double> data(count);
	for (int i=0; i<data.GetSize(); i++){
		data[i] = (i * mult) + offset;
	}
	vector<double>& colDataObj = col.GetDataObject();
	colDataObj = data;	
}
```

```c
void ColumnFillRandom(Column col, int count=100, double low=0, double high=1){
	// fill the column with random numbers (between low and high)
	vector<double> data(count);
	unifrnd(data, data.GetSize(), low, high); 	
	vector<double>& colDataObj = col.GetDataObject();
	colDataObj = data;	
}
```

## Notes Pages

### Links
* https://www.originlab.com/doc/OriginC/ref/Note
* https://www.originlab.com/doc/OriginC/ref/Note-Note

### Code Examples

```c
// create a new notes page and fill it with text
Note note;
note.Create();
note.SetLongName("this note is too cool for you", true, true);
note.TitleShow = WIN_TITLE_SHOW_BOTH;  
note.Text = "are you noting this?";
```

```c
Note NoteWithName(string noteName, bool inActiveFolder = true){
	// return the note whose long name matches the string
	foreach (Note note in Project.Notes){
		if (note.GetLongName()==noteName){
			if (inActiveFolder){
				string folderPathActive = FolderFullPath(FolderActive());
				string folderPathThisNote = FolderFullPath(note.GetFolder());
				if (folderPathActive != folderPathThisNote)
					continue;
			}
			return note;
		}
	}
	
	// return a null note if no match is found
	Note noteNull;
	return noteNull;
}
```

```c
Note NoteGetOrCreate(string noteName, bool inActiveFolder = true){
	// return the note page with the given name, creating it if it doesn't exist
	Note note = NoteWithName(noteName, inActiveFolder);
	if (note){
		return note;
	} else {
		note.Create();
		note.SetLongName(noteName, true, true);
		note.TitleShow = WIN_TITLE_SHOW_BOTH;
		return note;
	}
}
```

```c
void NoteClear(string noteName){
	// clear the contents of a note page
	Note note = NoteWithName(noteName);
	note.Text = "";
}
```

```c
void NoteAppend(string noteName, string message, bool breakBefore = true){
	// append a string to the end of a note page
	Note note = NoteWithName(noteName);
	if (breakBefore)
		message = "\n"+message;
	note.Text += message;
}
```

## Misc

```c
void DemoEverything(){
	// demonstrate uses of many of the functions on this page
	BooksDeleteAll();
	WorksheetPage wksPage = BookGetOrCreate("demoBook");
	Worksheet wks = SheetGetOrCreate(wksPage, "demoSheet");
	Column colX = wks.Columns(0);
	Column colY = wks.Columns(1);
	ColumnFillAscending(colX, 20, 5, -110);
	ColumnFillRandom(colY, 20, -10, 10);
}
```

```c
void CreateFakeMemtestBook(int sheetCount = 10){
	// use functions on this page to create something that looks like a thick book of memtests
	
	DWORD timerStart=GetTickCount();
	
	WorksheetPage wksPage = BookGetOrCreate("FakeMemtest");
	
	for (int sheetNumber = 0; sheetNumber < sheetCount; sheetNumber++){
		string abfID = StringRandomNumbers(8);
		Worksheet wks = SheetGetOrCreate(wksPage, abfID);
		ColumnsClear(wks);
		
		double sweepLength = 1.0/30;
		int sweepCount = 20;
		
		Column colTime = ColumnAdd(wks, "Time", "min", "", "X");
		ColumnFillAscending(colTime, sweepCount, sweepLength);
		
		Column colIh = ColumnAdd(wks, "Ih", "pA");
		ColumnFillRandom(colIh, sweepCount, sweepLength);
			
		Column colRa = ColumnAdd(wks, "Ra", "MOhm");
		ColumnFillRandom(colRa, sweepCount, sweepLength);
		
		Column colRm = ColumnAdd(wks, "Rm", "MOhm");
		ColumnFillRandom(colRm, sweepCount, sweepLength);
	}
	
	DWORD timerEnd=GetTickCount();
	printf("Timer took: %3.3f seconds.\n",(timerEnd-timerStart)/1000.00);

}
```
