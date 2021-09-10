#include <complex>
#include <vector>
#include <algorithm>
#include "utills.h"
using namespace std;

// double pi = 4 * atan(1.0);
double pi = M_PI;

/*
 *   Source of this algo :O
 *   https://youtu.be/h7apO7q16V0
 * 
 */

/*
 Computes the FFT of the given Complex Vector sequence
 params : vector<complex<double>> arr <- input sequence
 returns: vector<complex<double>> freqbins <- frequency bins [k]
 */

class Fourier
{
private:
    vector<complex<double>> FFT_REC(vector<complex<double>> arr)
    {
        // needs 2^n no of samples input!!
        int n = arr.size();
        if (n == 1)
        {
            return arr;
        }
        // split into even and odd subsums
        int half = n / 2;
        vector<complex<double>> Xeven(half, 0);
        vector<complex<double>> Xodd(half, 0);

        for (int i = 0; i != half; i++)
        {
            Xeven[i] = arr[2 * i];
            Xodd[i] = arr[2 * i + 1];
        }

        vector<complex<double>> Feven(half, 0);
        Feven = FFT_REC(Xeven);
        vector<complex<double>> Fodd(half, 0);
        Fodd = FFT_REC(Xodd);

        // need a single sample at end
        vector<complex<double>> freqbin(n, 0);
        for (int k = 0; k != half; k++)
        {
            complex<double> cmpexp = polar(1.0, -2 * pi * k / n) * Fodd[k];
            freqbin[k] = Feven[k] + cmpexp;
            freqbin[k + half] = Feven[k] - cmpexp;
        }
        return freqbin;
    }

public:
    vector<double> timeDomainVal{};
    vector<complex<double>> freqDomainVal{};

    Fourier() {}
    vector<complex<double>> FFT()
    {
        if (timeDomainVal.empty())
        {
            throw 404;
        }
        freqDomainVal = FFT_REC(ConvertToComplex(timeDomainVal));
        return freqDomainVal;
    }

    vector<double> IFFT()
    {
        if (freqDomainVal.empty())
        {
            throw 404;
        }
        vector<complex<double>> temp = freqDomainVal;
        reverse(temp.begin(), temp.end());
        vector<complex<double>> SampArr = FFT_REC(temp);
        timeDomainVal = DivByN(CmpMagnitude(SampArr));
        return timeDomainVal;
    }
};

/*
 Computes the IFFT of the given Complex Vector sequence
 params : vector<complex<double>> arr <- input sequence 
 returns: vector<double> IFFT Sequence <- frequency bins [k]
 */

vector<complex<double>> IFFT_OLD(vector<complex<double>> arr)
{
    int n = arr.size();
    if (n == 1)
    {
        return arr;
    }
    // split into even and odd subsums
    int half = n / 2;
    vector<complex<double>> Xeven(half, 0);
    vector<complex<double>> Xodd(half, 0);

    for (int i = 0; i != half; i++)
    {
        Xeven[i] = arr[2 * i];
        Xodd[i] = arr[2 * i + 1];
    }
    vector<complex<double>> Feven(half, 0);
    // Feven = FFT(Xeven);
    vector<complex<double>> Fodd(half, 0);
    // Fodd = FFT(Xodd);
    // need a single sample at end
    vector<complex<double>> freqbin(n, 0);
    for (int k = 0; k != half; k++)
    {
        complex<double> cmpexp = polar(1.0, 2 * pi * k / n) * Fodd[k] * (1 / (double)n);
        freqbin[k] = Feven[k] + cmpexp;
        freqbin[k + half] = Feven[k] - cmpexp;
    }
    return freqbin;
}

vector<complex<double>> FFT_OLD(vector<complex<double>> arr)
{
    int n = arr.size();
    if (n == 1)
        return arr;
    // vector<complex<double>> even = FFT(vector<complex<double>>(arr.begin(), arr.begin() + n / 2));
    // vector<complex<double>> odd = FFT(vector<complex<double>>(arr.begin() + n / 2, arr.end()));
    vector<complex<double>> retarr;
    for (int k = 0; k < n / 2; k++)
    {
        // complex<double> t = polar(1.0, -2 * pi * k / n) * odd[k];
        // retarr.push_back(even[k] + t);
        // retarr.push_back(even[k] - t);
    }
    return retarr;
}
