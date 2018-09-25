# Workbooks
* https://www.originlab.com/doc/OriginC/guide/Basic-Workbook-Operation
* https://www.originlab.com/doc/OriginC/ref/WorksheetPage
* https://www.originlab.com/doc/OriginC/ref/Page-AddLayer

## Concepts
* A workbook is a `WorksheetPage`
* workbooks can have duplicate long names
* workbooks must have unique names (project wide!)

## Creating
https://www.originlab.com/doc/OriginC/ref/Page-Create

```c
// create an empty workbook with an empty sheet
WorksheetPage wksPg;
wksPg.Create("");
```

```c
// create an empty workbook with a standard X and Y column
WorksheetPage wksPg;
wksPg.Create("Origin");
```

## Loop Through Workbooks
```c
foreach(WorksheetPage wksPage in Project.WorksheetPages)
{
    out_str(wksPage.GetName());
}
```

```c
void DeleteAllWorkbooks(){
	foreach(WorksheetPage wksPage in Project.WorksheetPages)
		wksPage.Destroy();
}
```

## Get Active WorkBook/WorkSheet
```
Worksheet wks = Project.ActiveLayer();
WorksheetPage wksPage = wks.GetPage();
string workSheetName = wks.GetName();
string workBookName = wksPage.GetName();
printf("[%s]%s",workBookName,workSheetName);
```
