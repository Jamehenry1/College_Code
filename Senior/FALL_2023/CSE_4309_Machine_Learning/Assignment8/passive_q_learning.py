# Nghia Lam
# 1001699317

import numpy as np
import copy 

def policy_evaluation(S, P, R, gamma, pi, K, U):
    U_k = copy.deepcopy(U)  # Make a copy of the initial utilities

    for k in range(1, K+1):
        U_k_prev = copy.deepcopy(U_k)  # Copy the utilities from the previous iteration
        for s in S:
            action = pi[s]  # Get the action prescribed by the policy for state s
            # Sum over all possible next states
            U_k[s] = R(s) + gamma * sum(P(s_prime, s, action) * U_k_prev[s_prime] for s_prime in S)

    return U_k

def AgentModel_Q_Learning_Passive(environment_file, policy_file, 
                              ntr, gamma, number_of_moves):
    mapStart = []
    policyMap = []
    nodeMap = []
    
    with open(environment_file, 'r') as file:
        for line in file:
            data = [x for x in line.strip().replace(" ","").split(",")]

            mapStart.append(data)
    
    with open(policy_file, 'r') as file:
        for line in file:
            data = [x for x in line.strip().replace(" ","").split(",")]
            policyMap.append(data)

    for i in range(len(mapStart)):
        for j in range(len(mapStart[i])):
            if mapStart[i][j] == ".":
                mapStart[i][j] = 0 
            
                

    print(mapStart)
    print(policyMap)
