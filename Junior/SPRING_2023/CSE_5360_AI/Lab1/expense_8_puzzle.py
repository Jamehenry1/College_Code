import sys
#import numpy as np
from copy import deepcopy
import time

class Node:
    def __init__(self, curNode, befNode, moveDir, g, h, depth,moveNum):
        self.curNode = curNode
        self.befNode = befNode
        self.moveDir = moveDir
        self.g = g      #G(cost of move each each piece) 
        self.h = h      #H(number of steps needed to reach goal state * number)
        self.fn = g + h
        self.depth = depth
        self.moveNum = moveNum
# This is to get the start and goal file
try:
    f1 = open(sys.argv[1],"r")
    f2 = open(sys.argv[2],"r")

    if len(sys.argv) == 3:
        algor = "a*"
        dump = 0
    elif len(sys.argv) == 4 and (sys.argv[3] == "1" or sys.argv[3] == "0"):
        algor = "a*"
        dump = int(sys.argv[3])
    else:
        algor = sys.argv[3]
        dump = 0
    
    if len(sys.argv) == 5:
        dump = int(sys.argv[4])

    line1 = f1.readlines()
    line2 = f2.readlines()
    startFile = []
    goalFile = []
    for x in (line1[:3]):
        startFile.append(x.strip().split(' '))
    for x in (line2[:3]):
        goalFile.append(x.strip().split(' '))
except FileNotFoundError:
    print('Input file not found')
    sys.exit()
except IndexError:
    print('Did not format the command line correctly, missing a condition')
    sys.exit()

timestr = "trace-" + time.strftime(("%Y_%m_%d-%H_%M_%S") + ".txt")
print(timestr)

if dump == 1:
    writeFile = open(timestr,"w")
    #commandline argument
    writeFile.write("Command Line Argument: " + str(sys.argv) + "\n")
    #method Selected
    writeFile.write("Method Selected: " + algor + "\n" + "Running: " + algor + "\n")

closed = []
fringe = []

#helps write the node using recusion 
def beforeChecker(node):
    writeFile.write("Parent = < state = " + str(node.curNode) 
                        + ", Action = {Move " + str(node.moveNum) + " " + str(node.moveDir)
                        + "} g(n) = " + str(node.g)
                        + " h(n) = " + str(node.h)
                        + " f(n) = " + str(node.fn)
                        + " Depth = " + str(node.depth) + ">\n")
    if(node.befNode != 0):
            #print(node.befNode.curNode)
            beforeChecker(node.befNode)

#writes the node
def dumpWriteOut(node,nodeGen):
    #print("work")
    #curNode, befNode, moveDir, g, h, depth,moveNum
    #Generating successor to state
    writeFile.write("\nGenerating successors to < state = " + str(node.curNode)
                    + ", g(n) = " + str(node.g)
                    + ", h(n) = " + str(node.h)
                    + ", f(n) = " + str(node.fn)
                    + ", depth = " + str(node.depth) + " >:\n")
                    #+ "Parent = " + str(node.befNode.curNode))
    writeFile.write(str(nodeGen) + " successors generated\n")
    #in closed set
    writeFile.write("Closed: " + str(closed))
    #in fringe
    writeFile.write("\nFringe: ")
    for i in range(len(fringe)):
        writeFile.write("\n< state = " + str(fringe[i].curNode) 
                        + ", Action = {Move " + str(fringe[i].moveNum) + " " + str(fringe[i].moveDir)
                        + "} g(n) = " + str(fringe[i].g)
                        + " h(n) = " + str(fringe[i].h)
                        + " f(n) = " + str(fringe[i].fn)
                        + " Depth = " + str(fringe[i].depth) + "\n")
        if(fringe[i].befNode.curNode != 0):
            #print(fringe[i].befNode.curNode)
            beforeChecker(fringe[i].befNode)


#finds the index of a number 
def findNum(puzzle, num):
    for i in range(3):
        for j in range(3):
            #print(puzzle[i][j])
            if int(puzzle[i][j]) == num:
                return (i,j)

