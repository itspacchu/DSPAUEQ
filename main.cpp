#include "include/includes.h"
#include "include/AudioFile.h"
#include "include/DSP/slidingdft.hpp"
using namespace std;

int main(void)
{
    d_vec EQ_SETTINGS = {1.4, 5.0, 0.2, 1.0, 3.0, 2.0, 2.0, 2.0, 5.0};
    AudioFile<double> songfile;
    songfile.load("build/song.wav");
    int sizeOfBuffer = songfile.getNumSamplesPerChannel();
    int sampleRate = songfile.getSampleRate();

    cout << sizeOfBuffer << endl;

    d_vec SignalFloats;
    for (int s = 0; s < sizeOfBuffer; s++)
    {
        SignalFloats.push_back(songfile.samples[0][s]);
    }
    int WINDOW_SIZE = 512;
    d_vec EQ_INTERPOLATED = rev_flip_append(Interpolate(EQ_SETTINGS, 32)); //gets me 256 samples
    //perform fft
    Fourier Process;

    d_vec freqDomain;
    d_vec freq_vals;
    comp_vec eq_filtered;
    d_vec filtered_time;
    const int imageframe = 1470;
    int win_val = 0;
    int imtrack = 0;
    d_vec final(sizeOfBuffer);
    comp_vec convolvedSignal;

    // Hamming window generation
    d_vec HammingWindow = blackman_window(512); // TODO: put it on top

    // Use double precision arithmetic and a 512-length DFT
    static SlidingDFT<double, 512> dft;

    // After at least 512 samples have been processed:
    complex<double> DC_bin;

    // shifting window by half length to avoid weird weirdness
    for (win_val = 0; win_val < sizeOfBuffer; win_val += 1)
    {
        cout << win_val << "/" << sizeOfBuffer << endl;

        dft.update(SignalFloats[win_val]);

        // Multiplying the two signals
        if (win_val % 512 > 0)
            convolvedSignal[win_val - 512] = dft.dft[win_val - 512];

        //EQ stuff goes here

        // cout << final << endl;
        //plotting
        // {
        //     ofstream myFile;
        //     myFile.open("buffer.txt");
        //     for (int i = 0; i < (int)WINDOW / 2; i++)
        //     {
        //         //myFile << i << "," << Signal[i] << "," << filtered_time[i] << endl;
        //         myFile << i + 1 << "," << freqDomain[i] << "," << eq_filtered[i] << "," << EQ_INTERPOLATED[i] << endl;
        //     }
        //     myFile.close();
        //     string mycmd = "python3 plotting.py buffer.txt " + to_string(imtrack);
        //     imtrack++;
        //     system(mycmd.c_str());
        //     cout << (int)win_val / 44100 << "seconds Rendered : " << win_val << "/" << sizeOfBuffer << endl;
        // }
    }
    eq_filtered = convolveCom(convolvedSignal, ConvertToComplex(EQ_INTERPOLATED));

    Process.freqDomainVal = eq_filtered;
    Process.RIFFT();

    for (int n = 0; n < Process.timeDomainVal.size() - 1; n++)
    {
        final[n] += Process.timeDomainVal[n];
        // final.push_back(filtered_time[n]);
    }

    AudioFile<double> songfile2;
    AudioFile<double>::AudioBuffer outBuffer;

    songfile2.setBitDepth(16);
    songfile2.setSampleRate(44100);

    // Set both the number of channels and number of samples per channel
    songfile2.setAudioBufferSize(1, final.size());
    outBuffer.resize(2);
    outBuffer[0].resize(final.size());
    outBuffer[1].resize(final.size());
    for (int i = 0; i < final.size() - 1; i++)
    {
        // for (int channel = 0; channel < 1; channel++) // channel size
        // cout << "works3" << endl;
        outBuffer[0][i] = final[i];
        outBuffer[1][i] = final[i];
    }
    // Wave file
    // 5. Put into the AudioFile object
    bool ok = songfile2.setAudioBuffer(outBuffer);
    songfile2.save("audioFile1.wav");
}
