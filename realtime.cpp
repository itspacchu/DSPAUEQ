#include<iostream>
#include<string>
#include "include/ffmpeg_wrapper.h"
#include<math.h>
using namespace std;


int main(int argc, char** argv){
    string songname,songout;
    int freqBands = 0;
    if(argc == 3){
        songname = argv[1];
        freqBands = atoi(argv[2]);
    }else{
        cout << "Usage: ./realtime <input_file> <eqbands> "<<endl;
        return 0;
    }

    FFMPEG source =  FFMPEG(songname,songout);
    cout << "Computing Frequencies for " << freqBands << " bands\n";

    for(int i = 0;i < freqBands;i++){
        float gain = 0;
        float currFreq = (22000.0/exp(freqBands))*exp(i+1);
        cout << "enter gain (dB)" << currFreq << " : ";
        cin >> gain;
        source.FFMPEG::addFilter(currFreq,gain);
        cout << "\n";
    }
    source.play_live(false);
}

