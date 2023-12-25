#Nghia Lam
#1001699317
#Assignment 2 Task 5

import numpy as np

def nice_print(dict,key):
    for i in dict[key]:
        print(str(i) + '\n')
    print(len(dict[key]))

#makes the dictionary from a file
def makeDict(f):
    with open(f) as file:   #opens file and puts the content in line
        lines = [i.strip() for i in file]   
    
    Dict = {}

    for line in lines:
        holder = line.split()   #Split the contents in line for easier access of each data point
        
        #Create dictionary so that each Class label
        key = int(holder[len(holder)-1])    #Makes the class value (last point in each dataset) the key
        #print(Dict.keys())
        if key not in Dict.keys():
            #print(key)
            Dict.update({key:[]})

        #print(key)
        Dict[key].append(holder)    #makes each class have there own key so that it is easier to get information
    
        
    
    #print(Dict)
    file.close()
    return Dict,len(lines)

def training_output(arr,num): 
    
    arrtrans = np.array(arr).transpose()
    mean = []
    std_dev = []
    #print(arrtrans)
    for i in range(len(arrtrans) - 1):
        x = 0
        for j in range(len(arrtrans[i])):
            x += float(arrtrans[i,j])
        mean.append(x/len(arrtrans[i]))
        std_deviation = np.std([float(val) for val in arrtrans[i]], ddof=1)
        if(std_deviation < .01):
            std_dev.append(.01)
        else:
            std_dev.append(std_deviation)

    #print("Mean: ",mean)
    #print("Standard Deviation: ", std_dev)
    
    for i in range(len(mean)):
        print("Class %d, attribute %d, mean = %.2f, std = %.2f" % (num,i+1,mean[i],std_dev[i]))

    return mean,std_dev

def cal(test_cases, class_means, class_stds,priorProb,testAnsw):

    totalAcc = 0

    for idx, test_object in enumerate(test_cases):
        likelihoods = {}  # Dictionary to store likelihoods for each class

        # Calculate P(x | C) for each class
        for cls in class_means.keys():
            likelihood = 1.0
            for i, feature in enumerate(test_object):
                mean = class_means[cls][i]
                std = class_stds[cls][i]
                pdf = (1 / (np.sqrt(2 * np.pi) * std)) * np.exp(-((feature - mean) ** 2) / (2 * std ** 2))
                #print(pdf)
                likelihood *= pdf

            likelihoods[cls] = likelihood

        postProbies = {}

        for cls in class_means.keys():
            prob = likelihoods[cls]
            
            #Cal denominator P(x), which is the sum of P(x|C) * P(C) for all classes
            denom = 0
            for c in class_means.keys():
                denom += likelihoods[c] * priorProb[c]
                
            #Calculate P(C|x)
            postProb = (prob * priorProb[cls]) / denom
            postProbies[cls] = postProb


        # Test to see if there are multiple 
        counter = 0
        acc = 0
        maxProb =  max(postProbies.values())
        for key,value in postProbies.items():
            if maxProb == value:
                counter += 1

        
        #print(postProbies[testAnsw[idx]],maxProb)
        
        if counter > 1 and (postProbies[testAnsw[idx]] == maxProb):
            acc = 1.00/counter
        elif max(postProbies, key=postProbies.get) == testAnsw[idx]:
            acc = 1.00
        else:
            acc = 0.00
        
        totalAcc += acc

        print(f"ID= {format(idx+1,'4d')}, predicted= {format(max(postProbies, key=postProbies.get),'2d')}, probability = {format(max(postProbies.values()), '.4f')}, true= {format(testAnsw[idx], '2.0f')}, accuracy={format(acc,'.2f')}")


        # Calulate P(C|x)
    print(f"classification accuracy= {format(totalAcc/len(test_cases), '.4f')}")


def naive_bayes(training_file,test_file):

    priorProbofTraining = {}
    cMean = {}
    cStd = {}
    trainDict,tSize = makeDict(training_file)     #Creates a dictionary where it is sorted by class
    #print(len(trainDict))
    for i in range(max(trainDict)+1):     #i is the Class number, used max because there might be cases where 4 and 6 exist but 5 does not
    #for i in trainDict.keys():
        if i in trainDict.keys():   #Checks to see if the class is in the dictionary 
            #print(i)
            mean, std_dev = training_output(trainDict[i],i)
            cMean[i] = mean
            cStd[i] = std_dev
            priorProbofTraining[i] = (round((len(trainDict[i])/tSize)*100,4))

    #print(trainDict[1])
    
    #Test file: Starting the Testing portion
    test_cases = []
    test_answers = []
    with open(test_file, 'r') as file:
        for line in file:
            testList = [float(x) for x in line.strip().split()]
            test_cases.append(testList[:-1])
            test_answers.append(testList[-1])
    #print(priorProbofTraining)
    cal(test_cases,cMean,cStd,priorProbofTraining,test_answers)

    return 1