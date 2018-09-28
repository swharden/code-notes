#include <vector>
#include <fstream>
#include <sstream>

#include "fileTools.h"

void DataWrite(vector<double> data, double xSpacing = 1){
    ofstream fb;
    fb.open("data.dat");
    fb << "# data ready to display with gnuplot\n";

    char charBuffer[32];

    for (int i=0; i<data.size(); i++){
        double x = (double)i * xSpacing;
        snprintf(charBuffer, sizeof(charBuffer), "%f %f \n", x, data[i]);
        fb << charBuffer;
    }
    fb.close();
}
