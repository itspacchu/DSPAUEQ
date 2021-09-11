#include "include/includes.h"
using namespace std;

int main(void)
{
    //convert Vector float to complex
    string fileName;
    cout << "Enter the name of the file: ";
    //cin >> fileName;
    fileName = "./build/test.wav";
    d_vec SignalFloats = ReadWaveFile(fileName);
    cout << SignalFloats.size() << endl;

    //perform fft
    Fourier Process;
    int WINDOW = 512;
    //int start;
    //cin >> start;
    cout << SignalFloats.size() <<  endl; 
    d_vec freqDomain; 
    d_vec freq_vals; 

    d_vec HammingWindow = blackman_window(WINDOW); //hamming_window(WINDOW);
    d_vec Signal;
    for(int i = 0; i < WINDOW; i++)
    {
        Signal.push_back(rand()%100);
    }
    d_vec convolvedSignal = convolve(Signal, HammingWindow);
    /*
    for(int start = 0 ; start < 512; start++){
        Process.timeDomainVal = convolve_window(slicer(SignalFloats, start, start+WINDOW), HammingWindow);

        // cout << Process.timeDomainVal.size() << endl;
        // for (int k = start; k < start + 4; k++)
        // {
        //     cout << Process.timeDomainVal[k] << endl;
        // }
        // cout << "..." << Process.timeDomainVal.size() << endl;

        freqDomain = Process.RFFT();
        freq_vals = Process.FFT_FREQS(freqDomain.size(),44100.0);
        ofstream myFile;
        myFile.open("buffer.txt");
        for (int i = start; i < (int)(start+WINDOW); i++)
        {
            myFile << i-start << "," << freqDomain[i]  << endl;
        }
        myFile.close();
        
        string mycmd = "python plotting.py buffer.txt"; //+ to_string((int)start/WINDOW);
        system(mycmd.c_str());
    */
    Process.timeDomainVal = HammingWindow;
    freqDomain = Process.RFFT();
    ofstream myFile;
    myFile.open("buffer.txt");
    for (int i = 0; i < WINDOW; i++)
    {
        myFile << i << "," << freqDomain[i]  << endl;
    }
    myFile.close();
    
    string mycmd = "python plotting.py buffer.txt"; //+ to_string((int)start/WINDOW);
    system(mycmd.c_str());
}
