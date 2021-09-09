#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <fstream>
#include "DSP/wave.h"
#include "DSP/fourier.h"

using namespace std;

int main(void)
{
    vector<double> insig{12.4, 34.3, 54.2, 19.1, 12.1, 34.2, 54.3, 19.4};
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
