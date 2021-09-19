## Sound Synthesis and Processing on ARM based SBC
To Perform Sound synthesis and Digital Signal Processing on and  [ ARM based SBC ](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/).

# Abstract

Sound Synthesis and Processing is used commonly in the field of Audio Engineering and Music Production.
The goal is to perform signal analysis and filtering using Discrete Fourier transform ( FFT Algorithm ) to perform Filtering and Synthesis of given input signals.

## Objectives
- To perform Filtering using EQ Bands
- Perform Close to Realtime Processing 


## Software

- C/C++ for Implementation
- Julia for Simulation of Signals
- Python for plotting (matplotlib)


## Hardware
- Raspberry Pi Zero 
- Serial DAC Peripheral
- SSD1306 OLED 


## Epoch 1

EQ is an 8 point Freq gain control

```d_vec EQ_SETTINGS = {1.4,5.0,0.2,2.0,3.0,1.0,1.0,3.0,5.0};```

this is being interpolated by using Cubic interpolation scheme ```Interpolate(EQ_SETTINGS,32)``` and is convoluted to the frequency response  

```eq_filtered = convolve(freqDomain,EQ_INTERPOLATED);```

Windowing ( Blackman ) Window is considered.

![buffer](https://user-images.githubusercontent.com/37984032/133150628-860d5017-4823-46d7-a92f-6c0a1daba2a0.png)


## Epoch 2

Fixed a bug where filter was not being applied properly to negative frequencies leading to weird filtering issues

### LOW PASS FILTER

**LEFT** The filter is not being flipped
**RIGHT** Is how the filter must be applied

![image](https://user-images.githubusercontent.com/37984032/133925568-e8217efe-3022-47dd-b4bd-54bd8abb112b.png)

**AUDACITY Freq plot**
![image](https://user-images.githubusercontent.com/37984032/133925625-fff9489e-1535-4fd5-9162-d877d1cfea5c.png)

Audio file generated is now sufficiently distortion free.

----


## Progress

### Got FFT to work

![image](https://user-images.githubusercontent.com/37984032/133048876-eb0851c0-3284-4b1f-8e2b-8675a6cbfb88.png)

### Windowing function [ Hamming ]
![image](https://user-images.githubusercontent.com/37984032/133049141-a230815c-0e00-4642-9b64-d1fcfd57abbc.png)


### windowing function implementation
```10*sin(TWOPI*i/(0.4*WINDOW)) + 5*sin(TWOPI*i/(0.05*WINDOW)) + 2*sin(TWOPI*i/(0.1*WINDOW))```
![image](https://media.discordapp.net/attachments/856258127568699443/887042194920333382/unknown.png?width=595&height=454)

## References
```(im a noob alright)```

https://ccrma.stanford.edu/~jos/vguitar/Fitting_Filters_Matlab.html
https://youtu.be/u8t-h31baFE
https://dsp.stackexchange.com/questions/9340/building-a-low-pass-fft-filter-for-a-noisy-current-pulse-signal 
