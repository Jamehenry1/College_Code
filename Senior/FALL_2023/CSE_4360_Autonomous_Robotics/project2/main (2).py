#!/usr/bin/env pybricks-micropython
# This program requires LEGO EV3 MicroPython v2.0 or higher.
# Click "Open user guide" on the EV3 extension tab for more information.

# from pybricks.hubs import EV3Brick
# from pybricks.ev3devices import Motor
# from pybricks.parameters import Port

# Initialize the EV3 Brick.
# ev3 = EV3Brick()

# #Initialize a motor at port B.
# test_motorA = Motor(Port.A)
# test_motorD = Motor(Port.D)


def check(wrld, base_val, x, y):
    if (x >= x_max or y >= y_max or x < 0 or y < 0):
        return 0
    if wrld[x][y] == -1:
        wrld[x][y] = base_val + 1
        return 1

def adjacent(wrld, loc, adj_list):
    x = loc[0]
    y = loc[1]
    
    if (not(x >= x_max or y - 1 >= y_max or x < 0 or y - 1 < 0) and wrld[x][y - 1] == -1):
        adj_list.append([x,y - 1])
        wrld[x][y - 1] = wrld[x][y] + 1 
    if (not(x >= x_max or y + 1 >= y_max or x < 0 or y + 1 < 0) and wrld[x][y + 1] == -1):
        adj_list.append([x,y + 1])
        wrld[x][y + 1] = wrld[x][y] + 1 
    if (not(x - 1 >= x_max or y >= y_max or x - 1 < 0 or y < 0) and wrld[x - 1][y] == -1):
        adj_list.append([x - 1,y])
        wrld[x - 1][y] = wrld[x][y] + 1 
    if (not(x + 1 >= x_max or y >= y_max or x +1 < 0 or y < 0) and wrld[x + 1][y] == -1):
        adj_list.append([x + 1,y])
        wrld[x + 1][y] = wrld[x][y] + 1 
    
def add_one_to_neighbors(wrld, loc):
    adj_list = []
    adjacent(wrld, loc, adj_list)

    while adj_list:
        cell = list(adj_list.pop(0))
        adjacent(wrld, cell, adj_list)

def checks_index_value(wrld,x,y):
    val = 0
    if wrld[x][y]:
        val = wrld[x][y]
    else:
        val = 0

    return val
        
#       BASIC INFOMATION OF THE ROBOT
#---------------------------------------------------------------------------------------
# Tire = 1.1 inches or 2.8 cm radius
# Turning 1 Tire: 500 is 90 Degrees, - is Clockwise 
# Turning 2 Tires: 250 is 90 Degrees
# 1 Rotation = 17.59292 cm, 17.59292/360 = .048896 cm/degree
    # 360/17.59292 = 2046.2777 degrees/cm
    # 63.334512 Degrees per Cm
# robot length = around 19.05 cm -> .1905 meter, Max Size of Robot= .1905 x .1905
# One Cell Length = 624.1147 in degrees
#---------------------------------------------------------------------------------------
Motor_Speed = 300
Cell_Length = 624.1147

#       MAP INFORMATION
#--------------------------------------------------------------------------------------------------
# 0.305 m x 0.305 size of cell and obstacles blocks
# Map size: 4.88 m x 3.05 m in size (this corresponds to exactly 16 x 10 floor tiles in the lab)
#--------------------------------------------------------------------------------------------------
MAX_OBSTACLES = 25 
num_obstacles = 13

rows = x_max = 16
columns = y_max = 10

obstacles = [
    [0.305 * 4 , 0.305 * 1],
    [0.305 * 4 , 0.305 * 2],
    [0.305 * 4 , 0.305 * 3],
    [0.305 * 4 , 0.305 * 4],
    [0.305 * 4 , 0.305 * 5],
    [0.305 * 7 , 0.305 * 4],
    [0.305 * 7 , 0.305 * 5],
    [0.305 * 7 , 0.305 * 6],
    [0.305 * 7 , 0.305 * 7],
    [0.305 * 7 , 0.305 * 8],
    [0.305 * 7 , 0.305 * 9],
    [0.305 * 7 , 0.305 * 10],
    [0.305 * 10 , 0.305 * 3],
    [0.305 * 10 , 0.305 * 4],
    [0.305 * 10 , 0.305 * 5],
    [0.305 * 10 , 0.305 * 6],
    [0.305 * 10 , 0.305 * 7],
    [0.305 * 11 , 0.305 * 3],
    [0.305 * 12 , 0.305 * 3],
    [0.305 * 12 , 0.305 * 4],
    [0.305 * 13 , 0.305 * 3],
    [0.305 * 13 , 0.305 * 4],
    [0.305 * 4, 0.305 * 0],
    [-1,-1],
    [-1,-1],
    [-1, -1]
]

def Straight():
    print(end="")
    # test_motorA.run_angle(Motor_Speed, -Cell_Length, wait = False)
    # test_motorD.run_angle(Motor_Speed, -Cell_Length, wait = True)

def Rotate_Left():
    print(end="")
    # test_motorA.run_angle(Motor_Speed, 250, wait = False)
    # test_motorD.run_angle(Motor_Speed, -250, wait = True)

def Rotate_Right():
    print(end="")
    # test_motorA.run_angle(Motor_Speed, -249, wait = False)
    # test_motorD.run_angle(Motor_Speed, 249, wait = True)

# Create a nested list filled with zeros
wrld = [[-1 for _ in range(columns)] for _ in range(rows)]

# initialize the starting indexes of the start and goal
start = [0.61, 0.61] # (2, 2)
goal = [3.965, 2.135] # (13, 7)

# convert the x coordinate value to a row value
goal[0] = round(goal[0] / .305) 
goal[1] = round(goal[1] / .305)

