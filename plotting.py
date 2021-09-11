import sys
import csv
import matplotlib.pyplot as plt
# csv file name
filename = str(sys.argv[1])
print(filename)
with open(filename, 'r') as csvfile:
    # get number of columns
    reader = csv.reader(csvfile)
    x = y = []
    for row in reader:
        x.append(float(row[0]))
        y.append(float(row[1]))
plt.plot(x, y)
plt.savefig(filename + '.png')
