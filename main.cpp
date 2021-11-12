#include "include/includes.h"
#include "include/AudioFile.h"
using namespace std;

int main()
{
    int imtrack = 0;
    comp_vec freq_vals; 
    comp_vec eq_filtered;
    comp_vec filtered_time;
    comp_vec freqDomain; 

    const int WINDOW_SIZE=2048;

    d_vec EQ_SETTINGS = {1.4 ,1.8 ,1.7 ,1.0 ,1.2 ,1.0 ,0.5 ,1.8, 0.2}; // EXTREME LOW PASS BOIS
    //d_vec EQ_SETTINGS = {0.0 ,0.0 ,0.0 ,0.0 ,1.0 ,1.0 ,1.0 , 1.0, 1.0}; //HIGH PASS BOIS
    d_vec EQ_INTERPOLATED = rev_flip_append(Interpolate(EQ_SETTINGS,WINDOW_SIZE/16)); //gets me 256 samples


    //Audio file input stuff and conversions
    AudioFile<double> songfile;
    songfile.load("input-small.wav");
    int sizeOfBuffer = songfile.getNumSamplesPerChannel();
    d_vec SignalFloats;
    for(int s = 0; s < sizeOfBuffer ;s++){
        SignalFloats.push_back(songfile.samples[0][s]);
    }

    // Hamming window generation
    d_vec HammingWindow = blackman_window(WINDOW_SIZE); 


    ComplexFourier cfourier;
    int win_val = 0;
    d_vec output_buffer = d_vec(sizeOfBuffer);

    /*
    * shifting window by half length to avoid weird weirdness
    * This is the beginning of windowed code performing computations on each window
    */
    for(win_val = 0;win_val < sizeOfBuffer - WINDOW_SIZE;win_val+=WINDOW_SIZE/2){ 
    //for(win_val = 512;win_val < 1024;win_val+=WINDOW_SIZE/2){ 
        
        //tqdm is cool asf m8
        cout << "\033[2J\033[1;1H" << (int)win_val/44100 << "s\n";

        // creating a slice of signalfloats
        d_vec windowed_signal = slicer(SignalFloats,win_val,WINDOW_SIZE);
        int WINDOW = windowed_signal.size();  

        // time domain signal generation
        d_vec Signal = windowed_signal;
        
        // Multiplying the two signals
        d_vec convolvedSignal = convolve(Signal, HammingWindow);

        // perform Fourier
        freqDomain = cfourier.fft(real2complex(convolvedSignal));

        //EQ stuff goes here
        eq_filtered = cfourier.convolve(freqDomain,real2complex(EQ_INTERPOLATED));

        // perform Inverse Fourier
        filtered_time = cfourier.ifft(eq_filtered);

        //overlap adding
        for(int d = 0;d < WINDOW_SIZE ;d++){
            output_buffer[d + win_val] += filtered_time[d].real(); //*HammingWindow[d];
        }

    }

    //plotting
        {
            ofstream myFile;
            myFile.open("buffer.txt");
            for (int i = 1; i < WINDOW_SIZE; i++)
            {
                myFile << i << "," << freqDomain[i].real() << "," << EQ_INTERPOLATED[i] << "," << eq_filtered[i].real()  << endl;
            }
            myFile.close();
            string mycmd = "python3 ./utils/plotting.py buffer.txt"; //+ to_string((int)start/WINDOW);
            system(mycmd.c_str());
        }
    
    cout << "done" << endl;
    AudioFile<double> outputAudioFile;
    // save the damn audio file
    int numSamplesPerChannel = sizeOfBuffer;
    outputAudioFile.setNumChannels(1);
    outputAudioFile.setSampleRate(48000.f);
    outputAudioFile.setBitDepth (songfile.getBitDepth());
    outputAudioFile.setNumSamplesPerChannel(output_buffer.size());
    for(int i=0;i<output_buffer.size();i++){
        outputAudioFile.samples[0][i] = output_buffer[i];
    }
    outputAudioFile.printSummary();
    outputAudioFile.save ("main_file.wav");
}