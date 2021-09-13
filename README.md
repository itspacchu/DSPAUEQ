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

## Progress

### Got FFT to work

![image](https://user-images.githubusercontent.com/37984032/133048876-eb0851c0-3284-4b1f-8e2b-8675a6cbfb88.png)

### Windowing function [ Hamming ]

![image](https://user-images.githubusercontent.com/37984032/133049141-a230815c-0e00-4642-9b64-d1fcfd57abbc.png)


### Windowing a time domain sequence

```10*sin(TWOPI*i/(0.4*WINDOW)) + 5*sin(TWOPI*i/(0.05*WINDOW)) + 2*sin(TWOPI*i/(0.1*WINDOW))```

![image](https://user-images.githubusercontent.com/37984032/133049254-9b8484e8-c6c1-4401-aa19-baf7ac715252.png)


### FFT

![image](https://user-images.githubusercontent.com/37984032/133049727-0e9ae5f4-6ce1-422e-85cd-003c00fffb21.png)


