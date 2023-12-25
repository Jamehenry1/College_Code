# Nghia Lam
# 1001699317
# Windows 
# Using python 3.9.7

# Conditions for working:
#   The input_RPN.txt File needs to have a space at the end of each line 

import os

file = open("input_RPN.txt","r")
value = ["1","2","3","4","5","6","7","8","9","0"]                   # Thought about this assignment as a PDA    
tape = ["1","2","3","4","5","6","7","8","9","0","+","-","*","/"]
operations = ["+","-","*","/"]
stack = ['$']

while file:                         #This will loop through the file
    content = file.readline()       #Put each line of RPN
    #print(content)
    x = content.split(" ")          #this the list
    print(x)
    error = 0


    #Do math with stack
    for i in range(len(x)):
        #print(x)
        exist_count = tape.count(x[i])

        if exist_count > 0:
            #print(x[i])
            if value.count(x[i]) > 0:       #This check if it is a number
                stack.append(int(x[i]))     #Adds it to the stack
                #print(x[i])

            elif operations.count(x[i]):    #Checks if it is an operation
                #print(x[i])
                hold1 = stack.pop()
                hold2 = stack.pop()
                if x[i] == "+":
                    stack.append(hold2+hold1)
                    #print(stack)
                if x[i] == "-":
                    stack.append(hold2-hold1)
                    #print(stack)
                if x[i] == "*":
                    stack.append(hold2*hold1)
                    #print(stack)
                if x[i] == "/":
                    #print("in div")
                    if hold1 == 0:                      #Checks for div by 0
                        print("CANNOT DIVID BY ZERO")
                        error = 1
                        break
                    else:
                        stack.append(hold2/hold1)
                    #print(stack)
            
        elif x[i] == "\n" :         #This handles new line
            #print("breaks")
            break
        elif x[i] == "":            #this handles space errors
            if i != len(x) -1 :
                error = 1
            break                   
        else:                       #This handles errors for everything else
            error = 1
            break

    
    #print(stack)
    result = stack.pop()            #pops the final result
    endCheck = len(stack)
    if endCheck > 1:                #Check the lenth of the final stack
        error = 1                   #If there exsist something other than $ that means it broke

    if endCheck == 1 and error == 0:        #prints if nothing went wrong for the RPN
        print("The Result is: " + str(result) +"\n")
    elif error == 1:
        print("ERROR IN INPUT\n")
        result = 0

    if content == "":
        break

    stack.clear()
    stack.append("$")


file.close