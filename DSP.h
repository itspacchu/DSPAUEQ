#include<vector>
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
    int sample_rate;			// sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;			// subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;

vector<float> ReadWaveFile(string filename){
    // Reading wave files here
    vector<float> inSignal;
    FILE * infile = fopen(filename.c_str(),"rb");	
    int WINDOWLEN = 512;
    int count = 0;
	short int buff16[WINDOWLEN];
    int nb;				
	header_p meta = (header_p)malloc(sizeof(header));
    cout << "Reading file " << filename << endl;

    if(infile){
        fread(meta,1,sizeof(header),infile);
        while (!feof(infile))
		{
			nb = fread(buff16,1,WINDOWLEN,infile);
            for(int i = 0; i < WINDOWLEN; i++)
            {
                inSignal.push_back(buff16[i]/32768.0);
            }
		}
    }
    fclose(infile);
    return inSignal;
}