import sys
import random

NUM_RED = sys.argv[1]
NUM_BLUE = sys.argv[2]
FIRST_PLAYER = sys.argv[3]
Depth = None

test_list = ["red","blue"]

if len(sys.argv) == 4:
    print("depth is not included")
elif len(sys.argv) == 5:
    print("depth is included")
    Depth = sys.argv[4]
else:
    print("ERROR")

def util(state):
    print(f"state Test: {state[0]}")
    blueScore = state[0] * 3
    redScore = state[1] * 2
    score = blueScore + redScore
    return score

def minimax(state,depth,alpha,beta,maximizingPlayer):
    if depth == 0 or state[0] == 0 or state[1] == 0: #If depth is 0 or red or blue marbles left is 0
        #if maximizingPlayer == False:
        score = (state[1] * 3 + state[0] * 2)
        if state[0] == 0:
            print(f"score: {score} Final State: {state} RED")
            return score,"red"
        
        elif state[1] == 0:
            print(f"score: {score} Final State: {state} BLUE")
            return score,"blue"
        
    
    childstate = [[state[0] - 1,state[1]],[state[0] ,state[1] -1]]
    #print(f"state: {state} childState: {childstate}")
    check = 0

    if maximizingPlayer == True:
        print("Max")
        maxEval = -100000
        for child in childstate:
            eval,move = minimax(child,depth,alpha,beta,False)
            maxEval = max(maxEval,eval)
            if maxEval >= beta:
                return maxEval,move
            alpha = max(alpha,maxEval)
        return maxEval,move
        
    else:
        print("Min")
        minEval = 100000
        for child in childstate:
            eval,move = minimax(child, depth, alpha, beta, True)
            minEval = min(minEval,eval)
            if minEval <= alpha:
                return minEval,move
            beta = min(beta,minEval)
        return minEval,move



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
            move = input("Pick (red/blue)?")
            if move == "red":
                num_red = num_red - 1 
            if move == "blue":
                num_blue = num_blue - 1
            player = "c"
            state = [num_red,num_blue] 

        elif player == "c":
            print(f"Computer Move: Red {num_red} Blue: {num_blue}")
            maxScore = -10000
            red_score = 0
            blue_score = 0
            #move = random.choice(test_list)
            #if player2 == "c":
            #    score,move = minimax(state,20,-100000,100000,False)
            #else:
            score,move = minimax(state,20,-100000,100000,True)
            childstate = [[num_red - 1, num_blue], [num_red, num_blue - 1]]
            print(f"childstate check {childstate[0]}")
            if util(childstate[0]) == score:
                move = "red"
            elif util(childstate[1]) == score:
                move = "blue"
            #print(f"MoveScore: {moveScore}")
            """
            childstate = [[num_red - 1, num_blue], [num_red, num_blue - 1]]
            red_score,move = minimax(childstate[0],20,-100000,100000,False)
            blue_score,move = minimax(childstate[1],20,-100000,100000,False)
            print(f"RedScore: {red_score} BlueScore {blue_score}")
            if red_score > blue_score:
                move = "red"
                print("This is going red")
            else:
                move = "blue"
                print("This is going blue")
            """
            #for child in childstate:
            #    score,move = minimax(child,20,-100000,100000,False)
            #    if score > maxScore:
            #       maxScore = score
            #    print(f"MoveScore: {score}")
            #if child == childstate[0]:
            #    print(f"child: {child} ChildState: {childstate[0]}")
            #    move = "red"
            #else:
            #    print(f"child: {child} ChildState: {childstate[1]}")
            #    move = "blue"

            print(move)
            if move == "red":
                num_red = num_red - 1 
            if move == "blue":
                num_blue = num_blue - 1
            player = "p"
            state = [num_red,num_blue]

        print(f"This is the current State: {state}")

    print("Game over")
    if player == "c":
        Winner = "Human"
    elif player == "p":
        Winner = "Computer"

    blueScore = num_blue * 3
    redScore = num_red * 2
    score = blueScore + redScore
    return Winner, score

Winner,score = red_blue(int(NUM_RED),int(NUM_BLUE),FIRST_PLAYER,Depth)    

print(f"The Winner is {Winner} and their Score is {score}")
