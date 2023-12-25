# Nghia Lam
# 1001699317
# Task 2

import numpy as np
from drawing import *


def Means(dic):
    kMeans = []

    for key in dic:
        xTotal = 0
        yTotal = 0
        for val in dic[key]:
            xTotal += val[0]
            if len(val) > 1:
                yTotal += val[1]
            
        kMeans.append([xTotal/len(dic[key]),yTotal/len(dic[key])])
        
    return kMeans

def Distance(dic,Kmean,K):

    newDic = {}
    for i in range(K):
        newDic[i+1] = []
    for key in dic:
        for val in dic[key]:
            vals = np.array(val)
            normVal = []
            for i in range(len(Kmean)):
                test = vals - Kmean[i]
                dis = np.sqrt(np.dot(test.T,test))
                normVal.append(dis)
            newIndex = normVal.index(min(normVal)) + 1

            if newIndex not in newDic:
                newDic[newIndex] = [val.copy()]
            else:
                newDic[newIndex] += [val.copy()]
    
    if(newDic == dic):
        return newDic
    else:
        newKmeans = Means(newDic)
        return Distance(newDic,newKmeans,K)
    

def k_means(data_file, K, initialization):
    values = []
    dic = {}
    with open(data_file) as file:
        lines = [i.strip() for i in file]

    for i in range(len(lines)):
        values.append([float(s) for s in lines[i].split()])
    
    for i in range(K):
        dic[i+1] = []

    if initialization == "round_robin":
        for i,val in enumerate((values)):
            key = (i)%K + 1
            dic[key] += [val] 
    
    if initialization == "random":
        for i,val in enumerate((values)):
            key = np.random.random_integers(low=1,high=K)
            #print(key)
            dic[key] += [val] 

    kMeans = Means(dic)
    finalDic = Distance(dic,kMeans,K)

    data = []
    assignments = []
    for key in finalDic:
        for val in finalDic[key]:
            assignments.append(key)
            data.append(val)
            
    for value in values:
        for k in finalDic:
            if value in finalDic[k]:
                #print("test1:",value,k)
                if len(value) > 1:
                    print('({:10.4f}, {:10.4f}) --> cluster {:d}'.format(value[0], value[1], k))
                else:
                    print('{:10.4f} --> cluster {:d}'.format(value[0], k))

    assignments = np.array(assignments)
    data = np.array(data)
    draw_assignments(data.T,assignments)


    

    