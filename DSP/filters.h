#include <complex>
#include <vector>
#include <cmath>
#include "utils.h"
#include "fourier.h"
#define PI 3.141592653589
#define TWOPI 6.28318530718

using namespace std;
class Filter
{
    enum WindowType
    {
        hamming,
        hanning,
        blackman,
        rectangular
    };

public:
    vector<double> filterVal;
    vector<double> InSignal;
    // size
    Filter(Fourier fourier, int size, double cutoff, double sampling_rate, WindowType window_type = hamming)
    {
    }

    // windows
    vector<double> window(WindowType type, int size)
    {
        vector<double> window;
        switch (type)
        {
        case 0:
            window = hamming_window(size);
            break;
        case 1:
            window = hanning_window(size);
            break;
        case 2:
            window = blackman_window(size);
            break;
        default:
            window = rectangular_window(size);
            break;
        }
        return window;
    }

private:
    vector<double> hamming_window(int size)
    {
        vector<double> window;
        for (int i = 0; i < size; i++)
        {
            window.push_back(0.54 - 0.46 * cos(TWOPI * i / (size - 1)));
        }
        return window;
    }

    vector<double> hanning_window(int size)
    {
        vector<double> window;
        for (int i = 0; i < size; i++)
        {
            window.push_back(0.5 - 0.5 * cos(TWOPI * i / (size - 1)));
        }
        return window;
    }

    vector<double> blackman_window(int size)
    {
        vector<double> window;
        for (int i = 0; i < size; i++)
        {
            window.push_back(0.42 - 0.5 * cos(TWOPI * i / (size - 1)) + 0.08 * cos(2 * TWOPI * i / (size - 1)));
        }
        return window;
    }

    vector<double> rectangular_window(int size)
    {
        vector<double> window;
        for (int i = 0; i < size; i++)
        {
            window.push_back(1);
        }
        return window;
    }
};
