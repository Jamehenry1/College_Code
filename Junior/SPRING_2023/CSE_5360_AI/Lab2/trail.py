import sys

state = [4,3]

childstate = [[state[0] - 1,state[1]],[state[0] ,state[1] -1]]

print(childstate[0][0])