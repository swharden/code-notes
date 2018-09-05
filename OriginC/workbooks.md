# Workbooks
* https://www.originlab.com/doc/OriginC/guide/Basic-Workbook-Operation

## Loop Through Workbooks
```c
foreach(WorksheetPage wksPage in Project.WorksheetPages)
{
    out_str(wksPage.GetName());
}
```
