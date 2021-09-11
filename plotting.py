import sys
import csv
import matplotlib.pyplot as plt
# csv file name
filename = str(sys.argv[1])
print(filename)
x,y = [],[]
myfile = open(filename, 'r')

for i in myfile.readlines():
    thing = i.split(',')
    x.append(thing[0])
    y.append(thing[1])
myfile.close()

plt.plot(x, y)
plt.savefig(filename.split('.')[0] + '.png')
