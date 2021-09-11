import sys
import os
import csv
import matplotlib.pyplot as plt
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
    x.append(thing[0])
    y.append(thing[1])
myfile.close()
os.system('rm ' + filename)
plt.plot(x, y)
plt.savefig("./images/" + filename.split('.')[0] + indx + '.png')
