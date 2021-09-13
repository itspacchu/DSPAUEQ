#include <complex>
#include <vector>
#include <cmath>
#define PI 3.141592653589
#define TWOPI 6.28318530718

using namespace std;

// Hamming Window (N-point)
d_vec hamming_window(int N){
    d_vec w(N);
    for(int i=0; i<N; i++){
        w[i] = 0.54 - 0.46*cos(TWOPI*i/(N-1));
    }
    return w;
}

d_vec sinusoid(int N){
    d_vec w(N);
    for(int i=0; i<N; i++){
        w[i] = sin(TWOPI*i/N);
    }
    return w;
}

// Hanning Window (N-point)
d_vec hanning_window(int N){
    d_vec w(N);
    for(int i=0; i<N; i++){
        w[i] = 0.5 - 0.5*cos(TWOPI*i/(N-1));
    }
    return w;
}

d_vec blackman_window(int N){
    d_vec w(N);
    for(int i=0; i<N; i++){
        w[i] = 0.42 - 0.5*cos(TWOPI*i/(N-1)) + 0.08*cos(2*TWOPI*i/(N-1));
    }
    return w;
}

d_vec rectangular_window(int N){
    d_vec w(N);
    for(int i=0; i<N; i++){
        w[i] = 1;
    }
    return w;
}

// Convolves two vectors of same length
d_vec convolve(d_vec x, d_vec w){
    if(x.size() != w.size()){
        cout << "Error: convolve_window: x and w must be the same size" << endl;
        return x;
    }
    d_vec y(x.size());
    for(int i=0; i<x.size(); i++){
        y[i] = x[i]*w[i];
    }
    return y;
}
