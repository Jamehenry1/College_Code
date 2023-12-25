Nghia Lam
1001699317

Language: Python3 3.10.10 or Python2 3.9.7 

The code is structured in a way where each method is in a different function

Pass the import I define my node class and initiate my fringe and closed set in global
- beforeChecker() returns the parents information
- dumpWriteOut() write everything out to the dump file
- hCost() is a compare fucntion of the current puzzle vs the goal state
- realHCost() finds the cost of h with the num value applied
- nodeCreate() Creates the node
- direction() checks each direction to see if you can go that direction then calls nodeCreate
- printer() prints the fringe
- LooperPrint() and infoPrint() prints out the moves if it gets to the goal
- ucsSortCondition(), greedySortCondition(), aStarSortCondition(): used for .sort in its each of their own method
- All the other function are the methods, each method creates a node and puts it into 
    the fringe. Then checks the fringe if it is empty or not. Then it compares the state
    of the node vs the goal state using hCost. Afterwards it checks it in the closed set.
    If it is not then it puts the state in the closed set then call direction() create and 
    check each direction to see if it can go to its new position. It it can then it calls 
    nodeCreate. This cycle will loop until nothing is in the fringe or it finds the goal state. 

!!!! DUMP FLAG is 0 or 1
    0 = False
    1 = True

How to run the Code: 
    current directory > python expense_8_puzzle.py <start-file> <goal-file> <method> <dump-flag>
    example: Desktop\AI\Lab1> python expense_8_puzzle.py start.txt goal.txt a* 1 
        This example will create a the trace file and store the dump info in there