#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "DSP.h"

using namespace std;
int main(void){
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;
    vector<float> SignalFloats = ReadWaveFile(fileName);
    cout << SignalFloats.size() << endl;
}