#finds the cost of h: it is now more like a compare fucntion now lol
def hCost(puzzle,goal):
    h = 0
    for i in range(3):
        for j in range(3):
            cPos = findNum(puzzle,int(puzzle[i][j]))
            gPos = findNum(goal,int(puzzle[i][j]))
            val = abs(cPos[0]-gPos[0]) + abs(cPos[1]-gPos[1])
            h += val
    return h

#finds the cost of h 
def realHCost(puzzle,goal):
    h = 0
    num = 0 
    for i in range(3):
        for j in range(3):
            num = int(puzzle[i][j])
            cPos = findNum(puzzle,int(puzzle[i][j]))
            gPos = findNum(goal,int(puzzle[i][j]))
            val = (abs(cPos[0]-gPos[0]) + abs(cPos[1]-gPos[1])) * num
            h += val
    return h

DIRECTIONS = {"U": [-1, 0], "D": [1, 0], "L": [0, -1], "R": [0, 1]}

def nodeCreate(newPuzzle,node, zeroPos, newZeroPos,dir):
    numChange = node.curNode[newZeroPos[0]][newZeroPos[1]]
    newPuzzle[zeroPos[0]][zeroPos[1]] = node.curNode[newZeroPos[0]][newZeroPos[1]]
    newPuzzle[newZeroPos[0]][newZeroPos[1]] = 0
    #print(node.curNode)
    #def __init__(self, curNode, befNode, moveDir, g, h, depth,moveNum)
    fringe.append(Node(newPuzzle,node,dir,node.g+int(numChange),realHCost(newPuzzle,goalFile),node.depth+1, numChange))

#check each direction
#create it as a node so that possble direction can represent a state
def direction(node,puzzle):
    zeroPos = findNum(node.curNode,0)
    newZeroPos = [0,0]
    nodeGen = 0
    
    if zeroPos[0] > 0: #0 can move up 
        #print("up")
        newZeroPos = (zeroPos[0] + DIRECTIONS['U'][0], zeroPos[1] + DIRECTIONS['U'][1])

        newPuzzle = deepcopy(node.curNode)
        nodeCreate(newPuzzle, node, zeroPos,newZeroPos,"down")
        nodeGen = nodeGen + 1

    if zeroPos[0] < 2: #0 can move down 
        #print("down")
        newZeroPos = (zeroPos[0] + DIRECTIONS['D'][0], zeroPos[1] + DIRECTIONS['D'][1])
        
        newPuzzle = deepcopy(node.curNode)
        nodeCreate(newPuzzle, node, zeroPos,newZeroPos,"up")
        nodeGen = nodeGen + 1

    if zeroPos[1] > 0: #0 can move left
        #print("left")
        newZeroPos = (zeroPos[0] + DIRECTIONS['L'][0], zeroPos[1] + DIRECTIONS['L'][1])
        newPuzzle = deepcopy(node.curNode)
        nodeCreate(newPuzzle, node, zeroPos,newZeroPos,"right")
        nodeGen = nodeGen + 1

    if zeroPos[1] < 2: #0 can move right
        #print("right")
        newZeroPos = (zeroPos[0] + DIRECTIONS['R'][0], zeroPos[1] + DIRECTIONS['R'][1])
        newPuzzle = deepcopy(node.curNode)
        nodeCreate(newPuzzle, node, zeroPos,newZeroPos,"left")
        nodeGen = nodeGen + 1 

    if dump == 1:
        dumpWriteOut(node,nodeGen)

    return nodeGen

#basic print so that I can see what is in the fringe
def printer():
    print("fringe:")
    for i in range(len(fringe)):
        print(str(fringe[i].curNode) + " Move Num: " + str(fringe[i].moveNum) + " " +str(fringe[i].g)) 
    #print("closed:")
    #for j in range(len(closed)):
    #    print(closed[j])

