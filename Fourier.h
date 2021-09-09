#include <complex>
#include <vector>
double pi = 4 * atan(1.0);

vector<complex<double>> ConvertToComplex(vector<double> RealArr)
{
    vector<complex<double>> retarr;
    for (int i = 0; i < RealArr.size(); i++)
    {
        retarr.push_back(complex<double>(RealArr[i], 0)); // indx1 + j0
    }
    return retarr;
}

vector<complex<double>> FFT(vector<complex<double>> arr)
{
    int n = arr.size();
    if (n == 1)
        return arr;
    vector<complex<double>> even = FFT(vector<complex<double>>(arr.begin(), arr.begin() + n / 2));
    vector<complex<double>> odd = FFT(vector<complex<double>>(arr.begin() + n / 2, arr.end()));
    vector<complex<double>> retarr;
    for (int k = 0; k < n / 2; k++)
    {
        complex<double> t = polar(1.0, -2 * pi * k / n) * odd[k];
        retarr.push_back(even[k] + t);
        retarr.push_back(even[k] - t);
    }
    return retarr;
}
