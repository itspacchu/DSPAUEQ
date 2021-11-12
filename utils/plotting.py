import sys ,os
import matplotlib.pyplot as plt
import numpy as np


csfont = {'fontname':'Bookerly'}

filename = str(sys.argv[1])
try:
    indx = str(sys.argv[2])
except:
    indx = '0'

x,y,z,k = [],[],[],[]
myfile = open(filename, 'r')
for i in myfile.readlines():
    thing = i.split(',')
    x.append(float(thing[0]))
    try:
        k.append(float(thing[3].replace("\n","")))    
        z.append(float(thing[2])+1.0)    
        y.append(float(thing[1])+1.0)  
    except:
        y.append(float(thing[1].replace("\n",""))+1.0)  

myfile.close()
# os.system('rm ' + filename)
plt.style.use('./include/dracula.mplstyle')
if(len(x) <= 64):
    
    plt.stem(x,y)
else:
    temp = z/np.max(z)
    temp2 = k/np.max(k)
    temp3 = y/np.max(y)

    plt.plot(x,np.abs(temp3),linewidth=.5)
    try:
        plt.plot(x,np.abs(temp),linewidth=2.5) ## eq
        plt.plot(x,np.abs(temp2),'--',linewidth=1) 
        pass
    except:
        pass
plt.xlim(min(x), max(x)/2)
plt.ylim(0, 2)
maxfreq = 2*max(y)/(len(x)/2)
# print(f" Plotting graph with {min(x)} - {max(x)} : {min(y)} - {max(y)}")
# print(f" Got Max frequency at {maxfreq} Hz \n Samples : {len(x)} \n Amplitude {2*max(y)}")
"""
plt.rcParams["font.family"] = "Bookerly"
plt.axis('off')
plt.legend(["Original Freq Response", "EQ Gain Freq Response" , "EQ Gain [Cubic Interpolated]"],loc ="lower left")
plt.title("FFT Equalizer filtering",**csfont)
plt.xlabel("log(freq)",**csfont)
plt.ylabel("log(amplitude)",**csfont)
plt.figtext(0.9,0.12, f"Blackman windowing \n512 freq_bin\n{indx}_index\n{round(maxfreq,2)} Hz normalized max", ha="right", fontsize=11)
plt.tick_params(
    axis='x',          # changes apply to the x-axis
    which='both',      # both major and minor ticks are affected
    bottom=False,      # ticks along the bottom edge are off
    top=False,         # ticks along the top edge are off
    labelbottom=False) # labels along the bottom edge are off

plt.tick_params(
    axis='y',          # changes apply to the x-axis
    which='both',      # both major and minor ticks are affected
    bottom=False,      # ticks along the bottom edge are off
    top=False,         # ticks along the top edge are off
    labelbottom=False) # labels along the bottom edge are off
"""
plt.savefig("./images/" + filename.split('.')[0] + indx + '.png',dpi=250,bbox_inches='tight');