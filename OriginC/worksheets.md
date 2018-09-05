# Worksheets
* https://www.originlab.com/doc/OriginC/guide/Worksheet-Basic-Operation
* https://www.originlab.com/doc/OriginC/ref/Worksheet-Class


## Get Active WorkBook/WorkSheet
```
Worksheet wks = Project.ActiveLayer();
WorksheetPage wksPage = wks.GetPage();
string workSheetName = wks.GetName();
string workBookName = wksPage.GetName();
printf("[%s]%s",workBookName,workSheetName);
```
