Nghia Lam 1001699317

Python 3 and Python 2

The code is structured like the minmax pruning on the slides except there is no terminal function. I have terminal conditions where the terminal fucntion would be. 


CODE STRUCTURE

- util(state): This is the utility state and I use it to calcuate the score for minmax
- childstates(state): This gives me the child states
- maxValue(state,alpha,beta,depth): This function has the terminal condition, the alpha beta and calling of the min function. The terminal condition has has it so when the depth hits 0 it returns same in minValue(state,alpha,beta,depth)
- minValue(state,alpha,beta,depth): This function has the terminal condition, the alpha beta and calling of the max function
- alphaBetaDecision(state,depth): This is where the call starts and where it will calculate which move it is going to do
- def red_blue(num_red,num_blue,player,depth): This handles the turns, calling alphaBetaDecision(state,depth) when it is the computer's turn, and the win condition. 

(1) | Winner,score = red_blue(int(NUM_RED),int(NUM_BLUE),FIRST_PLAYER,Depth) <- This is where it starts	
(2) | def red_blue(num_red,num_blue,player,depth): 										
(3) | alphaBetaDecision(state,depth):	
(4) | minValue(state,alpha,beta,depth):
(5) |	maxValue(state,alpha,beta,depth):

HOW TO RUN THE CODE 

- c = computer
- p = human

Outline : python red_blue_nim.py <red> <blue> <player> <depth>
Example1: python red_blue_nim.py 4 4 c 3
Example2: python .\red_blue_nim.py 4 4 c 3

Win condition: 	turn 1 Person turn:   red 1 blue 1
			picks red
			turn 2 Computer turn: red 0 blue 1
			Computer wins points 3