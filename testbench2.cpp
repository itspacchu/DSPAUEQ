#include "include/includes.h"
#include "include/AudioFile.h"

using namespace std;

int main(void){
    AudioFile<double> songfile;
    songfile.load("build/test.wav");
    songfile.printSummary();
    int sizeOfBuffer = songfile.getNumSamplesPerChannel();
    d_vec AudioBuff(sizeOfBuffer);
    for(int s = 0; s < sizeOfBuffer ;s++){
        AudioBuff.push_back(songfile.samples[0][s]);
    }
    
    Fourier fourier;
    fourier.timeDomainVal = AudioBuff;
    d_vec FreqDomainVal = fourier.RFFT();
    d_vec FreqFrequencyVals = fourier.FFT_FREQS(FreqDomainVal.size());

    //plotting
        {
            cout << "Writing Values" <<  endl; 
            ofstream myFile;
            myFile.open("buffer.txt");
            for (int i = 0; i < 1024; i++)
            {
                myFile << i << "," << fourier.timeDomainVal[i]  << endl;
            }
            myFile.close();
            string mycmd = "python plotting.py buffer.txt"; //+ to_string((int)start/WINDOW);
            system(mycmd.c_str());
        }

}