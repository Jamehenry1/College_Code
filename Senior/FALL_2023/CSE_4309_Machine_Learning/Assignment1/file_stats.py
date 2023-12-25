import sys
import numpy as np

x = []

with open(sys.argv[1]) as file:
    lines = [i.strip() for i in file]

for i in range(len(lines)):
    x.append([float(s) for s in lines[i].split()])
    
#print(x)
def mean(x):
    sumOfCol = [0,0,0,0,0]
    meanOfCol = [0,0,0,0,0] # Totally for got that there was a .mean for python, too late now
    
    for i in range(len(x)):
        for j in range(len(x[i])):
            #print(len(x[i]))
            sumOfCol[j] = sumOfCol[j] + float(x[i][j])

    for i in range(len(sumOfCol)):
        meanOfCol[i] = "{:.4f}".format(sumOfCol[i]/len(x))

    std = np.std(x,axis=0,ddof=1)

    #print(std)
    #print(meanOfCol)

    for i in range(5):
        print("Column %d: mean = %.4f, std = %.4f" % (i,float(meanOfCol[i]),float(std[i])))



    return meanOfCol

meanOfCol = mean(x)







