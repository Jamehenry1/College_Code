#!/usr/bin/env pybricks-micropython
from pybricks.hubs import EV3Brick
from pybricks.ev3devices import (Motor, TouchSensor, ColorSensor,
                                 InfraredSensor, UltrasonicSensor, GyroSensor)
from pybricks.parameters import Port, Stop, Direction, Button, Color
from pybricks.tools import wait, StopWatch, DataLog
from pybricks.robotics import DriveBase
from pybricks.media.ev3dev import SoundFile, ImageFile
from pybricks.iodevices import I2CDevice

import time
import random

# define variables and constants
blueCount = 0
default_speed = 400
motor_speed = 450

# initilize ev3 object
ev3 = EV3Brick()

# initialize sensors and motors
motorA = Motor(Port.A)
motorD = Motor(Port.D)
color_sensor = ColorSensor(Port.S3)
sonar_sensor = UltrasonicSensor(Port.S1)
ir_seeker = I2CDevice(Port.S2, 0x01)
gyro = GyroSensor(Port.S4, Direction.CLOCKWISE)
gyro.reset_angle(0)

def turn_90(direction):
    speed = 450
    if direction == "left":
        motorA.run_angle(speed, 250, wait = False)
        motorD.run_angle(speed, -250, wait = True)
    else:
        motorA.run_angle(speed, -250, wait = False)
        motorD.run_angle(speed, 250, wait = True)

def turn_by_angle(angle):
    spd = 3
    print("turning by", angle, "degree(s)")
    motorA.run_angle(motor_speed, -spd * angle, wait = False)
    motorD.run_angle(motor_speed, spd * angle, wait = True)
        
def read_sensor(ir_seeker):
    # direction will be either 0 - 9
    # 0 - no infrared detected
    direction = int.from_bytes(ir_seeker.read(0x42, 1), 'little')

    # five numbers that represent the magnitude of the infrared at each 
    # sensor
    # 0th - facing at 1
    # 1st - facing at 3
    # 2nd - facing at 5
    # 3rd - facing at 7
    # 4th - facing at 9
    magnitude = []

    for i in range(0, 5):
        magnitude.append(int.from_bytes(ir_seeker.read(0x43 + i, 1), 'little'))

    return direction, magnitude

def ball_in_sight(ir_data):
    print("direction:", ir_data[0])
    return ir_data[0] > 0
    
def ball_in_possession(ir_data):
    print("checking if ball in posesssion")
    print(sum(ir_data[1]))
    if sum(ir_data[1]) > 30:
        return True
    
    return False

def color_check(blueCount):
    # print("bluecount = ", blueCount)
    if color_sensor.color() == Color.RED or color_sensor.color() == Color.BLUE and blueCount > 0:
        # print("CHECKING COLOR")
        motorA.run(default_speed)
        motorD.run(default_speed)
        time.sleep(1.25)
        turn_90("left")
        if ball_in_sight(read_sensor(ir_seeker)): return blueCount
        turn_90("left")

        return blueCount
    
    elif blueCount == 0 and color_sensor.color() == Color.BLUE:
        motorA.run(-default_speed)
        motorD.run(-default_speed)
        time.sleep(1)
        return blueCount + 1
    
    elif blueCount == 0:
        return 0
    
    elif color_sensor.color() == Color.BLUE:
        return blueCount + 1
    
    else:
        return blueCount

def set_motor_right(direction, speed):
    motorD.run(direction * speed)

def set_motor_left(direction, speed):
    motorA.run(direction * speed)

def get_angle_to_turn_by(angle):
    temp_angle = angle
    angle_to_turn_by = 0

    while abs(temp_angle) > 360:
        if temp_angle > 0:
            temp_angle -= 360
        else:
            temp_angle += 360

    if abs(temp_angle) > 180:
        if temp_angle > 0:
            angle_to_turn_by = 360 - abs(temp_angle)
        else:
            angle_to_turn_by = -1 * (360 - abs(temp_angle))
    else:
        angle_to_turn_by = -1 * temp_angle
    
    return angle_to_turn_by

while True:
    seenVal = read_sensor(ir_seeker)
    print(seenVal[0],seenVal[0] % 5)
    randomPickLeftorRight = random.randint(0,1)
    val = -1
    blueCount = color_check(blueCount)

    if seenVal[0] > 0:
        # ball seen and is now in our possession so now turn towards goal
        if ball_in_possession(seenVal):
            if sonar_sensor.distance() < 250:
                turn_by_angle(get_angle_to_turn_by(gyro.angle()))
                continue
            
            print("BALL IN POSSESSION")

            if color_sensor.color() == Color.RED: continue

            angle = gyro.angle()

            # turn the correct direction
            if abs(angle) % 360 == 0:
                # gun it
                set_motor_left(-1, 1000)
                set_motor_right(-1, 1000)
                continue

            angle_to_turn_by = get_angle_to_turn_by(angle)

            if color_sensor.color() == Color.RED: continue

            if angle_to_turn_by <= 30 and angle_to_turn_by >= -30:
                print("no need to turn")
            else:
                turn_by_angle(angle_to_turn_by)
            
            if color_sensor.color() == Color.RED: continue

            # gun it
            set_motor_left(-1, 1000)
            set_motor_right(-1, 1000)
            time.sleep(.2)
            if color_sensor.color() == Color.RED: continue
            
            continue

        # chase ball
        elif 1 < seenVal[0] < 5:
            if sonar_sensor.distance() < 250:
                turn_90("left")

            val = (10 - seenVal[0]) % 5

            print("ball is on the left Magnitude:", val)

            if color_sensor.color() == Color.RED: continue

            motorA.run(-default_speed/(val * 3))
            motorD.run(-default_speed * (val * 1.5))

        elif 5 < seenVal[0] < 9:
            if sonar_sensor.distance() < 250:
                turn_90("left")
                continue

            val = (seenVal[0] % 5)

            print("ball is on the right Magnitude:", val)

            if color_sensor.color() == Color.RED: continue

            motorA.run(-default_speed * (val * 1.5))
            motorD.run(-default_speed/(val * 3))

        elif seenVal[0] == 5:
            if sonar_sensor.distance() < 250:
                continue

            # check to see if we crossed the red line
            if color_sensor.color() == Color.RED: continue

            motorA.run(-default_speed)
            motorD.run(-default_speed)

        elif seenVal[0] == 0:
            continue
    else:
        blueCount = color_check(blueCount)
        
        # if the color is not seen then wander
        if color_sensor.color() != Color.RED and color_sensor.color() != Color.BLUE:

            # if it sees a wall
            if sonar_sensor.distance() < 250:
                print("wall")
                if randomPickLeftorRight == 0:
                    turn_90("right")

                elif randomPickLeftorRight == 1:
                    turn_90("left")

            # if it is open space then wander
            else:
                if randomPickLeftorRight == 0:
                    motorA.run(-default_speed)
                    motorD.run(-default_speed/2)
                    blueCount = color_check(blueCount)

                else:
                    motorA.run(-default_speed/2)
                    motorD.run(-default_speed)

                    blueCount = color_check(blueCount)

                blueCount = color_check(blueCount)
                time.sleep(.2)

            blueCount = color_check(blueCount)

        # if the color is red or blue back up a little bit and turn 
        blueCount = color_check(blueCount)