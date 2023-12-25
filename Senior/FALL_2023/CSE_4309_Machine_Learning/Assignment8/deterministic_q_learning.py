#Nghia Lam
#1001699317

import numpy as np
import copy

def eta(N):
    return 20 / (19 + N)

def Q_Learning_Update(Q, N_s_a, s, a, r_prime,r, s_prime, gamma,environment):
    if is_terminal(s_prime,environment):  # Check if s' is a terminal state
        Q[s_prime, None] = r_prime  # Use r' for the reward of terminal state
    if s is not None:  # Check if s is not null
        N_s_a[s, a] += 1
        
        # Calculate the learning rate c
        c = eta(N_s_a[s, a])

        # Find the max Q-value for the next state across all possible actions
        if is_terminal(s_prime,environment):
            max_q = r_prime
        else:
            max_q = max([Q[s_prime, next_a] for next_a in ['up', 'down', 'left', 'right']])
        #max_q = max([Q.get((s_prime, next_a), 0) for next_a in ['up', 'down', 'left', 'right']])
        #rVal,lVal,uVal,dVal = DirVal(s,environment)
        # Update the Q-value for the current state-action pair
        Q[s, a] = (1 - c) * Q[s, a] + (c * (r + (gamma * max_q)))


def AgentModel_Q_Learning_Deterministic(environment_file, actions_file, 
                                    ntr, gamma, number_of_moves):
    mapStart = []
    actionsFile = []
    non_terminal_reward = ntr
    with open(environment_file, 'r') as file:
        for line in file:
            data = [x for x in line.strip().replace(" ","").split(",")]
            mapStart.append(data)
    
    with open(actions_file, 'r') as file:
        for line in file:
            data = [x for x in line.strip().replace(" ","").split(",")]
            actionsFile.append(data)

    mapFinished = copy.deepcopy(mapStart)
    # Initialize Q and N_s_a
    Q = {}
    N_s_a = {}
    # Initialize other variables
    moves = 0
    initial_state = None
    state_action_pairs = []

    for i, row in enumerate(mapStart):
        for j, cell in enumerate(row):
            if cell == 'I':
                initial_state = (i, j)
                for action in ['up', 'down', 'left', 'right']:
                    state_action_pairs.append(((i, j), action))
            elif cell == '.' or cell == 'I'or cell == '1.0'or cell == '-1.0':
                for action in ['up', 'down', 'left', 'right']:
                    state_action_pairs.append(((i, j), action))

    
    for state, action in state_action_pairs:
        Q[state, action] = 0
        N_s_a[state, action] = 0
    
    # Begin the main loop
    while moves < number_of_moves:
        s = None
        r = 0
        a = None
        s_prime = initial_state
        
        while moves < number_of_moves:
            # SenseStateAndReward() can be simulated here
            
            if s == None:
                s_prime, r_prime = SenseStateAndReward1(s, mapStart, non_terminal_reward,initial_state)
            # Execute one step of Q-Learning
            # for action in ['up', 'down', 'left', 'right']:
            #     if a == action:
            Q_Learning_Update(Q, N_s_a, s, a, r_prime,r, s_prime, gamma,mapStart)
            
            # If s_prime is terminal, restart from initial state
            if is_terminal(s_prime, mapStart):
                #reset defualt start over
                s = None
                r = 0
                a = None
                #maybe break?
                #break
            else:
                #a = max(["up", "down", "left", "right"], key= lambda a_prime: (f(Q[(s_prime,a_prime)], N_s_a[(s_prime,a_prime)],Ne), random.random()))
                a = actionsFile[moves][2]
                if a == "<":
                    a = "left"
                elif a == ">":
                    a = "right"
                elif a == "^":
                    a = "up"
                else:
                    a = "down"

                state = (int(actionsFile[moves][3]),int(actionsFile[moves][4]))
                moves += 1
                s_n, r_n = SenseStateAndReward(state, mapStart, non_terminal_reward)
                s = s_prime
                r = r_prime
                s_prime = s_n
                r_prime = r_n

        
    for i in range(len(mapStart)):
        for j in range(len(mapStart[0])):
            actions = ["up", "down", "left", "right"]
            state = (i,j)
            if mapStart[i][j] == "X":
                mapStart[i][j] = 0
            if mapStart[i][j] == "-1.0":
                mapStart[i][j] = -1.0
            if mapStart[i][j] == "1.0":
                mapStart[i][j] = 1.0
            #print(state,any((state, action) in Q for action in actions))
            if any((state, action) in Q for action in actions):
                best_action = max(["up", "down", "left", "right"], key=lambda a: Q[state, a])
                #print(best_action, Q[state,best_action],Q[state,"up"],Q[state,"down"],Q[state,'left'],Q[state,'right'])
                if mapStart[state[0]][state[1]] != "X" and mapStart[state[0]][state[1]] != 0: 
                    if mapStart[state[0]][state[1]] != 1.0 and mapStart[state[0]][state[1]] != -1.0:
                        mapStart[state[0]][state[1]] = Q[state,best_action]
                        if best_action == "up":
                            mapFinished[state[0]][state[1]] = "^"
                        elif best_action == "down":
                            mapFinished[state[0]][state[1]] = "v"
                        elif best_action == "right":
                            mapFinished[state[0]][state[1]] = ">"
                        else:
                            mapFinished[state[0]][state[1]] = "<"
                    else:
                        mapFinished[state[0]][state[1]] = "o"
                        
    formatedRows = [" ".join(f"{float(val):6.3f}" for val in row) for row in mapStart]

    print("\nutilities:")
    for row in formatedRows:
        print(row)
    
    return Q


def is_terminal(state, environment):
    i = state[0]
    j = state[1]
    if environment[i][j] == "-1.0" or environment[i][j] == "1.0":
        return True
    else:
        return False
    

def SenseStateAndReward(state, environment, non_terminal_reward):
    # For terminal states, return the terminal reward
    # For non-terminal states, return the non-terminal reward

    if is_terminal(state, environment):
        return state, float(environment[state[0]][state[1]])
    else:
        return state, non_terminal_reward
    
def SenseStateAndReward1(state, environment, non_terminal_reward,initial):

    if state == None:
        state = initial
    if is_terminal(state, environment):
        return state, float(environment[state[0]][state[1]])
    else:
        return state, non_terminal_reward
