#include <iostream>
#include <vector>

#include "toolsTest.h"
#include "toolsVector.h"
#include "toolsInteraction.h"
#include "toolsGnuPlot.h"

using namespace std;

void Demo_00(){
    TestFunction();
}

void Demo_01(){
    // plot vector values to the console
    vector<double> data;
    data = NoisySin(100);
    VectorDisplay(data);
}

void Demo_02(){
    // save data to a .dat file then plot it by a .gp script
    vector<double> data;
    data = NoisySin(1000);
    GpSaveData(data, "output/data.dat");
    GpRunScript();
}

int main() 
{
    Demo_02();
    cout << "\nDONE\n";
    return 0;
}
