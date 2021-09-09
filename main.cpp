#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <fstream>
#include "DSP/DSP.h"
#include "DSP/Fourier.h"

using namespace std;

int main(void)
{
    //convert Vector float to complex
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;
    vector<double> SignalFloats = ReadWaveFile(fileName);
    cout << SignalFloats.size() << endl;

    //perform fft
    vector<complex<double>> SignalComplex = FFT(ConvertToComplex(SignalFloats));

    cout << SignalComplex.size() << endl;
    //print all pls
    for (int i = 0; i < SignalComplex.size(); i++)
    {
        cout << SignalComplex[i] << endl;
    }
}