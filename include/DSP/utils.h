#include <complex>
#include <vector>
#include <algorithm>
using namespace std;

#define comp_vec vector<complex<double>>
#define d_vec vector<double>

/*
 *   Utility
 * 
 */

bool isPowerOfTwo(int n) // cuz fft really likes to simp powers of 2 values
{
   return (ceil(log2(n)) == floor(log2(n))) && (n != 0);
}

d_vec CmpMagnitude(vector<complex<double>> myFFTOUTPUT)
{
   vector<double> myFFTOUTPUT_abs;
   for (int i = 0; i < myFFTOUTPUT.size(); i++)
   {
      myFFTOUTPUT_abs.push_back(abs(myFFTOUTPUT[i]));
   }
   return myFFTOUTPUT_abs;
}

vector<double> DivByN(vector<double> myFFTOUTPUT_abs, int N = 0)
{
   if (N == 0)
   {
      N = myFFTOUTPUT_abs.size(); // sanity no zero division ;-;
   }
   vector<double> DivbyNReturn;
   for (int i = 0; i < myFFTOUTPUT_abs.size(); i++)
   {
      DivbyNReturn.push_back(myFFTOUTPUT_abs[i] / (double)N);
   }
   return DivbyNReturn;
}

vector<complex<double>> ConvertToComplex(vector<double> RealArr)
{
   vector<complex<double>> retarr;
   for (int i = 0; i < RealArr.size(); i++)
   {
      retarr.push_back(complex<double>(RealArr[i], 0)); // indx1 + j0
   }
   return retarr;
}