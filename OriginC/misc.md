## Adding C files from the command window

https://www.originlab.com/doc/LabTalk/ref/Run-obj

```
run.LoadOC(OriginLab\fft_utils.c, 2048)
```

This command edits `%Y/Origin.ini`

## Common Tasks
```c

void swh_demo_common()
{
	// create some data
	int points = 10;
	vector<double> vX(points);
	vector<double> vY(points);
	vector<double> vYerr(points);
    for(int i = 0; i < vX.GetSize(); i++){
        vX[i] = i;
		vY[i] = i*i;
		vYerr[i] = i*1.23;
	}
	
	// create a an empty workbook (worhsheetpage)
	WorksheetPage wksPage;
	wksPage.Create("Origin");
	
	// by default there is one empty worksheet (with 2 columns)
	Worksheet wksOne = Project.ActiveLayer();
	
	// add an extra column
	wksOne.AddCol();
	wksOne.Columns(2).SetType(OKDATAOBJ_DESIGNATION_ERROR);
	
	// annotate columns
	wksOne.Columns(0).SetLongName("Xs");
	wksOne.Columns(1).SetLongName("Ys");
	wksOne.Columns(2).SetLongName("Yerr");
	
	// add a worksheet
	int wksTwoIndex = wksPage.AddLayer("SheetTwo");
	Worksheet wksTwo = wksPage.Layers(wksTwoIndex);

	// create datasets
	Dataset dsX;
	Dataset dsY;
	Dataset dsYerr;
	
	// attach datasets to worksheet
	dsX.Attach(wksOne,0);
	dsY.Attach(wksOne,1);
	dsYerr.Attach(wksOne,2);
	
	// fill dataset with data
	dsX = vX;
	dsY = vY;
	dsYerr = vYerr;
	
}
```
