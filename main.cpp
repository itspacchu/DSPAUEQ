#include "include/includes.h"
#include "include/AudioFile.h"
using namespace std;

int main(void)
{
    int imtrack = 0;
    comp_vec freq_vals; 
    comp_vec eq_filtered;
    comp_vec filtered_time;
    comp_vec output_buffer;
    comp_vec freqDomain; 

    int WINDOW_SIZE=2048;

    d_vec EQ_SETTINGS = {1.0,0.0,3.0,0.0,0.0,0.0,0.0,1.0,1.0};
    d_vec EQ_INTERPOLATED = rev_flip_append(Interpolate(EQ_SETTINGS,128)); //gets me 256 samples


    //Audio file input stuff and conversions
    AudioFile<double> songfile;
    songfile.load("build/test.wav");
    int sizeOfBuffer = songfile.getNumSamplesPerChannel();
    d_vec SignalFloats;
    for(int s = 0; s < sizeOfBuffer ;s++){
        SignalFloats.push_back(songfile.samples[0][s]);
    }


    ComplexFourier cfourier;
    int win_val = 0;

    /*
    * shifting window by half length to avoid weird weirdness
    * This is the beginning of windowed code performing computations on each window
    */
    for(win_val = 0;win_val < sizeOfBuffer;win_val+=1024){ 
        
        //tqdm is cool asf m8
        cout << "\033[2J\033[1;1H";
        cout << (int)win_val/44100 << "s" << endl;

        // creating a slice of signalfloats
        d_vec windowed_signal = slicer(SignalFloats,win_val,WINDOW_SIZE);
        int WINDOW = windowed_signal.size();


        // Hamming window generation
        d_vec HammingWindow = rectangular_window(WINDOW); 

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

        // perform windowing on ifft and shove it in
        comp_vec output_windowed_buffer = cfourier.convolve(filtered_time,real2complex(HammingWindow));
        for(int d = 0;d < output_windowed_buffer.size() ;d++){
            output_buffer.push_back(output_windowed_buffer[d]);
            cout << output_buffer.size() << endl;
        }
        imtrack++;
 
    }

    AudioFile<double> outputAudioFile;
    // save the damn audio file
    int numSamplesPerChannel = sizeOfBuffer;
    outputAudioFile.setNumChannels(1);
    outputAudioFile.setSampleRate(48000.f);
    outputAudioFile.setBitDepth (16);
    outputAudioFile.setNumSamplesPerChannel(output_buffer.size());
    for(int i=0;i<output_buffer.size();i++){
        outputAudioFile.samples[0][i] = compl_to_float(output_buffer[i]);
    }
    outputAudioFile.printSummary();
    outputAudioFile.save ("audioFile.wav");
}