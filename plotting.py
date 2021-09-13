import sys
import os
import csv
import matplotlib.pyplot as plt
import pprint
# csv file name
filename = str(sys.argv[1])
try:
    indx = str(sys.argv[2])
except:
    indx = '0'
x,y = [],[]
myfile = open(filename, 'r')

for i in myfile.readlines():
    thing = i.split(',')
    x.append(float(thing[0]))
    y.append(float(thing[1].replace("\n","")))

myfile.close()
os.system('rm ' + filename)
if(len(x) <= 64):
    plt.stem(x,y)
else:
    plt.plot(x,y)
plt.xlim(min(x), max(x))
plt.ylim(min(y), max(y))
maxfreq = 2*max(y)/(len(x)/2)
print(f" Plotting graph with {min(x)} - {max(x)} : {min(y)} - {max(y)}")
print(f" Got Max frequency at {maxfreq} Hz \n Samples : {len(x)} \n Amplitude {2*max(y)}")
plt.savefig("./images/" + filename.split('.')[0] + '.png')


"""
2*max(x)
------
len(x)/2
"""