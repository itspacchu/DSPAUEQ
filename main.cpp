#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <fstream>
#include "wave/wave.h"   // Reading and writing wave files
#include "DSP/fourier.h" // Fourier Computations are here

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
    Fourier Process;
    Process.timeDomainVal = SignalFloats;
    vector<complex<double>> freqDomain = Process.FFT();
    vector<double> timeDomain = Process.IFFT();

    cout << timeDomain.size() << endl;
    //print all pls
    for (int i = 0; i < timeDomain.size(); i++)
    {
        cout << timeDomain[i] - SignalFloats[i] << endl;
    }
}