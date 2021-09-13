#include "include/includes.h"
#include "include/AudioFile.h"
using namespace std;

int main(void)
{
    AudioFile<double> songfile;
    songfile.load("build/test.wav");
    int sizeOfBuffer = songfile.getNumSamplesPerChannel();
    d_vec SignalFloats;
    for(int s = 0; s < sizeOfBuffer ;s++){
        SignalFloats.push_back(songfile.samples[0][s]);
    }

    //perform fft
    Fourier Process;
    int win_val = 0;
    //for(win_val = 0;win_val < sizeOfBuffer;win_val+=128){
        //pbar.disable_colors();
        //pbar.set_label("Song Progress");
        //pbar.progress(win_val,sizeOfBuffer);
        d_vec windowed_signal = slicer(SignalFloats,win_val,512);
        int WINDOW = windowed_signal.size();

        d_vec freqDomain; 
        d_vec freq_vals; 


        // Hamming window generation
        d_vec HammingWindow = blackman_window(WINDOW); 

        // time domain signal generation
        d_vec Signal = windowed_signal;
        

        // Multiplying the two signals
        d_vec convolvedSignal = convolve(Signal, HammingWindow);
        Process.timeDomainVal = convolvedSignal;


        // perform Fourier
        freqDomain = Process.RFFT();
        freq_vals = Process.FFT_FREQS(WINDOW);
        //plotting
        {
            ofstream myFile;
            myFile.open("buffer.txt");
            for (int i = 0; i < (int)WINDOW; i++)
            {
                myFile << i << "," << freqDomain[i] << "," << 100*convolvedSignal[i] << endl;
            }
            myFile.close();
            string mycmd = "python plotting.py buffer.txt"; //+ to_string((int)start/WINDOW);
            system(mycmd.c_str());
        }
    //}
}
