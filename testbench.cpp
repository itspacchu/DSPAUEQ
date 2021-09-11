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
    d_vec insig;
    for(int i = 0; i < 100; i++)
    {
        insig.push_back(sin(4*M_PI*i/100));
    }

    Fourier Process;
    Process.timeDomainVal = insig;
    d_vec freqDomain = Process.RFFT();
    d_vec freqs = Process.FFT_FREQS(freqDomain.size());
    d_vec timeDomain = Process.RIFFT();
    ofstream myFile;
    myFile.open("test2.txt");
    for (int i = 0; i < timeDomain.size(); i++)
    {
        myFile << freqDomain[i] << "," << freqs[i] << endl;
    }
    myFile.close();
}
