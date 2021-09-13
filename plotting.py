import sys ,os
import matplotlib.pyplot as plt
import numpy as np


filename = str(sys.argv[1])
try:
    indx = str(sys.argv[2])
except:
    indx = '0'

x,y,z = [],[],[]
myfile = open(filename, 'r')
for i in myfile.readlines():
    thing = i.split(',')
    x.append(float(thing[0]))
    try:
        z.append(float(thing[2].replace("\n",""))+1.0)    
        y.append(float(thing[1])+1.0)  
    except:
        y.append(float(thing[1].replace("\n",""))+1.0)  

myfile.close()
#os.system('rm ' + filename)
if(len(x) <= 64):
    plt.stem(x,y)
else:
    plt.plot(x,np.abs(y))
    try:
        plt.plot(x,np.abs(z))
    except:
        pass
plt.xlim(min(x), max(x))
plt.ylim(0, 8)
maxfreq = 2*max(y)/(len(x)/2)
# print(f" Plotting graph with {min(x)} - {max(x)} : {min(y)} - {max(y)}")
# print(f" Got Max frequency at {maxfreq} Hz \n Samples : {len(x)} \n Amplitude {2*max(y)}")
plt.savefig("./images/" + filename.split('.')[0] + '.png')