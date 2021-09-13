#include <fstream>
#include <vector>
#include <iostream>
// #include "tqdm/tqdm.h"
using namespace std;

typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate; // sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size; // subchunk2_size denotes the number of samples.
} header;

typedef struct header_file *header_p;

vector<double> ReadWaveFile(string filename , bool Normalize=true)
{
    // Reading wave files here
    vector<double> inSignal;
    FILE *infile = fopen(filename.c_str(), "rb");
    int WINDOWLEN = 512;
    int count = 0;
    short int buff16[WINDOWLEN];
    int nb;
    header_p meta = (header_p)malloc(sizeof(header));
    cout << "Reading file " << filename << endl;
    float normality = Normalize ? 32768.0 : 1.0;
    if (infile)
    {
        fread(meta, 1, sizeof(header), infile);
        while (!feof(infile))
        {
            nb = fread(buff16, 1, WINDOWLEN, infile);
            for (int i = 0; i < WINDOWLEN; i++)
            {
                inSignal.push_back(buff16[i] / normality);
            }
        }
    }
    fclose(infile);
    return inSignal;
}

// vector<double> WriteWaveFile(string filename, vector<double> Sequence, double ScaleNormalize, header_p headerValues, int BUFFERSIZE = 512)
// {
//     FILE *writeWave = fopen(filename.c_str(), "wb");
//     fwrite(headerValues, 1, writeWave);
//     int nb;
//     int count = 0;
//     int NoOfBytes = 0;
//     short int buff16[BUFFERSIZE];
//     for (double &indx : tqdm::tqdm(Sequence))
//     {
//         NoOfBytes = Sequence.size() > BUFFERSIZE ? BUFFERSIZE : BUFFERSIZE - Sequence.size();
//         // buff16 fix loop it with increments of short int
//         count++;
//         fwrite(buff16, 1, nb, outfile);
//     }
// }
