#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <fstream>
// #include "wave/wave.h"
#include "DSP/fourier.h"

using namespace std;

int main(void)
{
    vector<double> insig{12.4345345345, 34.3, 54.2, 19.1, 12.1, 34.2, 54.3, 19.4};
    Fourier Process;
    Process.timeDomainVal = insig;
    vector<complex<double>> freqDomain = Process.FFT();
    vector<double> timeDomain = Process.IFFT();
    ofstream myFile;
    myFile.open("test2.txt");
    for (int i = 0; i < timeDomain.size(); i++)
    {
        myFile << timeDomain[i] << endl;
    }
    myFile.close();
}
