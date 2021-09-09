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
    vector<double> insig{12.0, 34.0, 54.0, 19.0, 12.0, 34.0, 54.0, 19.0};
    vector<complex<double>> myFFTOUTPUT = FFT(ConvertToComplex(insig));
    vector<double> myIFFTOUTPUT = IFFT(myFFTOUTPUT);
    ofstream myFile;
    myFile.open("test2.txt");
    for (int i = 0; i < myIFFTOUTPUT.size(); i++)
    {
        myFile << myIFFTOUTPUT[i] << endl;
    }
    myFile.close();
}
