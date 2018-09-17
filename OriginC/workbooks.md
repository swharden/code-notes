# Workbooks
* https://www.originlab.com/doc/OriginC/guide/Basic-Workbook-Operation
* https://www.originlab.com/doc/OriginC/ref/WorksheetPage

## Loop Through Workbooks
```c
foreach(WorksheetPage wksPage in Project.WorksheetPages)
{
    out_str(wksPage.GetName());
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
