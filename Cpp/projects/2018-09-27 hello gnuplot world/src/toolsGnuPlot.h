#ifndef TOOLSGNUPLOT_H_
#define TOOLSGNUPLOT_H_

#include <vector>
#include <windows.h> // for system()
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

void GpRunCommand(string cmd){
    // execute a system command (Windows) and display time information
    cout << "System command: " + cmd + "\n";
    cout << "Running ...";
    clock_t start;
    double duration;
    start = std::clock();
    system(cmd.c_str());
    duration = 1000.0 * (clock() - start) / (double)CLOCKS_PER_SEC;
    cout << " complete (took " <<  duration << " ms)\n";
}

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

    cout << "Saved data to file: " + filePath + "\n";
}

void GpRunScript(string scriptPath = "dataPlot.gp"){
    // launch gnuplot to run a pre-existing script
    string cmd = "gnuplot " + scriptPath;
    cout << "Tasking gnuplot with script: " + scriptPath + "\n";
    GpRunCommand(cmd);
}

void GpPlotDataFileInteractive(string dataFile = "output/data.dat"){
    // plot data file interactively using a compiled-in gnuplot command
    string gpScript = "plot '" + dataFile + "' using 1:2";
    string gpCmd = "gnuplot -e \"" + gpScript + "\" -persist";
    GpRunCommand(gpCmd);
}


void GpPlotDataFilePNG(string dataFile = "output/data.dat", string saveAs = "output/data2.png"){
    // plot data file and save it to a PNG file using a compiled-in gnuplot command
    string gpScript;
    gpScript += "set terminal png size 400,300; ";
    gpScript += "set output '" + saveAs + "'; ";
    gpScript += "plot '" + dataFile + "' using 1:2;";
    string gpCmd = "gnuplot -e \"" + gpScript + "\"";
    GpRunCommand(gpCmd);
}


#endif