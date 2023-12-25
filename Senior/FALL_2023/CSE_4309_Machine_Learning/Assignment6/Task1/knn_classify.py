# Nghia Lam
# 1001699317

import numpy as np
from uci_data import *

def meanAndStdAndTrans(trainInputs,testInputs):
    inputTransposed = trainInputs.T
    testTransposed = testInputs.T
    meanVal = []
    standardDev = []


    for i in range(len(inputTransposed)):
        meanVal.append(sum(inputTransposed[i])/len(inputTransposed[i]))
        if (np.std(inputTransposed[i], axis = 0,ddof = 1)) == 0:
            standardDev.append(1)
        else:
            standardDev.append(np.std(inputTransposed[i], axis = 0,ddof = 1))
    
    #print(meanVal)
    #print(standardDev)

    return meanVal, standardDev, inputTransposed, testTransposed
        

def normalize(trainInputs,testInputs):
    # F(v) = (v - mean) / std
    trainNomArr = []
    testNomArr = []
    meanVal, standardDev, inputTransposed,testTransposed = meanAndStdAndTrans(trainInputs,testInputs)

    for i in range(len(inputTransposed)):
        valTrain = []
        
        for j in range(len(inputTransposed[i])):
            Vtrain = (inputTransposed[i][j] - meanVal[i])/standardDev[i]
            valTrain.append(Vtrain)
    
        trainNomArr.append(valTrain)
        
    for i in range(len(testTransposed)):
        valTest = []
        for j in range(len(testTransposed[i])):
            Vtest = (testTransposed[i][j] - meanVal[i])/standardDev[i]
            valTest.append(Vtest)

        testNomArr.append(valTest)

    #for i in range(len(nomArr)):
    #print(nomArr[0])
    return np.array(trainNomArr).T,np.array(testNomArr).T

def classification(trainingNom,testNom,training_labels,test_labels,k):
    replace = 1000

    classAcc = 0
    for i in range(len(testNom)):
        lowest = []
        lowestLabel = []
        L2 = []
        for j in range(len(trainingNom)):
            x = testNom[i] - trainingNom[j]
            L2.append(np.dot(x,x))

        #print(L2)
        for j in range(k):
            lowVal = min(L2)
            lowIndex = L2.index(min(L2))
            L2[lowIndex] = 10000
            lowest.append(lowVal)
            lowestLabel.append(training_labels[lowIndex][0])
        
        if k == 1:
            predicted_class = lowestLabel[0]
            true_class = test_labels[i][0]
        
            if predicted_class == true_class:
                accuracy = 1
            else:
                accuracy = 0
        else:
            true_class = test_labels[i][0]
            uniqueLables,count = np.unique(lowestLabel,return_counts= True)
            maxVal = max(count)
            tied = []
            for l in range(len(uniqueLables)):
                if count[l] == maxVal:
                    tied.append(uniqueLables[l])
            
            if true_class in tied:
                accuracy = 1/len(tied)
            else:
                accuracy = 0
            predicted_class = np.random.choice(tied)
        classAcc += accuracy
        print('ID={:5d}, predicted={:3d}, true={:3d}, accuracy={:4.2f}'.format(i+1, predicted_class, true_class, accuracy))
    
    print("classification accuracy={:0.4f}".format(classAcc/len(testNom)))
    #for L in L2:
    #print("L2: {}".format(L2))


def knn_classify(training_file, test_file, k):
    #print(training_file)
    #print(test_file)

    (training_set, test_set) = read_uci1(training_file, test_file)
    (training_inputs, training_labels) = training_set
    (test_inputs, test_labels) = test_set

    trainingNom,testNom = normalize(training_inputs,test_inputs)
    #testNom = normalize(test_inputs)

    classification(trainingNom,testNom,training_labels,test_labels,k)