#this is to print out my steps or moves if there is a solution 
def LooperPrint(node,depth):
    holdList = []

    if algor == 'bfs':
        print("Solution Found at depth " + str(node.depth))
    elif algor == 'ucs':
        print("Solution Found at depth " + str(node.depth) +" with cost of " + str(node.g))
    elif algor == 'a*':
        print("Solution Found at depth " + str(node.depth) +" with cost of " + str(node.fn))
    elif algor == 'dfs':
        print("Solution Found at depth " + str(node.depth))
    elif algor == 'greedy':
        print("Solution Found at depth " + str(node.depth))
    elif algor == 'dls':
        print("Solution Found at depth " + str(node.depth))
    elif algor == 'ids':
        print("Solution Found at depth " + str(node.depth))  


    for i in range(depth):
        #print(str(node.curNode) + "Move " + str(node.moveNum) + " " + str(node.moveDir))
        holdList.append("Move " + str(node.moveNum) + " " + str(node.moveDir))
        node = node.befNode

    holdList.reverse()
    for j in range(len(holdList)):
        print(holdList[j])

#Prints out the basic info
def infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize):
    print("Nodes Popped: " + str(nodePop))
    print("Nodes Expanded: " + str(nodeExpanded))
    print("Nodes Generated: " + str(nodeGenerated))
    print("Max Fringe Size: " + str(maxFrigeSize))

def ucsSortCondidtion(val):
    return val.g

def bfs(puzzle):

    nodePop = 0
    nodeExpanded = 0                    #This is how many times expantions happened
    nodeGenerated = 0                   #this the total amount of nodes
    maxFrigeSize = 0

    finish = False
    fringe.append(Node(puzzle,0,0,0,0,0,0))
    
    #for i in range(20):
    while finish != True:
        if not fringe:                  #checks to see if the fringe is empty     
            return "nothing in fringe"
        if maxFrigeSize < len(fringe):
            maxFrigeSize = len(fringe)

        workingNode = fringe.pop(0)     #pops the node out of the fringe (FIFO)
        nodePop = nodePop + 1           #adds up how many nodes were poped

        #Goal test im using hCost to check if they are all in the right place
        if hCost(workingNode.curNode,goalFile) == 0:
            finish = True
            infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize)
            LooperPrint(workingNode,workingNode.depth)
            return True
        
        #Checks to see if it is in the closed set
        if closed.count(workingNode.curNode) == 0:  
            closed.append(workingNode.curNode)      #print("addded in closed")
            nodeExpanded = nodeExpanded + 1         #increase the amount of nodes expanded
            #print(workingNode.curNode)
            nodeGenerated = direction(workingNode,workingNode.curNode) + nodeGenerated

def dfs(puzzle):

    nodePop = 0
    nodeExpanded = 0    #This is how many times expantions happened
    nodeGenerated = 0   #this the total amount of nodes
    maxFrigeSize = 0

    finish = False
    fringe.append(Node(puzzle,0,0,0,0,0,0))

    #for i in range(20):
    while finish != True:
        if not fringe:  #checks to see if the fringe is empty     
            return "nothing in fringe"
        if maxFrigeSize < len(fringe):
            maxFrigeSize = len(fringe)

        workingNode = fringe.pop()  #pops the node out of the fringe (FILO)
        nodePop = nodePop + 1       #adds up how many nodes were poped

        #Goal test im using hCost to check if they are all in the right place
        if hCost(workingNode.curNode,goalFile) == 0:
            finish = True
            infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize)
            LooperPrint(workingNode,workingNode.depth)
            return True
        
        #Checks to see if it is in the closed set
        if closed.count(workingNode.curNode) == 0:  
            closed.append(workingNode.curNode)      #print("addded in closed")
            nodeExpanded = nodeExpanded + 1         #increase the amount of nodes expanded
            #print(workingNode.curNode)
            nodeGenerated = direction(workingNode,workingNode.curNode) + nodeGenerated
        
