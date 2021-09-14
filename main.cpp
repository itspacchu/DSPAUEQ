#include "include/includes.h"
#include "include/AudioFile.h"
using namespace std;

int main(void)
{
    d_vec EQ_SETTINGS = {1.4,5.0,0.2,1.0,3.0,2.0,2.0,2.0,5.0};
    AudioFile<double> songfile;
    songfile.load("build/song.wav");
    int sizeOfBuffer = songfile.getNumSamplesPerChannel();
    d_vec SignalFloats;
    for(int s = 0; s < sizeOfBuffer ;s++){
        SignalFloats.push_back(songfile.samples[0][s]);
    }
    int WINDOW_SIZE=512;
    d_vec EQ_INTERPOLATED = rev_flip_append(Interpolate(EQ_SETTINGS,32)); //gets me 256 samples
    //perform fft
    Fourier Process;
    int win_val = 0;

    int imtrack = 0;

    // shifting window by half length to avoid weird weirdness
    for(win_val = 0;win_val < sizeOfBuffer;win_val+=1470){ 
        //tqdm is cool asf m8
        //cout << "\033[2J\033[1;1H";
        cout << (int)win_val/44100 << "seconds Rendered : " << win_val << "/" << sizeOfBuffer << endl;

        // creating a slice of signalfloats
        d_vec windowed_signal = slicer(SignalFloats,win_val,WINDOW_SIZE);
        int WINDOW = windowed_signal.size();

        d_vec freqDomain; 
        d_vec freq_vals; 
        d_vec eq_filtered;
        d_vec filtered_time;


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

        //EQ stuff goes here
        eq_filtered = convolve(freqDomain,EQ_INTERPOLATED);

        // perform Inverse Fourier
        Process.freqDomainVal = ConvertToComplex(eq_filtered);
        filtered_time = Process.RIFFT(); 


        //plotting
        {
            ofstream myFile;
            myFile.open("buffer.txt");
            for (int i = 0; i < (int)WINDOW/2; i++)
            {
                //myFile << i << "," << Signal[i] << "," << filtered_time[i] << endl;
                myFile << i+1 << "," << freqDomain[i] << "," << eq_filtered[i] << "," << EQ_INTERPOLATED[i] << endl;
            }
            myFile.close();
            string mycmd = "python plotting.py buffer.txt " + to_string(imtrack);
            imtrack++;
            system(mycmd.c_str());
        }
    }
}
