#include <complex>
#include <vector>
#include <algorithm>
using namespace std;

#ifdef __linux__
double pi = M_PI;
#else
double pi = 4 * atan(1.0);
#endif

/*
 Source of this algo :O
 https://youtu.be/h7apO7q16V0
 
 Computes the FFT of the given Complex Vector sequence
 params : comp_vec arr <- input sequence
 returns: comp_vec freqbins <- frequency bins [k]
 */

class ComplexFourier {
    private:
    comp_vec complexFixPower2(comp_vec input){
            if(isPowerOfTwo(input.size())){
                return input;
            }else{
                int pow2 = ceil(log2(input.size()));
                comp_vec returnarr = input;
                for(int k = input.size(); k < pow(2,pow2) ; k++){
                    returnarr.push_back(complex<double>(0,0));
                }
                cout << "ComplexFourier:  padded zeros at end " << endl;
                return returnarr;
            }
        }
    
    comp_vec cfft(comp_vec arr){
            // needs 2^n no of samples input!!
            int n = arr.size();
            if (n == 1)
            {
                return arr;
            }
            // split into even and odd subsums
            int half = n / 2;
            comp_vec Xeven(half, 0);
            comp_vec Xodd(half, 0);

            for (int i = 0; i != half; i++)
            {
                Xeven[i] = arr[2 * i];
                Xodd[i] = arr[2 * i + 1];
            }

            comp_vec Feven(half, 0);
            Feven = cfft(Xeven);
            comp_vec Fodd(half, 0);
            Fodd = cfft(Xodd);

            // need a single sample at end
            comp_vec freqbin(n, 0);
            for (int k = 0; k != half; k++)
            {
                complex<double> cmpexp = polar(1.0, -2 * pi * k / n) * Fodd[k];
                freqbin[k] = Feven[k] + cmpexp;
                freqbin[k + half] = Feven[k] - cmpexp;
            }
            return freqbin;
    }

    comp_vec cifft(comp_vec arr){
            int n = arr.size();
            if (n == 1)
            {
                return arr;
            }
            // split into even and odd subsums
            int half = n / 2;
            comp_vec Xeven(half, 0);
            comp_vec Xodd(half, 0);
            for (int i = 0; i != half; i++)
            {
                Xeven[i] = arr[2 * i];
                Xodd[i] = arr[2 * i + 1];
            }
            comp_vec Feven = cifft(Xeven);
            comp_vec Fodd = cifft(Xodd);
            // need a single sample at end
            comp_vec timebin(n, 0);
            for (int k = 0; k != half; k++)
            {
                complex<double> cmpexp = polar(1.0, 2 * pi * k / n) * Fodd[k];
                timebin[k] = Feven[k] + cmpexp;
                timebin[k + half] = Feven[k] - cmpexp;
            }
            return timebin;
    }

    public:
    /*
    *  FFT Complex to Complex
    */
    comp_vec fft(comp_vec arr) {
        if(isPowerOfTwo(arr.size())) {
            arr = complexFixPower2(arr);
        }
        return cfft(arr);
    }


    /*
    *  Inverse FFT Complex to Complex
    */
    comp_vec ifft(comp_vec arr) {
        if(isPowerOfTwo(arr.size())) {
            arr = complexFixPower2(arr); 
        }
        comp_vec returnarr = cifft(arr);
        for(int k = 0; k < returnarr.size(); k++){
            returnarr[k] /= arr.size();
        }
        return returnarr;
    }

    comp_vec convolve(comp_vec arr1, comp_vec arr2){
        comp_vec returnarr = arr1;  
        for(int k = 0; k < arr1.size(); k++){
            returnarr[k] *= arr2[k];
        }
        return returnarr;
    }
};