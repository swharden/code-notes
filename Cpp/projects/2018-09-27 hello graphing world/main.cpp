#include <iostream>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void VectorDisplay(vector<double> data){
    for (int i=0; i<data.size(); i++){
        printf("[%d] %f\n", i, data[i]);
    }
}

vector<double> NoisySin(int points){
    vector<double> data(points);
    for (int i=0; i<points; i++){
        data[i]=sin((double)i/100);
    }
    return data;
}

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

void PauseBeforeClosing(){
    cout << "\npress ENTER to exit...";
    cin.get();
}

int main() 
{
    vector<double> data;
    data = NoisySin(100);
    VectorDisplay(data);
    DataWrite(data);
    
    PauseBeforeClosing();
    return 0;
}
