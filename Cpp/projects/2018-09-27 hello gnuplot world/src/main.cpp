/* The "hello world" of gnuplot graphing in CPP - by Scott Harden
 * 
 * This file demonstrates how to create gnuplot graphs using cpp 
 * and only the standard library. It's a bit inelegant, but it's
 * simple. All three methods work by saving data into a text file
 * then having gnuplot plot the text file. The three ways to launch
 * gnuplot from cpp are:
 * 
 * Option 1 - have gnuplot execute a .gp script
 *   This seems like the most flexible option. You can simply run
 *   the command line program "gnuplot scriptfile.gp" and whatever
 *   is in the script gets executed. This means graph sizes and
 *   styles are not compiled-in, so they're easy to change. This
 *   demo saves the output as a PNG file.
 * 
 * Option 2 - launch gnuplot interactively
 *   You can send gnuplot commands with the -e argument. Send a
 *   bunch of commands followed by the -persist argument, and when
 *   the command is run the main program will hang while an
 *   interactive gnuplot windows runs. This is great to quickly
 *   display data to the user in an interactive way. A downside
 *   is that styling commands are compiled-in, but this method could
 *   be used in combination with a flat file script.
 * 
 * Option 3 - launch gnuplot with only command-line arguments
 *   This option is the simpest way to go from data to PNG file.
 *   All styling is done with command line arguments, and these
 *   are compiled-in. Configure for PNG output and this is a simple
 *   way to plot data as an image.
 * 
 */

#include <iostream>
#include <vector>

#include "toolsVector.h"
#include "toolsGnuPlot.h"

using namespace std;

void Demo_01(){
    // Generate some data and display it to the console
    vector<double> data;
    data = NoisySin(100);
    VectorDisplay(data);
}

void Demo_02_data_file_gnuplot_script(){
    // Plot some data by saving it to file and running a gnuplot script.
    // This could be done all from the command-line, but calling a script
    // lets the user customize the look of the graph without recompiling.
    vector<double> data;
    data = NoisySin(1000, 2);
    GpSaveData(data, "output/data.dat");
    GpRunScript("dataPlot.gp");
}

void Demo_03_data_file_gnuplot_interactive(){
    // Display an interactive gnuplot by saving data to a file then launching
    // gnuplot with all its plotting styles defined as command line arguments.
    vector<double> data;
    data = NoisySin(1000, 3);
    GpSaveData(data, "output/data.dat");
    GpPlotDataFileInteractive("output/data.dat");
}

void Demo_04_data_file_gnuplot_save(){
    // Launch gnuplot using a compiled-in command to plot data from the data
    // file and save the plot as a PNG without launching an interactive window
    vector<double> data;
    data = NoisySin(1000, 3);
    GpSaveData(data, "output/data.dat");
    GpPlotDataFilePNG("output/data.dat", "output/data2.png");
}

int main()
{
    Demo_02_data_file_gnuplot_script();
    Demo_03_data_file_gnuplot_interactive();
    Demo_04_data_file_gnuplot_save();
    cout << "\nDONE\n";
    return 0;
}
