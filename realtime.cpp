#include<iostream>
#include<string>
#include "include/ffmpeg_wrapper.h"
using namespace std;


int main(){
    string songname,songout;
    cout << "Enter input file (ffmpeg input) : ";
    cin >> songname;
    FFMPEG source =  FFMPEG(songname,songout);
    source.addFilter(72,4);
    source.addFilter(80,4);
    source.addFilter(1000,-4);
    source.addFilter(1200,-4);
    source.addFilter(1500,-4);
    source.addFilter(1600,-4);
    source.play_live();
}

