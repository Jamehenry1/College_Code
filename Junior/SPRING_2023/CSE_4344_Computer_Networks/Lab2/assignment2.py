import sys

INF = 16

class Table:
    def __init__(self, id):
        self.id = id
        self.graph = []
        self.neighbor = [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]

    def addGraph(self, u, x, v):
        self.graph.append([u,x,v])
    
    def addNeigbor(self,col,cost):
        self.neighbor.append([col,cost])

    def changeNeigborVal(self,x,cost):
        self.neighbor[x][1] = cost

class NodeT:
    def __init__(self,table):
        self.node = [Table(0),Table(1),Table(2),Table(3),Table(4)]
        self.table = table

    def UTable(self,row,col,val):
        self.table[row][col] = val

DVtable = [[0,INF,INF,INF,INF],
           [INF,0,INF,INF,INF],
           [INF,INF,0,INF,INF],
           [INF,INF,INF,0,INF],
           [INF,INF,INF,INF,0]]

Dv = NodeT(DVtable)

def UpdateTable():
    for i in range(5):
        for j in range(5):
            Dv.UTable(i,j,Dv.node[i].neighbor[j][1])

def PrintTable():
    print("\n")
    #for i in range(5):
    #    print(Dv.table[i])

    z = 0
    print(' DV | {:2} | {:^2} | {:>2} | {:<2} | {:<2} |'.format(0,1,2,3,4))
    print('------------------------------')
    for row in Dv.table:
        print('| ' + str(z) + ' | {:2} | {:^2} | {:>2} | {:<2} | {:<2} |'.format(*row))
        z = z+1

#This is opening file and inputing it into a table ----------------------

with open("input.txt") as f:
    content = f.read()

#This zero's out the input on diagonal 
for j in range(5):
    Dv.node[j].changeNeigborVal(j,0)

for i in range(0,len(content),6):
    row = int(content[i]) - 1
    col = int(content[i+2]) - 1
    cost = int(content[i+4])
    DVtable[row][col] = cost
    
    #changes the neigbors value
    if Dv.node[row].neighbor[col][1] == INF:
        Dv.node[row].changeNeigborVal(col,cost)
        Dv.node[col].changeNeigborVal(row,cost)

print("Would you like to run the program without stopping? (y) or (n): ")
answer = input()
z = 0
print("\nTime: " + str(1) + "--------------------------------------\n")
print(' DV | {:2} | {:^2} | {:>2} | {:<2} | {:<2} |'.format(0,1,2,3,4))
print('------------------------------')
for row in DVtable:
    print('| ' + str(z) + ' | {:2} | {:^2} | {:>2} | {:<2} | {:<2} |'.format(*row))
    z = z+1

print("\n")

#------------------------------------------------------------------------

def DVmaker(check): #Check is the slot it is calculating
    
    zero = [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]
    one = [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]
    two = [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]
    three = [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]
    four = [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]
    minValNeigbor = [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]

    UpdateTable()
    #PrintTable()

    #Reciving: Testing with node 0
    for i in range(5):
        if Dv.node[check].neighbor[i][1] != 16: # This gets the neighbor ---- 
            if Dv.node[check].neighbor[i][1] != 0:
                #print("neigbor: " + str(i))
                print("node " + str(check) + " reveives DV from node " + str(i))
                #nholder.append(i)
                #print(Dv.node[i].neighbor)  # This computes each neighbor
                for j in range(5):
                    if i == 0:
                        zero[j][1] = Dv.node[check].neighbor[i][1] + Dv.node[i].neighbor[j][1]
                    if i == 1:
                        one[j][1] = Dv.node[check].neighbor[i][1] + Dv.node[i].neighbor[j][1]
                    if i == 2:
                        two[j][1] = Dv.node[check].neighbor[i][1] + Dv.node[i].neighbor[j][1]
                    if i == 3:
                        three[j][1] = Dv.node[check].neighbor[i][1] + Dv.node[i].neighbor[j][1]
                    if i == 4:
                        four[j][1] = Dv.node[check].neighbor[i][1] + Dv.node[i].neighbor[j][1]

                for k in range(5):  # This gets the min value of all the neighbor
                    minValNeigbor[k][1] = min(zero[k][1],one[k][1],two[k][1],three[k][1],four[k][1],)
    

    return minValNeigbor

def sendDV():
    #time = 1
    #count = 1

    #while count < 0:
    count = 0
    #print("Time: " + str(time) + "-----------------------------")
    DVArray =  [[0,INF],[1,INF],[2,INF],[3,INF],[4,INF]]
    PrintOutputString = []
    
    #print(PrintOutputString)

    DVArray[0] = DVmaker(0)
    DVArray[1] = DVmaker(1)
    DVArray[2] = DVmaker(2)
    DVArray[3] = DVmaker(3)
    DVArray[4] = DVmaker(4)

    
    print("\nDV Table: ")
    for i in range(5): #This will check if the new calculated Dv for each neighbor is less then before
        for j in range(5):
            if DVArray[i][j][1] < Dv.node[i].neighbor[j][1]:
                PrintOutputString.append("Updated node " + str(i) +" --> " + str(j) + " from cost " +
                                            str(Dv.node[i].neighbor[j][1]) + " --> " + str(DVArray[i][j][1]))
                Dv.node[i].changeNeigborVal(j,DVArray[i][j][1])
                count = count + 1

    if len(PrintOutputString) != 0:
        for x in PrintOutputString:
            print(x)
        #print("Count: " + str(count))
    else:
        print("None")

    UpdateTable()
    PrintTable()
    #time = time + 1
    return count

def Run(time):
    
    xinput = 0
    
    if answer == "n":
        print("Enter (c) to change a link, or press (enter) to proceed: ")
        xinput = input()
        if xinput == "c":
            print("changed")
            row, col, cost = input("Enter three values: ").split()
            print("Row Number : ", row)
            print("Col Number : ", col)
            print("Cost : ", cost)

            Dv.node[int(row)-1].changeNeigborVal(int(col)-1,int(cost))
            Dv.node[int(col)-1].changeNeigborVal(int(row)-1,int(cost))
    
    count = sendDV()
        
    if count > 0:
        time = time + 1
        print("\nTime: " + str(time) + "--------------------------------------\n")
        Run(time)

    return time

time = Run(1)