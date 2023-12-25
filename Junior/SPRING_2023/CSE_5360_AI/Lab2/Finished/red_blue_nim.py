#Nghia Lam 1001699317

import sys
import random

NUM_RED = sys.argv[1]
NUM_BLUE = sys.argv[2]
FIRST_PLAYER = sys.argv[3]
Depth = 20

test_list = ["red","blue"]

if len(sys.argv) == 4:
    print("depth is not included")
elif len(sys.argv) == 5:
    print("depth is included")
    Depth = sys.argv[4]
else:
    print("ERROR")

"""
def minimax(state,depth,alpha,beta,maximizingPlayer):
    if depth == 0 or state[0] == 0 or state[1] == 0: #If depth is 0 or red or blue marbles left is 0
        if maximizingPlayer == False:
            score = (state[1] * 3 + state[0] * 2)
        else:
            score = -(state[1] * 3 + state[0] * 2)
        print(f"score: {score}")
        print(f"Final State: {state}")
        if state[0] == 0:
            return score,"red"
        else:
            return score,"blue"
        
    
    childstate = [[state[0] - 1,state[1]],[state[0] ,state[1] -1]]
    print(f"state: {state} childState: {childstate}")
    check = 0

    if maximizingPlayer == True:
        print("Max")
        maxEval = -100000
        for child in childstate:
            eval,move = minimax(child,depth - 1,alpha,beta,False)
            maxEval = max(maxEval,eval,beta)
            if maxEval >= beta:
                return maxEval,move
            alpha = max(alpha,maxEval)
        return maxEval,move
        
    else:
        print("Min")
        minEval = 100000
        for child in childstate:
            eval,move = minimax(child, depth - 1, alpha, beta, True)
            minEval = min(minEval,eval,beta)
            if minEval <= alpha:
                return minEval,move
            beta = min(beta,minEval)
        return minEval,move

"""

def util(state): # this is the util to calculate the score

    redScore = state[0] * 2
    blueScore = state[1] * 3
    score = blueScore + redScore
    #score = max(blueScore,redScore)
    #print(f"state Test: {score}")
    return score

def childStates(state): #This gets the childstates
    #if state[0] > 0: 
    #    yield("red", [state[0] - 1 , state[1]])
    #if state[1] > 0:
    #    yield("blue", [state[0], state[1] - 1])
    return (("red",[state[0] - 1,state[1]]),("blue",[state[0] ,state[1] -1]))

def maxValue(state,alpha,beta,depth):
    if depth == 0 or state[0] == 0 or state[1] == 0: #If depth is 0 or red or blue marbles left is 0
        score = util(state)
        return score
        
    v = -float('inf')

    #childstate = ([[state[0] - 1,state[1]],[state[0] ,state[1] -1]])
    #print(f"MAX: state: {state} childState: {childstate}")

    for move, children in childStates(state):
        v = max(v, minValue(children,alpha,beta,depth - 1))

        if v >= beta:
            return v
        alpha = max(alpha,v)
    return v


def minValue(state,alpha,beta,depth):
    if depth == 0 or state[0] == 0 or state[1] == 0: #If depth is 0 or red or blue marbles left is 0
        score = util(state)
        return score
        
    v = float('inf')

    #childstate = [[state[0] - 1,state[1]],[state[0] ,state[1] -1]]
    #print(f"MIN: state: {state} childState: {childstate}")

    for move, children in childStates(state):
        v = min(v, maxValue(children,alpha,beta,depth - 1))
        if v <= alpha:
            return v
        beta = min(beta,v)
    return v

def alphaBetaDecision(state,depth):

    maxVal = float('inf')
    curminVal = float('-inf')
    finalMove = None

    #childstate = [[state[0] - 1,state[1]],[state[0] ,state[1] -1]]
    #score = maxValue(state, -float('inf'),float('inf'),20)
    #score2 = maxValue(childstate[1], -float('inf'),float('inf'),20)
    if depth == 0 or state[0] == 0 or state[1] == 0:
        return util(state)
    
    ''' Tried it with max but the return did not return a move so just gonna check min for both successors
    val = maxValue(state, float('-inf'), float('inf'), 20)

    for move, children in childStates(state):
        if util(children) == val:
            return move
    '''

    for move, children in childStates(state): #this gets the max even though we ask for min 
        minResult = minValue(children,curminVal,maxVal,depth)
        if minResult > curminVal:
            curminVal = minResult
            finalMove = move
    
    
    if state[1] == 1 and state[1] < state[0]:   #this checks with the condition when there is one marble left
        print("red check")
        finalMove = "red"
    elif state[0] == 1 and state[0] <= state[1]:
        finalMove = "blue"
    

    return finalMove

   
def red_blue(num_red,num_blue,player,depth):
    print("works")
    redScore = 0
    blueScore = 0
    state = [num_red,num_blue]
    print(state)
    if player == "p":
        player2 = "c"
    else:
        player2 = "p"
    
    while num_blue > 0 and num_red > 0:
        if player == "p":
            print(f"Your Move: Red {num_red} Blue: {num_blue}")
            move = input("Pick (red/blue)? ")
            if move == "red":
                num_red = num_red - 1 
            elif move == "blue":
                num_blue = num_blue - 1
            else:
                print("Wrong Input please put in either (red/blue): ")
                continue
            player = "c"
            state = [num_red,num_blue] 

        elif player == "c":
            print(f"Computer Move: Red {num_red} Blue: {num_blue}")
    
            move = alphaBetaDecision(state,depth)
            print(f"state {state[0]} state {state[1]}")
           
            if move == "red":
                num_red = num_red - 1 
            else:
                num_blue = num_blue - 1

            player = "p"
            state = [num_red,num_blue]

    print("Game over")
    if player == "p":
        Winner = "Human"
    elif player == "c":
        Winner = "Computer"

    blueScore = num_blue * 3
    redScore = num_red * 2
    score = blueScore + redScore
    return Winner, score

Winner,score = red_blue(int(NUM_RED),int(NUM_BLUE),FIRST_PLAYER,int(Depth))   

print(f"The Winner is {Winner} and their Score is {score}")