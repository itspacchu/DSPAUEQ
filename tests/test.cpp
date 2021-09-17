#include "../include/includes.h"
#include "../include/AudioFile.h"
#include "../include/DSP/slidingdft.hpp"
using namespace std;

int main(void)
{
   d_vec EQ_SETTINGS = {1.4, 5.0, 0.2, 1.0, 3.0, 2.0, 2.0, 2.0, 5.0};
   AudioFile<double> songfile;
   songfile.load("build/song.wav");
   int sizeOfBuffer = songfile.getNumSamplesPerChannel();
   int sampleRate = songfile.getSampleRate();
}