def dls(puzzle):

    nodePop = 0
    nodeExpanded = 0    #This is how many times expantions happened
    nodeGenerated = 0   #this the total amount of nodes
    maxFrigeSize = 0
    print("Enter Depth: ")
    finalDepth = input() 
    
    finish = False
    fringe.append(Node(puzzle,0,0,0,0,0,0))

    #for i in range(20):
    while finish != True:
        if not fringe:  #checks to see if the fringe is empty     
            return "nothing in fringe: Failed to search"
        if maxFrigeSize < len(fringe):
            maxFrigeSize = len(fringe)

        workingNode = fringe.pop()  #pops the node out of the fringe (FILO)
        nodePop = nodePop + 1       #adds up how many nodes were poped
    
        #Goal test im using hCost to check if they are all in the right place
        if hCost(workingNode.curNode,goalFile) == 0:
            finish = True
            infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize)
            LooperPrint(workingNode,workingNode.depth)
            return True
        
        
        if int(finalDepth) >= int(workingNode.depth):
            #print(workingNode.depth)
            #Checks to see if it is in the closed set
            if closed.count(workingNode.curNode) == 0:  
                closed.append(workingNode.curNode)      #print("addded in closed")
                nodeExpanded = nodeExpanded + 1         #increase the amount of nodes expanded
                #print(workingNode.curNode)
                nodeGenerated = direction(workingNode,workingNode.curNode) + nodeGenerated

def ids(puzzle,finalDepth):

    nodePop = 0
    nodeExpanded = 0    #This is how many times expantions happened
    nodeGenerated = 0   #this the total amount of nodes
    maxFrigeSize = 0
    
    finish = False
    fringe.append(Node(puzzle,0,0,0,0,0,0))

    #for i in range(20):
    while finish != True:
        if not fringe:  #checks to see if the fringe is empty     
            return False
        if maxFrigeSize < len(fringe):
            maxFrigeSize = len(fringe)

        workingNode = fringe.pop()  #pops the node out of the fringe (FILO)
        nodePop = nodePop + 1       #adds up how many nodes were poped
    
        #Goal test im using hCost to check if they are all in the right place
        if hCost(workingNode.curNode,goalFile) == 0:
            finish = True
            infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize)
            LooperPrint(workingNode,workingNode.depth)
            return True
        
        
        if int(finalDepth) >= int(workingNode.depth):
            #print(workingNode.curNode)
            #Checks to see if it is in the closed set
            if closed.count(workingNode.curNode) == 0:  
                closed.append(workingNode.curNode)      #print("addded in closed")
                nodeExpanded = nodeExpanded + 1         #increase the amount of nodes expanded
                #print(workingNode.curNode)
                nodeGenerated = direction(workingNode,workingNode.curNode) + nodeGenerated

def ucs(puzzle):
    nodePop = 0
    nodeExpanded = 0                    #This is how many times expantions happened
    nodeGenerated = 0                   #this the total amount of nodes
    maxFrigeSize = 0

    finish = False
    fringe.append(Node(puzzle,0,0,0,0,0,0))

    #for i in range(3):
    while finish != True:
        if not fringe:                  #checks to see if the fringe is empty     
            return "nothing in fringe"
        if maxFrigeSize < len(fringe):
            maxFrigeSize = len(fringe)

        fringe.sort(key=ucsSortCondidtion)
        #printer()
        workingNode = fringe.pop(0)     #pops the node out of the fringe (FIFO)
        nodePop = nodePop + 1           #adds up how many nodes were poped

        #Goal test im using hCost to check if they are all in the right place
        if hCost(workingNode.curNode,goalFile) == 0:
            finish = True
            infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize)
            LooperPrint(workingNode,workingNode.depth)
            return True
        
        #Checks to see if it is in the closed set
        if closed.count(workingNode.curNode) == 0:  
            closed.append(workingNode.curNode)      #print("addded in closed")
            nodeExpanded = nodeExpanded + 1         #increase the amount of nodes expanded
            #print(workingNode.curNode)
            nodeGenerated = direction(workingNode,workingNode.curNode) + nodeGenerated

