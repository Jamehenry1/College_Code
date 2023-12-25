#Nghia Lam
#1001699317

import numpy as np
import random
import copy

def eta(N):
    return 20 / (19 + N)

def f(u, n, Ne):
    return 1 if n < Ne else u

def Q_Learning_Update(Q, N_s_a, s, a, r_prime,r, s_prime, gamma, Ne,environment):
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


# Define the AgentModel_Q_Learning function
def AgentModel_Q_Learning(environment_file, non_terminal_reward, gamma, number_of_moves, Ne):
    mapStart = []
    
    with open(environment_file, 'r') as file:
        for line in file:
            data = [x for x in line.strip().replace(" ","").split(",")]
            mapStart.append(data)

    mapFinished = copy.deepcopy(mapStart)
    # Initialize Q and N_s_a
    Q = {}
    N_s_a = {}
    # Initialize other variables
    moves = 0
    initial_state = None
    state_action_pairs = []

    # Find the initial state and state-action pairs
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
            
            if s == None:
                s_prime, r_prime = SenseStateAndReward1(s, mapStart, non_terminal_reward,initial_state)
            # Execute one step of Q-Learning
            # for action in ['up', 'down', 'left', 'right']:
            #     if a == action:
            Q_Learning_Update(Q, N_s_a, s, a, r_prime,r, s_prime, gamma, Ne,mapStart)
            
            # If s_prime is terminal, restart from initial state
            if is_terminal(s_prime, mapStart):
                #reset defualt start over
                s = None
                r = 0
                a = None
                #maybe break?
                #break
            else:
                a = max(["up", "down", "left", "right"], key= lambda a_prime: (f(Q[(s_prime,a_prime)], N_s_a[(s_prime,a_prime)],Ne), random.random()))
                moves += 1
                s_n, r_n = execute_action(s_prime,a,mapStart,non_terminal_reward)
                s = s_prime
                r = r_prime
                s_prime = s_n
                r_prime = r_n

        # After the learning, return the learned Q-values
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
    
    formatedRows = [" ".join(f"{str(val):6.3s}" for val in row) for row in mapFinished]
    print("\npolicy:")
    for row in formatedRows:
        print("    ",row)
    return Q


# Define helper function to check if state is terminal
def is_terminal(state, environment):
    i = state[0]
    j = state[1]
    if environment[i][j] == "-1.0" or environment[i][j] == "1.0":
        return True
    else:
        return False
    
def execute_action(state, action, environment, non_terminal_reward):
    actions = {
        'up': (-1, 0),
        'down': (1, 0),
        'left': (0, -1),
        'right': (0, 1)
    }
    wrongState1 = state
    wrongState2 = state
    
    action_effect = actions.get(action)
    if action_effect is None:
        return state, non_terminal_reward  # Invalid action
    

    if action == "up" or action == "down":
        wrongState1 = (state[0] + 0, state[1] - 1) #left
        wrongState2 = (state[0] + 0, state[1] + 1) #right
    else:
        wrongState1 = (state[0] - 1, state[1] + 0)  #up
        wrongState2 = (state[0] + 1, state[1] + 0)  #down

    
    new_state = (state[0] + action_effect[0], state[1] + action_effect[1])
    arrayState = [new_state,wrongState1,wrongState2]

    state_choice = np.random.choice([0,1,2],p=[.8,.1,.1])
    true_state = arrayState[state_choice]
    
    # Check if the new state is within the bounds of the environment and not blocked
    rows = len(environment)
    cols = len(environment[0])
    if (0 <= true_state[0] < rows and 0 <= true_state[1] < cols and 
        environment[true_state[0]][true_state[1]] != 'X'):
        return SenseStateAndReward(true_state, environment, non_terminal_reward)
    else:
        # If the new state is out of bounds or blocked, stay in the current state
        return SenseStateAndReward(state, environment, non_terminal_reward)


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