# convert the y coordinate value to a column value
start[0] = round(start[0] / .305)
start[1] = round(start[1] / .305)

# set the start to have a really high value
wrld[start[0]][start[1]] = 99

# set the goal to be zero
wrld[goal[0]][goal[1]] = 0

# place the obstacle into the array representation of the world
for obj in obstacles:
    x = round(obj[0] / .305) 
    y = round(obj[1] / .305)

    if x < rows and y < columns and obj[0] != -1:
        wrld[x][y] = float('inf')

# flood fill the map with each successive position being higher in value
# of the goal
add_one_to_neighbors(wrld, goal)

#       IMPORTANT INFORMATION PLEASE READ !!!!!!!!!!!!!!!!!!
#------------------------------------------------------------------------------------
# IMPORTANT !!!!!!!!!!!!!!!!!!!!!!!!
# This is so we know what direction we are facing
# We are going to need to check if our direction is the same as or smallest value, 
# if it is then move that that direction else rotate to that direction
#------------------------------------------------------------------------------------
STRAIGHT = "Straight"
LEFT = "Left"
DOWN = "Down"
RIGHT = "Right"

# Based on wwhat direction it is going it will determine the starting orientation of the robot
#   This is based by comparing the rows (x) if the goal is greater than the start then it is
#   then it is going straight. If the other way then the the robot is doing down
WhereWeGoing = STRAIGHT

if (goal[0] >= start[0]):
    cur_facing_direction = STRAIGHT
else:
    cur_facing_direction = DOWN

#       MAPPING THE MAZE (PATH PLANNING)
#------------------------------------------------------------------------------------
# perspective is from the top
# forward is +rows so +x
# left is +col so +y
# right is -col so -y
#------------------------------------------------------------------------------------
curloc = start

#This loop will check if the robot has reach the goal or not
while curloc != goal:

    # Check the 3 paths around it, go to the smallest one
    curVal = wrld[curloc[0]][curloc[1]]

    # This will give the value in each direction
    valL = checks_index_value(wrld,curloc[0],curloc[1] + 1)
    valR = checks_index_value(wrld,curloc[0],curloc[1] - 1)
    valS = checks_index_value(wrld,curloc[0] + 1,curloc[1])
    valD = checks_index_value(wrld,curloc[0] - 1, curloc[1])

    # Checks to see what direction is the smallest then changes the current location (curloc)
    # These if statements check the current direction vs the next direction and based on that 
    #   it will tell the robot to either go straight, turn left, or turn right. 
    if valS <= valL and valS <= valR and valS <= curVal:
        curloc[0] = curloc[0] + 1 
        smallest_variable = "valS"
        next_facing_direction = STRAIGHT

    elif valL <= valS and valL <= valR and valL <= curVal:
        curloc[1] = curloc[1] + 1
        smallest_variable = "valL"
        next_facing_direction = LEFT
            
    elif valR <= valS and valR <= valL and valR <= curVal:
        curloc[1] = curloc[1] - 1 
        smallest_variable = "valR"
        next_facing_direction = RIGHT

    elif valD <= valL and valD <= valR and valD <= curVal:
        curloc[0] = curloc[0] - 1
        smallest_variable = "valD"
    
    if(smallest_variable == "valR" and cur_facing_direction == DOWN):
        # rotate 90 degrees to the left    
        Rotate_Left()
        # move forward 
        Straight()
        cur_facing_direction = RIGHT

    elif(smallest_variable == "valR" and cur_facing_direction == RIGHT):
        # the robot goes forward in that current direction
        Straight()
        cur_facing_direction = RIGHT

    elif(smallest_variable == "valR" and cur_facing_direction == STRAIGHT):
        # rotate 90 degrees to the right
        Rotate_Right()
        # move forward
        Straight()
        cur_facing_direction = RIGHT
    elif(smallest_variable == "valD" and cur_facing_direction == RIGHT):
        # rotate 90 degrees to the right
        Rotate_Right()
        # move forward
        Straight()
        cur_facing_direction = DOWN
    elif(smallest_variable == "valD" and cur_facing_direction == DOWN):
        #move forward
        Straight()
        cur_facing_direction = DOWN
    elif(smallest_variable == "valD" and cur_facing_direction == LEFT):
        #rotate left
        Rotate_Left()
        #move forward
        Straight()
        cur_facing_direction = DOWN
    elif(smallest_variable == "valS" and cur_facing_direction == STRAIGHT):
        #move forward
        Straight()
        cur_facing_direction = STRAIGHT
    elif(smallest_variable == "valS" and cur_facing_direction == LEFT):
        # rotate right
        Rotate_Right()
        # move forward
        Straight()
        cur_facing_direction = STRAIGHT
    elif(smallest_variable == "valS" and cur_facing_direction == RIGHT):
        # rotate left
        Rotate_Left()
        # move forward
        Straight()
        cur_facing_direction = STRAIGHT
    elif(smallest_variable == "valL" and cur_facing_direction == LEFT):
        # move forward
        Straight()
        cur_facing_direction = LEFT
    elif(smallest_variable == "valL" and cur_facing_direction == DOWN):
        # rotate 90 degrees to the right
        Rotate_Right()
        # move forward
        Straight()
        cur_facing_direction = LEFT
    elif(smallest_variable == "valL" and cur_facing_direction == STRAIGHT):
        # rotate 90 degrees to the left
        Rotate_Left()
        # move forward
        Straight()
        cur_facing_direction = LEFT
        
    curVal = wrld[curloc[0]][curloc[1]]

    print(smallest_variable)

# This will print out the flow map of the robot.
for i in range(len(wrld)):
    for j in range(len(wrld[i])):
        print("{point:3}".format(point = wrld[i][j]), end=" ")
    print()