#include "include/includes.h"
using namespace std;

int main(void)
{
    string fileName;
    cout << "Enter the name of the file: ";
    fileName = "./build/test.wav";
    d_vec SignalFloats = ReadWaveFile(fileName);

    //perform fft
    cFourier Process;
    int WINDOW = 512;

    d_vec freqDomain; 
    d_vec freq_vals; 


    // Hamming window generation
    d_vec HammingWindow = hamming_window(WINDOW); 

    for(int fftsamp = 0; fftsamp < SignalFloats.size(); fftsamp += (int)WINDOW/2){ 
    
        // time domain signal generation
        d_vec Signal = slicer(SignalFloats,fftsamp,WINDOW);
        

        // Multiplying the two signals
        d_vec convolvedSignal = convolve(Signal, HammingWindow);
        Process.timeDomainVal = convolvedSignal;


        // perform Fourier
        freqDomain = Process.RFFT();
        freq_vals = Process.FFT_FREQS(WINDOW);

        //plotting
        {
            cout << "Writing Values" <<  endl; 
            ofstream myFile;
            myFile.open("buffer.txt");
            for (int i = 0; i < (int)WINDOW; i++)
            {
                myFile << i << "," << freqDomain[i]  << endl;
            }
            myFile.close();
            string mycmd = "python plotting.py buffer.txt"; //+ to_string((int)start/WINDOW);
            system(mycmd.c_str());
        }

    }
    

}