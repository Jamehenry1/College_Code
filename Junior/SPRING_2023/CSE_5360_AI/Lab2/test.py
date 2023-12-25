import sys

def red_blue_nim(num_red, num_blue, first_player='computer', depth=None):
    player = first_player
    red_score = 2 * num_red
    blue_score = 3 * num_blue
    state = (num_red, num_blue)
    
    while num_red > 0 and num_blue > 0:
        print(f"Red marbles left: {num_red}, Blue marbles left: {num_blue}")
        
        if player == 'computer':
            print("Computer's turn")
            _, move = minimax(state, depth, -sys.maxsize, sys.maxsize, True)
            if move[0] == 'red':
                num_red -= 1
                print(f"Computer takes 1 red marble")
            else:
                num_blue -= 1
                print(f"Computer takes 1 blue marble")
            player = 'human'
            
        else:
            print("Your turn")
            move = input("Which pile do you want to take from (red/blue)? ")
            while move not in ['red', 'blue'] or (move == 'red' and num_red == 0) or (move == 'blue' and num_blue == 0):
                print("Invalid move")
                move = input("Which pile do you want to take from (red/blue)? ")
            if move == 'red':
                num_red -= 1
            else:
                num_blue -= 1
            player = 'computer'
            
    print("Game over!")
    if num_red == 0:
        winner = 'blue'
        score = blue_score
    else:
        winner = 'red'
        score = red_score
    print(f"{winner.capitalize()} wins with a score of {score}")
    
def minimax(state, depth, alpha, beta, maximizing_player):
    if depth == 0 or state[0] == 0 or state[1] == 0:
        red_score = 2 * state[0]
        blue_score = 3 * state[1]
        if maximizing_player:
            return blue_score - red_score, None
        else:
            return red_score - blue_score, None
        
    if maximizing_player:
        max_eval = -sys.maxsize
        max_move = None
        for move in [('red',), ('blue',)]:
            if move[0] == 'red' and state[0] == 0:
                continue
            if move[0] == 'blue' and state[1] == 0:
                continue
            eval, _ = minimax(update_state(state, move), depth-1, alpha, beta, False)
            if eval > max_eval:
                max_eval = eval
                max_move = move
            alpha = max(alpha, eval)
            if beta <= alpha:
                break
        return max_eval, max_move
    
    else:
        min_eval = sys.maxsize
        min_move = None
        for move in [('red',), ('blue',)]:
            if move[0] == 'red' and state[0] == 0:
                continue
            if move[0] == 'blue' and state[1] == 0:
                continue
            eval, _ = minimax(update_state(state, move), depth-1, alpha, beta, True)
            if eval < min_eval:
                min_eval = eval
                min_move = move
            beta = min(beta, eval)
            if beta <= alpha:
                break
        return min_eval