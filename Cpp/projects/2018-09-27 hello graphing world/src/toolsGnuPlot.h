#ifndef TOOLSGNUPLOT_H_
#define TOOLSGNUPLOT_H_

#include <vector>
#include <windows.h> // XD

using namespace std;

void GpSaveData(vector<double> data, string filePath, double xSpacing = 1){
    // save data values from a vector as a text file ready to plot with gnuplot
    ofstream fb;
    fb.open(filePath.c_str());
    fb << "# data ready to display with gnuplot\n";

    char charBuffer[32];

    for (int i=0; i<data.size(); i++){
        double x = (double)i * xSpacing;
        snprintf(charBuffer, sizeof(charBuffer), "%f %f \n", x, data[i]);
        fb << charBuffer;
    }
    fb.close();
}

void GpRunScript(string scriptPath = "dataPlot.gp"){
    // run the gnuplot command on a pre-existing script
    string cmd = "gnuplot " + scriptPath;
    system(cmd.c_str());
}

#endif