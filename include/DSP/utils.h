#include <complex>
#include <vector>
#include <algorithm>
using namespace std;

#define comp_vec vector<complex<double>>
#define d_vec vector<double>


/*
Substring slicing the signal based on offset and window length
input : vector<double> x,  int inputOffset (default 0) , int WindowSize (default 512)
*/
d_vec slicer(d_vec x, int offset=0, int WINDOW=512){
   d_vec y(WINDOW);
   for(int i=offset; i<offset+WINDOW; i++)
      y[i - offset] = x[i];
   return y;
}

d_vec print_vec(d_vec x){
   for(int i=0; i<x.size(); i++){
      if(x[i] == 0){
         continue;
      }
      cout << x[i] << " ";
   }
   cout << endl;
   return x;
}

double LinearInterpolate(double y1,double y2,double mu)
{
   return(y1*(1-mu)+y2*mu);
}

double CosineInterpolate(double y1,double y2,double mu)
{
   double mu2;
   mu2 = (1-cos(mu*M_PI))/2;
   return(y1*(1-mu2)+y2*mu2);
}

/*
Adds additional samples between points aka Interpolation
source : http://paulbourke.net/miscellaneous/interpolation/

input  : vector<double> in , float resample
output : new interpolated signal
*/
d_vec Interpolate(d_vec in,int upsample,int downsample=1, bool is_linear=false){
   d_vec retArr((in.size()-1)*upsample);
   int n = 0;
   for(int i = 0;i < in.size()-1;i++){
      for(int j=0;j<upsample;j++){
         //retArr[n] = CosineInterpolate(in[i],in[i+1],(float)j/(float)upsample);
         retArr[n] = CosineInterpolate(exp(in[i]),exp(in[i+1]),(float)j/(float)upsample);
         n++;
      }
   }
   return retArr;
}

float compl_to_float(complex<double> c){
   return c.real();
}

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

vector<complex<double>> real2complex(vector<double> RealArr)
{
   vector<complex<double>> retarr;
   for (int i = 0; i < RealArr.size(); i++)
   {
      retarr.push_back(complex<double>(RealArr[i], 0)); // indx1 + j0
   }
   return retarr;
}

vector<complex<double>> overlapadd(vector<complex<double>> myFFTOUTPUT, vector<complex<double>> myFFTINPUT){
   vector<complex<double>> retarr;
   for (int i = 0; i < myFFTOUTPUT.size(); i++)
   {
      retarr.push_back(myFFTOUTPUT[i] + myFFTINPUT[i]);
   }
   return retarr;
}

