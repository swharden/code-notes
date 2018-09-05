# Worksheets
* https://www.originlab.com/doc/OriginC/guide/Worksheet-Basic-Operation
* https://www.originlab.com/doc/OriginC/ref/Worksheet-Class

## Loop Through Worksheets
```c
	Worksheet wks = Project.ActiveLayer();
	WorksheetPage wksPage = wks.GetPage();
	foreach (Layer lyr in wksPage.Layers){
		Worksheet thisWks = lyr;
		out_str(thisWks.GetName());
	}
```

## Get Active WorkBook/WorkSheet
```c
Worksheet wks = Project.ActiveLayer();
WorksheetPage wksPage = wks.GetPage();
string workSheetName = wks.GetName();
string workBookName = wksPage.GetName();
printf("[%s]%s",workBookName,workSheetName);
```
