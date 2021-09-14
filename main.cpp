#include "include/includes.h"
#include "include/AudioFile.h"
using namespace std;

int main(void)
{
    int imtrack = 0;
    d_vec freq_vals; 
    d_vec eq_filtered;
    d_vec filtered_time;
    d_vec output_buffer;
    d_vec freqDomain; 

    int WINDOW_SIZE=2048;

    d_vec EQ_SETTINGS = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};
    d_vec EQ_INTERPOLATED = rev_flip_append(Interpolate(EQ_SETTINGS,128)); //gets me 256 samples


    //Audio file input stuff and conversions
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

        // perform windowing on ifft and shove it in
        d_vec output_windowed_buffer = convolve(filtered_time,HammingWindow);
        if(imtrack%2 == 0){
            for(int d = 0;d < output_windowed_buffer.size() ;d++){
                output_buffer.push_back(output_windowed_buffer[d]);
            }
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
        outputAudioFile.samples[0][i] = output_buffer[i];
    }
    outputAudioFile.printSummary();
    outputAudioFile.save ("audioFile.wav");
}

        // //plotting
        // {
        //     ofstream myFile;
        //     myFile.open("buffer.txt");
        //     for (int i = 0; i < (int)WINDOW/2; i++)
        //     {
        //         //myFile << i << "," << Signal[i] << "," << filtered_time[i] << endl;
        //         myFile << i+1 << "," << freqDomain[i] << "," << eq_filtered[i] << "," << EQ_INTERPOLATED[i] << endl;
        //     }
        //     myFile.close();
        //     string mycmd = "python plotting.py buffer.txt " + to_string(imtrack);
        //     imtrack++;
        //     system(mycmd.c_str());
        // }