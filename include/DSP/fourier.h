#include <complex>
#include <vector>
#include <algorithm>
#include "utils.h"
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

class Fourier
{
private:
    d_vec FREQS_BY_LEN(int n, double fs = 1.0)
    {
        d_vec freqs(n);
        for (int i = 0; i < (int)fs/2; i+=fs/n){
            freqs.push_back(i);
        }
        for (int i = 1; i < (int)fs/2; i+=fs/n){
            freqs.push_back(-i);
        }
        return freqs;
    }

    comp_vec FFT_REC(comp_vec arr)
    {
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
        Feven = FFT_REC(Xeven);
        comp_vec Fodd(half, 0);
        Fodd = FFT_REC(Xodd);

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

    d_vec FixPower2Issue(d_vec input){
        if(isPowerOfTwo(input.size())){
            return input;
        }else{
            int pow2 = ceil(log2(input.size()));
            d_vec returnarr = input;
            for(int k = input.size(); k < pow(2,pow2) ; k++){
                returnarr.push_back(0.0);
            }
            cout << "Padded zeros ..." << endl;
            return returnarr;
        }
    }

public:
    d_vec timeDomainVal{};
    comp_vec freqDomainVal{};

    Fourier() {}
    comp_vec FFT()
    {
        if (timeDomainVal.empty())
        {
            throw 404;
        }
        freqDomainVal = FFT_REC(ConvertToComplex(FixPower2Issue(timeDomainVal)));
        return freqDomainVal;
    }

    /*
    Parameters
    ----------
    n : int
        Window length.
    d : scalar, optional
        Sample spacing (inverse of the sampling rate). Defaults to 1.

    Returns
    -------
    f : vector<double>
        Array of length ``n//2 + 1`` containing the sample frequencies.
    */
    d_vec FFT_FREQS(int n, double d = 1.0)
    {
        return FREQS_BY_LEN(n, d);
    }

    d_vec RFFT()
    {
        if (timeDomainVal.empty())
        {
            throw 404;
        }
        if(!isPowerOfTwo(timeDomainVal.size())){
            cout << "Signal is not Power of 2" << endl;
            timeDomainVal = FixPower2Issue(timeDomainVal);
        }
        freqDomainVal = FFT_REC(ConvertToComplex(timeDomainVal));
        return CmpMagnitude(freqDomainVal);
    }

    d_vec RIFFT()
    {
        if (freqDomainVal.empty())
        {
            throw 404;
        }
        comp_vec temp = freqDomainVal;
        reverse(temp.begin(), temp.end());
        comp_vec SampArr = FFT_REC(temp);
        timeDomainVal = DivByN(CmpMagnitude(SampArr));
        return timeDomainVal;
    }
};

/*
 Computes the IFFT of the given Complex Vector sequence
 params : comp_vec arr <- input sequence 
 returns: d_vec IFFT Sequence <- frequency bins [k]
 */

comp_vec IFFT(comp_vec arr)
{
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
    // Feven = FFT(Xeven);
    comp_vec Fodd(half, 0);
    // Fodd = FFT(Xodd);
    // need a single sample at end
    comp_vec freqbin(n, 0);
    for (int k = 0; k != half; k++)
    {
        complex<double> cmpexp = polar(1.0, 2 * pi * k / n) * Fodd[k] * (1 / (double)n);
        freqbin[k] = Feven[k] + cmpexp;
        freqbin[k + half] = Feven[k] - cmpexp;
    }
    return freqbin;
}

comp_vec FFT_OLD(comp_vec arr)
{
    int n = arr.size();
    if (n == 1)
        return arr;
    // comp_vec even = FFT(comp_vec(arr.begin(), arr.begin() + n / 2));
    // comp_vec odd = FFT(comp_vec(arr.begin() + n / 2, arr.end()));
    comp_vec retarr;
    for (int k = 0; k < n / 2; k++)
    {
        // complex<double> t = polar(1.0, -2 * pi * k / n) * odd[k];
        // retarr.push_back(even[k] + t);
        // retarr.push_back(even[k] - t);
    }
    return retarr;
}
