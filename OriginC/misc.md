## Timers

> If you want to use built in timer in labtalk you can type ‘sec’ in the command window onces.  Then type ‘watch’. You can the run ‘watch’ repeatedly without typing sec each time to get time since last watch command. There is also a way to do that in C. -JF

```c
// something like
DWORD dwBegin=GetTickCount();
DWORD dwEnd=GetTickCount();
printf("\n  Total RunTime: %3.2f seconds.\n",(dwEnd-dwBegin)/1000.00);
```

## Adding C files from the command window

https://www.originlab.com/doc/LabTalk/ref/Run-obj

```
run.LoadOC(OriginLab\fft_utils.c, 2048)
```

This command edits `%Y/Origin.ini`

## Common Tasks
```c

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
  ```
