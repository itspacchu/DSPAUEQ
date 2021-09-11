#include "include/includes.h"
using namespace std;

int main(void)
{
    //convert Vector float to complex
    string fileName;
    cout << "Enter the name of the file: ";
    cin >> fileName;
    d_vec SignalFloats = ReadWaveFile(fileName);
    cout << SignalFloats.size() << endl;

    //perform fft
    Fourier Process;
    Process.timeDomainVal = SignalFloats;
    d_vec freqDomain = Process.RFFT();
    d_vec freq_vals = Process.FFT_FREQS(freqDomain.size());
    //print all pls
    cout << "Size of input file (samples)" << Process.timeDomainVal.size() << endl;
    cout << "Frequency Domain: " << endl;
    ofstream myFile;
    myFile.open("plotvals.csv");
    for (int i = 0; i < freqDomain.size(); i++)
    {
        myFile << freqDomain[i] << "," << freq_vals[i] << endl;
    }
    myFile.close();
    std::system("python3 plotting.py plotvals.csv");
    return 0;
}