#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <fstream>
#include "DSP.h"
#include "Fourier.h"

using namespace std;

int main(void)
{
    vector<double> insig{1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0};
    vector<complex<double>> myFFTOUTPUT = FFT(ConvertToComplex(insig));

    ofstream myFile;
    myFile.open("test1.txt");
    for (int i = 0; i < myFFTOUTPUT.size(); i++)
    {
        myFile << myFFTOUTPUT[i] << endl;
    }
    myFile.close();
}