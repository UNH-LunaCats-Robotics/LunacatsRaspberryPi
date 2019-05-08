from RobotCommunication import *
import GetPixyInfo
from time import sleep
import json
import threading
import SerialMessages



# The height that the picture should be at the target position
posHeight = 20
posWidth  = 30

# The allowed variation for the height
heightVary = 5
widthVary = 5;


taskInput = ""

lidarDistance = 0
objectDetected = False


def terminTask():
    global taskInput
    while taskInput != "S":
        taskInput = raw_input("Input")


def faceTarget(angle,target):
    if angle - 50 > target:
        right(15)
        return False
    elif angle + 50 < target:
        left(15)
        return False
    return True

def goForward():
    SerialMessages.send_json({"c":0})


def goBack():
    SerialMessages.send_json({"c":1})

def goLeft(angle):
    SerialMessages.send_json({"c":2})

def goRight(angle):
    SerialMessages.send_json({"c":3})

def holdPos():
    SerialMessages.send_json({"c":4})


atGoodHeight = False

def processHeight(data,i):
    global atGoodHeight
    height = data["H" + str(i)]
    #print "getting Height:" + str(height)

    if height > posHeight + heightVary:
        goBack()
        atGoodHeight = False
    elif height < posHeight - heightVary:
        goForward()
        atGoodHeight = False
    else:
        atGoodHeight = True
        holdPos()

def processWidth(data,i,angle):
    width = data["W" + str(i)]
    #print "getting Width:" + str(width)

    if width > posWidth + widthVary:
        goLeft(angle)
    elif width < posWidth - widthVary:
        goRight(angle)
    else:
        holdPos()





if __name__ == '__main__':

    GetPixyInfo.startup()

    while taskInput != "S":
        
        data = GetPixyInfo.getSig()

        if objectDetected:
            print "Object Detected!!!!!"
            back(15)
            sleep(0.5)
            left(15)
            sleep(2)
            forward(15)
            sleep(1.5)
            objectDetected = False
            print "Object evaded!"
        if data["C"] == 0:
            holdPos()
        else:
            for i in range(0,data["C"]):
                if data["S"+str(i)] == 1:
                    processHeight(data,i)
                if data["S" + str(i)] == 1 and atGoodHeight:
                    # processWidth(data, i,data["A"])
                    print "Test"