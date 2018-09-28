#include <iostream>
#include <vector>
#include <cmath>

#include "vectorTools.h"

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