#include "include/includes.h"
using namespace std;

int main(void)
{
    d_vec Something = {1.0,2.0,1.0,1.0,2.0,3.0};
    Fourier fourier;
    fourier.timeDomainVal = Something;
    d_vec freqdom = fourier.RFFT();
    for(int i =0; i < freqdom.size(); i++){
        cout << freqdom[i] << endl;
    }
}
    

