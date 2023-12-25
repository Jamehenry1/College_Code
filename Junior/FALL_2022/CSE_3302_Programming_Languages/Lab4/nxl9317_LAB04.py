# Nghia Lam
# 1001699317
# Windows 
# Using python 3.9.7

import os



file = open("input.txt","r")
value = ["{","}"]
tape = ["{","}","/"]
operations = ["/"]
block = ["*"]
weird = ["(",")","\""]       #for unknown situation 
stack = ['$']
depth = 0
clean = 0
check = 0
blockCom = False
quote = 0


while file:                         #This will loop through the file
									#Bases case to check if there is a comment and it starting location
    content = file.readline()      
    #print(content)

    for i in range(len(content)):
        exist_ComB = operations.count(content[i-1])
        exist_ComN = operations.count(content[i])

        blockComB = block.count(content[i-1])
        blockComN = block.count(content[i])
        #print(str(i) + " - " + str(exist_ComN) + " - " + str(exist_ComB))

        if exist_ComN == 1 and exist_ComB == 1: #This means there is a comment, next line
            break

        if exist_ComB == 1 and blockComN == 1:
            blockCom = True
        if blockComB == 1 and exist_ComN == 1:
            blockCom = False
        
        exist_werid = weird.count(content[i])
        if exist_werid == 1:
            #print("Clean")
            if content[i] == "(":
                clean = 1
                #print("clean1: " + str(clean))
            elif content[i] == ")":
                clean = 0
            elif content[i] == "\"":
                quote = quote + 1
                print("quote: " + str(quote))
                if quote == 2:
                    quote = 0

        brak = value.count(content[i])
        if brak == 1 and clean == 0 and blockCom == False and quote == 0:
            if content[i] == "{":
                stack.append(content[i])
                check = 0
            elif content[i] == "}":
                stack.pop()
                check = 1
                
        depth = len(stack) - 1

    content = content.rstrip()
    if(check == 1):
        print(str(depth + 1) + content)
        check = 0
    else:
        print(str(depth) + content)

    if depth < 0:
        print("ERROR MISSMATCH BRACKETS")
        break

    #print("\n")
    if content == "":
        break

file.close

if depth > 0:
    print("ERROR MISSMATCH BRACKETS")
