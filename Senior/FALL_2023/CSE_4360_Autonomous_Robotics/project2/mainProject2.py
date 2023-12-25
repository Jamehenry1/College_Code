#!/usr/bin/env pybricks-micropython
# This program requires LEGO EV3 MicroPython v2.0 or higher.
# Click "Open user guide" on the EV3 extension tab for more information.

from pybricks.hubs import EV3Brick
from pybricks.ev3devices import Motor
from pybricks.parameters import (Port,Color)
from pybricks.ev3devices import (TouchSensor, ColorSensor, UltrasonicSensor)
import random
import time

# Initialize the EV3 Brick.
ev3 = EV3Brick()

# #Initialize a motor at port B.
test_motorA = Motor(Port.A)
test_motorD = Motor(Port.D)
touch_motor1 = TouchSensor(Port.S2)
touch_motor2 = TouchSensor(Port.S4)
color_sensor = ColorSensor(Port.S3)
touched = False

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
Motor_Speed = 200
Cell_Length = 624.1147
start_time = 0

def Straight():
    test_motorA.run_angle(Motor_Speed, -90, wait = False)
    test_motorD.run_angle(Motor_Speed, -90, wait = True)

def Back():
    test_motorA.run_angle(Motor_Speed, 70, wait = False)
    test_motorD.run_angle(Motor_Speed, 70, wait = True)

def Rotate_Left():
    test_motorA.run_angle(Motor_Speed, 70, wait = False)
    test_motorD.run_angle(Motor_Speed, -70, wait = True)

def Rotate_Right():
    test_motorA.run_angle(Motor_Speed, -70, wait = False)
    test_motorD.run_angle(Motor_Speed, 70, wait = True)

def Rotate_90():
    if ult_sonic_sensor.distance() < 200:
        test_motorA.run_angle(Motor_Speed, -250, wait = False)
        test_motorD.run_angle(Motor_Speed, 250, wait = True)
    else:
        test_motorA.run_angle(Motor_Speed, 250, wait = False)
        test_motorD.run_angle(Motor_Speed, -250, wait = True)

def Unstuck():
    random_num = 250 + int(random.random() * 250)
    if ult_sonic_sensor.distance() < 200:
        test_motorA.run_angle(Motor_Speed, -random_num, wait = False)
        test_motorD.run_angle(Motor_Speed, random_num, wait = True)
    else:
        test_motorA.run_angle(Motor_Speed, random_num, wait = False)
        test_motorD.run_angle(Motor_Speed, -random_num, wait = True)

def Slight_Rotate_Left():
    test_motorA.run_angle(Motor_Speed, 81, wait = False)
    test_motorD.run_angle(Motor_Speed, -81, wait = True)

# Messures in mm 
ult_sonic_sensor = UltrasonicSensor(Port.S1)

def check_end():
    if(color_sensor.color() == Color.YELLOW):
        test_motorA.brake()
        test_motorD.brake()
        ev3.speaker.say("FIRE. FIRE. FIRE.")
        exit()

def check_stuck(move_history):
    if move_history[-5:] == "lrlrl" or move_history[-5:] == "rlrlr":
        move_history += "u"
        Back()
        Unstuck()

    # if move_history[-5:] == "rrrrr" or move_history[-5:] == "lllll":
    #     move_history += "u"
    #     Back()
    #     Unstuck()

# while color not yellow
    # WANDER until hit something
        #if wall on left, turn right and continue moving forward
        #if no wall on left detected, move forward and turn slightly left THEN WANDER


move_history = "aaaaaaaaa"
while(color_sensor.color() != Color.YELLOW):
    while (touch_motor1.pressed() == False and touch_motor2.pressed() == False):
        check_end()
        check_stuck(move_history)
        test_motorA.run(-200)
        test_motorD.run(-200)

    test_motorA.brake()
    test_motorD.brake()

    if(ult_sonic_sensor.distance() < 300):
        start_time = time.time()

        while ult_sonic_sensor.distance() < 300:
            check_end()
            test_motorA.run(-200)
            test_motorD.run(-200)
            if touch_motor1.pressed() == True and touch_motor2.pressed() == True:
                Back()
                Rotate_90()
            if touch_motor1.pressed() == True or touch_motor2.pressed() == True:
                Back()
                Rotate_Right()

        end_time = time.time()

        if(end_time - start_time >= 3):
            move_history += "w"
            Straight()
            Slight_Rotate_Left()
    else:
        #Wall to the Left
        if touch_motor1.pressed() == True and touch_motor2.pressed() == False:
            Back()
            Rotate_Right()
            move_history += "r"
        #Wall to the Right
        elif touch_motor1.pressed() == False and touch_motor2.pressed() == True:
            Back()
            Rotate_Left()
            move_history += "l"
        else:
            Back()
            Rotate_Left()
            move_history += "l"

    

test_motorA.brake()
test_motorD.brake()
ev3.speaker.say("FIRE. FIRE. FIRE.")




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

