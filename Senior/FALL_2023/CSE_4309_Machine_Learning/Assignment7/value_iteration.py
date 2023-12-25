# Nghia Lam
# 1001699317

import numpy as np
import copy

class Node:
    def __init__(self,value,terminal):
        self.value = value
        self.terminalVal = terminal
        
        # Thought I need this, yeah nah lol
        self.up = None
        self.down = None
        self.right = None
        self.left = None

        self.chosenDir = None
        self.chosenVal = None

def DirVal(i,j,map):
    # Checks if the direction is achivable and give it a based on the condition
    if (0 <= i+1 < len(map)) and (map[i+1][j].value != "X"):
        dVal = map[i+1][j].value
    else:
        dVal = map[i][j].value

    if (0 <= i-1 < len(map)) and (map[i-1][j].value != "X"):
        uVal = map[i-1][j].value
    else:
        uVal = map[i][j].value
    
    if (0 <= j-1 < len(map[i])) and (map[i][j-1].value != "X"):
        lVal = map[i][j-1].value
    else:
        lVal = map[i][j].value

    if (0 <= j+1 < len(map[i])) and (map[i][j+1].value != "X"):
        rVal = map[i][j+1].value
    else:
        rVal = map[i][j].value
    
    return float(rVal),float(lVal),float(uVal),float(dVal)

def MapUpdate(map,Umap):
    for i in range(len(map)):
        for j in range(len(map[i])):
            map[i][j].value = Umap[i][j]

def find_optimal_action(Umap, i, j,map):

    if Umap[i][j] in [1, -1]:
        # Terminal state, represented by 'o'
        return 'o'
    rVal,lVal,uVal,dVal = DirVal(i,j,map)
    actions = {}
    # Check all possible actions and get the weighted utility
    if i > 0 and Umap[i-1][j] != 'X' and Umap[i-1][j] != 0:
        actions['^'] = (.8 * uVal + .1*lVal + .1*rVal)
    if i < len(Umap) - 1 and Umap[i+1][j] != 'X' and Umap[i+1][j] != 0:
        actions['v'] = (.8 * dVal + .1*lVal + .1*rVal)
    if j > 0 and Umap[i][j-1] != 'X' and Umap[i][j-1] != 0:
        actions['<'] = (.8 * lVal + .1*uVal + .1*dVal)
    if j < len(Umap[0]) - 1 and Umap[i][j+1] != 'X' and Umap[i][j+1] != 0:
        actions['>'] = (.8 * rVal + .1*uVal + .1*dVal)

    # Return the action that has the highest utility, or 'X' if no action is possible
    if actions:
        return max(actions, key=actions.get)
    else:
        return 'X'

def generate_optimal_policy(Umap,map):

    policy_map = []
    for i in range(len(Umap)):
        policy_row = []
        for j in range(len(Umap[0])):
            if Umap[i][j] == 'X':
                policy_row.append('X')  # Obstacle
            elif Umap[i][j] == 0:
                policy_row.append('X')  # No action for zero utility
            else:
                optimal_action = find_optimal_action(Umap, i, j,map)
                policy_row.append(optimal_action)
        policy_map.append(policy_row)

    formatedRows = [" ".join(f"{str(val):6.3s}" for val in row) for row in policy_map]

    return formatedRows


def Prob(map,ntr,gamma,K,mapStart):

    states = {"upState": 0,"downState":0, "rightState": 0, "leftState": 0}
    Umap = copy.deepcopy(mapStart)
    for k in range(K):
        #upState,downState,rightState,leftState = 0
        for i in range(len(map)):
            for j in range(len(map[i])):
                maxState = 0
                if map[i][j].terminalVal == False:
                    rVal,lVal,uVal,dVal = DirVal(i,j,map)
                    #print("test:",i,rVal,lVal,uVal,dVal)
                    states["upState"] = ntr + gamma * (.8 * uVal + .1*lVal + .1*rVal)
                    states["downState"] = ntr + gamma * (.8 * dVal + .1*lVal + .1*rVal)
                    states["rightState"] = ntr + gamma * (.8 * rVal + .1*uVal + .1*dVal)
                    states["leftState"] = ntr + gamma * (.8 * lVal + .1*uVal + .1*dVal)
                    
                    maxState = max(states,key=states.get)
                    Umap[i][j] = states[maxState]
        #print(Umap)
        MapUpdate(map,Umap)

    # Changes the values of the map for printing
    for i in range(len(Umap)):
        for j in range(len(Umap[i])):
            if Umap[i][j] == "1.0":
                Umap[i][j] = 1.0
            if Umap[i][j] == "-1.0":
                Umap[i][j] = -1.0
            if Umap[i][j] == "X":
                Umap[i][j] = 0
            

    formatedRows = [" ".join(f"{float(val):6.3f}" for val in row) for row in Umap]

    print("\nutilities:")
    for row in formatedRows:
        print(row)
    
    optimal_policy = generate_optimal_policy(Umap,map)
    print("\npolicy:")
    for row in optimal_policy:
        print("    ",row)
            

def value_iteration(data_file, ntr, gamma, K):
    mapStart = []
    nodeMap = []
    with open(data_file, 'r') as file:
        for line in file:
            data = [x for x in line.strip().split(",")]
            mapStart.append(data)
            #nodeMap.append(data)
    nodeMap = copy.deepcopy(mapStart)
    for i in range(len(mapStart)):
        for j in range(len(mapStart[i])):
            if mapStart[i][j] == ".":
                mapStart[i][j] = 0 
                nodeMap[i][j] = Node(mapStart[i][j],False)
            else:
                nodeMap[i][j] = Node(mapStart[i][j],True)

    # for i in range(len(nodeMap)):
    #     for j in range(len(nodeMap[i])):
    #         print(nodeMap[i][j].value)

    Prob(nodeMap,ntr,gamma,K,mapStart)
    #print(DirVal(0,0,nodeMap))

    #print(nodeMap)
    



    