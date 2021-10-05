### ~~pls ignore this thing, its for college minor project documentation~~


<br>

# 1

### Got FFT to work

<img src="https://user-images.githubusercontent.com/37984032/133048876-eb0851c0-3284-4b1f-8e2b-8675a6cbfb88.png" width=400>

### time windowing function 

```10*sin(TWOPI*i/(0.4*WINDOW)) + 5*sin(TWOPI*i/(0.05*WINDOW)) + 2*sin(TWOPI*i/(0.1*WINDOW))```

<img src="https://media.discordapp.net/attachments/856258127568699443/887042194920333382/unknown.png" width=400>


EQ is an 8 point Freq gain control

```d_vec EQ_SETTINGS = {1.4,5.0,0.2,2.0,3.0,1.0,1.0,3.0,5.0};```

this is being interpolated by using Cubic interpolation scheme ```Interpolate(EQ_SETTINGS,32)``` and is convoluted to the frequency response  

```eq_filtered = convolve(freqDomain,EQ_INTERPOLATED);```

Windowing ( Blackman ) Window is considered.

<img src="https://user-images.githubusercontent.com/37984032/133150628-860d5017-4823-46d7-a92f-6c0a1daba2a0.png" width=400>


# 2

Fixed a bug where filter was not being applied properly to negative frequencies leading to weird filtering issues

### LOW PASS FILTER

**LEFT** The filter is not being flipped
**RIGHT** Is how the filter must be applied

<img src="https://user-images.githubusercontent.com/37984032/133925568-e8217efe-3022-47dd-b4bd-54bd8abb112b.png" width=400>

**AUDACITY Freq plot**

<img src="https://user-images.githubusercontent.com/37984032/133925625-fff9489e-1535-4fd5-9162-d877d1cfea5c.png" width=400>


# 3

Decided to use ffmpeg due to it being faster and more efficient than mess of for loops i wrote ;-;
made a basic ffmpeg wrapper ```/include/ffmpeg_wrapper.h``` from ffmpeg documentation, implemented bare stuff which are required to perform what project needs to do.

```source.addFilter( frequency_in_Hz , gain_in_db );```

ffmpeg documentation
```firequalizer=gain_entry='entry(100,0);'```

### realtime audio playback

```ffmpeg -i song.wav -f wav pipe:1 | ffplay -i -``` allows to pipe ffmpeg output realtime to ffplay


# 4

Raspberry pi zero (which is being used in the presentation of project) doesn't have the required DAC to generate audio output so we pipe output through the PWM pins of rpi0.

<img src="https://cdn.discordapp.com/attachments/852930321493655563/894956737193463909/unknown.png" width=400>

GPIO pin 13 is used to pipe audio as PWM signal.

LPF HPF cascaded BPF filtering at GPIO pin

<img src="https://media.discordapp.net/attachments/852930321493655563/894959676863684658/unknown.png" width=400>

----


## References
```(im a noob alright)```

http://ffmpeg.org/ffmpeg-filters.html#equalizer

https://ccrma.stanford.edu/~jos/vguitar/Fitting_Filters_Matlab.html

https://youtu.be/u8t-h31baFE

https://dsp.stackexchange.com/questions/9340/building-a-low-pass-fft-filter-for-a-noisy-current-pulse-signal 