def greedySortCondidtion(val):
    return val.h

def greedy(puzzle):
    nodePop = 0
    nodeExpanded = 0                    #This is how many times expantions happened
    nodeGenerated = 0                   #this the total amount of nodes
    maxFrigeSize = 0

    finish = False
    fringe.append(Node(puzzle,0,0,0,0,0,0))

    #for i in range(3):
    while finish != True:
        if not fringe:                  #checks to see if the fringe is empty     
            return "nothing in fringe"
        if maxFrigeSize < len(fringe):
            maxFrigeSize = len(fringe)

        fringe.sort(key=greedySortCondidtion)
        #printer()
        workingNode = fringe.pop(0)     #pops the node out of the fringe (FIFO)
        nodePop = nodePop + 1           #adds up how many nodes were poped

        #Goal test im using hCost to check if they are all in the right place
        if hCost(workingNode.curNode,goalFile) == 0:
            finish = True
            infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize)
            LooperPrint(workingNode,workingNode.depth)
            return True
        
        #Checks to see if it is in the closed set
        if closed.count(workingNode.curNode) == 0:  
            closed.append(workingNode.curNode)      #print("addded in closed")
            nodeExpanded = nodeExpanded + 1         #increase the amount of nodes expanded
            #print(workingNode.curNode)
            nodeGenerated = direction(workingNode,workingNode.curNode) + nodeGenerated

def aStarSortCondidtion(val):
    return val.fn

def aStar(puzzle):
    nodePop = 0
    nodeExpanded = 0                    #This is how many times expantions happened
    nodeGenerated = 0                   #this the total amount of nodes
    maxFrigeSize = 0

    finish = False
    fringe.append(Node(puzzle,0,0,0,0,0,0))

    #for i in range(3):
    while finish != True:
        if not fringe:                  #checks to see if the fringe is empty     
            return "nothing in fringe"
        if maxFrigeSize < len(fringe):
            maxFrigeSize = len(fringe)

        fringe.sort(key=aStarSortCondidtion)
        #printer()
        workingNode = fringe.pop(0)     #pops the node out of the fringe (FIFO)
        nodePop = nodePop + 1           #adds up how many nodes were poped

        #Goal test im using hCost to check if they are all in the right place
        if hCost(workingNode.curNode,goalFile) == 0:
            finish = True
            infoPrint(nodePop,nodeExpanded,nodeGenerated,maxFrigeSize)
            LooperPrint(workingNode,workingNode.depth)
            
            return True
        
        #Checks to see if it is in the closed set
        if closed.count(workingNode.curNode) == 0:  
            closed.append(workingNode.curNode)      #print("addded in closed")
            nodeExpanded = nodeExpanded + 1         #increase the amount of nodes expanded
            #print(workingNode.curNode)
            nodeGenerated = direction(workingNode,workingNode.curNode) + nodeGenerated

def main(puzzle):
    works = False

    if algor == 'bfs':
        works = bfs(puzzle)
        print("bfs")
    elif algor == 'ucs':
        print("ucs")
        works = ucs(puzzle)
    elif algor == 'a*':
        works = aStar(puzzle)
        print("a*")
    elif algor == 'dfs':
        works = dfs(puzzle)
        print(works)
    elif algor == 'dls':
        works = dls(puzzle)
        print(works)
    elif algor == 'greedy':
        works = greedy(puzzle)
        print("greedy")
    elif algor == 'ids':
        print("Enter Depth for ids: ")
        finalDepth = input() 
        for i in range(int(finalDepth) + 1):
            works = ids(puzzle,i)
            if dump == 1:
                if works == False:
                    writeFile.write("\nnothing in fringe: Failed to search " + str(i) + "\n")
            #print(works)
            closed.clear()
            fringe.clear()
    else:
        print("No such algorithm")

start = main(startFile)
#print(len(sys.argv))
#print(dump)
if dump == 1:
    writeFile.close()