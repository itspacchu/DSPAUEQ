#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <fstream>
// #include "wave/wave.h"
#include "DSP/fourier.h"

using namespace std;

double sinc(double x) {
    if (x == 0) {
        return 1;
    } else {
        return sin(x) / x;
    }
}

int main(void)
{
    d_vec insig;
    for(int i = 0; i < 256; i++)
    {
        insig.push_back(sin(2*M_PI*i/10) + sin(3*M_PI*i/10));
    }

    Fourier Process;
    Process.timeDomainVal = insig;
    d_vec freqDomain = Process.RFFT();
    d_vec freqs = Process.FFT_FREQS(freqDomain.size());
    d_vec timeDomain = Process.RIFFT();
    ofstream myFile;
    myFile.open("test2.txt");
    for (int i = 0; i < (int)timeDomain.size()/2; i++)
    {
        myFile << freqs[i] << "," << freqDomain[i]  << endl;
    }
    myFile.close();
}
