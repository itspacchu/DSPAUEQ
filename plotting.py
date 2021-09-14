import sys ,os
import matplotlib.pyplot as plt
import numpy as np


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
#os.system('rm ' + filename)
plt.style.use('fivethirtyeight')
if(len(x) <= 64):
    plt.stem(x,y)
else:
    plt.plot(np.log10(x),np.log10(np.abs(y)),linewidth=2)
    try:
        plt.plot(np.log10(x),np.log10(np.abs(z)),linewidth=2)
        plt.plot(np.log10(x),np.log10(np.abs(k)),'--',linewidth=2)
    except:
        pass
plt.xlim(min(np.log10(x)), max(np.log10(x)))
plt.ylim(-2, 2)
maxfreq = 2*max(y)/(len(x)/2)
# print(f" Plotting graph with {min(x)} - {max(x)} : {min(y)} - {max(y)}")
# print(f" Got Max frequency at {maxfreq} Hz \n Samples : {len(x)} \n Amplitude {2*max(y)}")
plt.legend(["Original Freq Response", "EQ Gain Freq Response" , "EQ Gain [Cubic Interpolated]"])
plt.title("EQ Signal synthesis LOG")
plt.savefig("./images/" + filename.split('.')[0] + indx + '.png',dpi=200);