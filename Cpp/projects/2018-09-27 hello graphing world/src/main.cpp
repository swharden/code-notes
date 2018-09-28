#include <iostream>
#include <vector>

#include "toolsTest.h"

using namespace std;

void PauseBeforeClosing(){
    cout << "\npress ENTER to exit...";
    cin.get();
}

void Demo_00(){
    TestFunction();
}

void Demo_01(){
    vector<double> data;
    //data = NoisySin(100);
    //VectorDisplay(data);
    //DataWrite(data);
}

int main() 
{
    Demo_00();
    PauseBeforeClosing();
    return 0;
}
