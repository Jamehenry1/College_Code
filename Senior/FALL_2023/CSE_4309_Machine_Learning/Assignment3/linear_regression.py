#Nghia Lam
#1001699317
#Assignment 3 Task 1

import numpy as np

def Making_matrix(tList,degree):
    finalList = []
    for sublist in tList:
        holderList = []

    # Iterate through each number in the sub-list
        for num in sublist:
            # Generate powers of the number from 1 to 3
            powers = [num**i for i in range(1, degree + 1)]

            # Extend the holderList with the powers
            holderList.extend(powers)
            
        finalList.append(holderList)

    return finalList

def linReg(tList,answers,lambda1):

    phi = np.array(tList)
    phi = np.insert(phi,0,1,axis=1)

    #Identity matrix 
    I = np.identity(phi.shape[1])

    #Weight is done THANK GOD
    weights = np.linalg.pinv(lambda1 * I + phi.T @ phi) @ phi.T @ answers
    #print(weights)
    return weights,phi

def testing(testPred,tarOut):
    for i, prediction in enumerate(testPred, start=1):
        sqrError = (prediction - tarOut[i-1]) ** 2
        print(f"ID={i:5d}, output={prediction:14.4f}, target value = {tarOut[i-1]:10.4f}, squared error = {sqrError:.4f}")

def linear_regression(training_file, test_file, degree, lambda1):

    training_cases = []
    training_answers = []
    with open(training_file, 'r') as file:
        for line in file:
            trainList = [float(x) for x in line.strip().split()]
            training_cases.append(trainList[:-1])
            training_answers.append(trainList[-1])

    #tList = If the degree is 2, then φ(x) = (1, x1, (x1)2, x2, (x2)2..., xD, (xD)2)T
    tList = Making_matrix(training_cases,degree)

    #This gets the weight
    trainWeight,trainPhi = linReg(tList,training_answers,lambda1)
    #print(trainPhi)
    for i, weight in enumerate(trainWeight, start=0):
        print(f"w{i}={weight:.4f}")

    #for test case
    test_cases = []
    test_answers = []
    with open(test_file, 'r') as file:
        for line in file:
            testList = [float(x) for x in line.strip().split()]
            test_cases.append(testList[:-1])
            test_answers.append(testList[-1])

    #teList = If the degree is 2, then φ(x) = (1, x1, (x1)2, x2, (x2)2..., xD, (xD)2)T 
    teList = np.array(Making_matrix(test_cases,degree))
    #this is to add a one if front of each row
    teList = np.insert(teList,0,1,axis=1)

    #this is the output
    testPred = teList @ trainWeight

    testing(testPred,test_answers)

    #for test in testPred:
    #    print(f"test {test}")

    return 1