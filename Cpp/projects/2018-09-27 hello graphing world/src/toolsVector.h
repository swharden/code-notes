#ifndef TOOLSVECTOR_H_
#define TOOLSVECTOR_H_

#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void VectorDisplay(vector<double> data){
    for (int i=0; i<data.size(); i++){
        printf("[%d] %f\n", i, data[i]);
    }
}

vector<double> NoisySin(int points, int cycles = 3, double noiseLevel=.2){
    // return a sine wave with random noise in it
    vector<double> data(points);
    for (int i=0; i<points; i++){
        float noise = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        double sinThis = (double)i / points;
        sinThis *= 3.14159 * 2;
        sinThis *= cycles;
        data[i] = sin(sinThis) + noise * noiseLevel;
    }
    return data;
}


void VectorWriteFile(vector<double> data, string filePath, double xSpacing = 1){

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

#endif