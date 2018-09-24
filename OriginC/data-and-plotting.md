# Data and Plotting

## Create a workbook for a vector ready to plot
```
void ShowTrace(vector<double> vectorToGraph, double xOffset){
  // utility function to quickly create a new worksheet with data suitable for graphing.

  // create a new worksheet
  WorksheetPage wksPage;
  wksPage.Create("Origin");
  Worksheet wks = Project.ActiveLayer();

  // fill Y column with vee data
  Column colY = wks.Columns(1);
  vector<double>& dataY = colY.GetDataObject();
  dataY = vectorToGraph;

  // fill X column with points
  Column colX = wks.Columns(0);
  vector<double> valuesX(dataY.GetSize());
  for (int i=0; i<dataY.GetSize(); i++){
    valuesX[i] = i+xOffset;
  }
  vector<double>& dataX = colX.GetDataObject();
  dataX = valuesX;
}
```
